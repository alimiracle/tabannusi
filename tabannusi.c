#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <syslog.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <string.h>
int read_pid (char *pidfile)
{
  FILE *f;
  int pid;

  if (!(f=fopen(pidfile,"r")))
    return 0;
  fscanf(f,"%d", &pid);
  fclose(f);
  return pid;
}
/* check_pid
 *
 * Reads the pid using read_pid and looks up the pid in the process
 * table (using /proc) to determine if the process already exists. If
 * so 1 is returned, otherwise 0.
 */
int check_pid (char *pidfile)
{
  int pid = read_pid(pidfile); /* rede the pid from file and save it to var */

  /* Amazing ! _I_ am already holding the pid file... */
  if ((!pid) || (pid == getpid ()))
    return 0;

  /*
   * The 'standard' method of doing this is to try and do a 'fake' kill
   * of the process.  If an ESRCH error is returned the process cannot
   * be found -- GW
   */
  /* But... errno is usually changed only on error.. */
  if (kill(pid, 0) & errno == ESRCH)
	  return(0);

  return pid;
}
int write_pid (char *pidfile)
{
  FILE *f;
  int fd;
  int pid;

  if ( ((fd = open(pidfile, O_RDWR|O_CREAT, 0644)) == -1)
       || ((f = fdopen(fd, "r+")) == NULL) ) {
      fprintf(stderr, "Can't open or create %s.\n", pidfile);
      return 0;
  }

 /* It seems to be acceptable that we do not lock the pid file
  * if we run under Solaris. In any case, it is highly unlikely
  * that two instances try to access this file.
  */

#if HAVE_FLOCK
  if (flock(fd, LOCK_EX|LOCK_NB) == -1) {
      fscanf(f, "%d", pid);
      fclose(f);
      printf("Can't lock, lock is held by pid %d.\n", pid);
      return 0;
  }
#endif

  pid = getpid();
  if (!fprintf(f,"%d\n", pid)) {
      char errStr[1024];
      printf("Can't write pid , %s.\n", errStr);
      close(fd);
      return 0;
  }
  fflush(f);

#if HAVE_FLOCK
  if (flock(fd, LOCK_UN) == -1) {
      char errStr[1024];
      printf("Can't unlock pidfile %s, %s.\n", pidfile, errStr);
      close(fd);
      return 0;
  }
#endif
  close(fd);

  return pid;
}

/* function run by Demon */
void* runcmd (void* unused)
{
system("bash /bin/run.sh");
return NULL; 
}
int run()
{
pthread_t thread_id;
        /* Fork off the parent process */       
 pid_t pid;
 pid = fork();
 /* If the pid is less than zero, something went wrong when forking */
 if (pid < 0) 
{
/* Now we will tell the log server can't fork*/
 syslog(LOG_NOTICE, "Cant Fork\n");
 exit(EXIT_FAILURE);
 }
 /* If the pid we got back was greater than zero, then the clone was successful and we are the parent. */ 
if (pid > 0)
 {
 exit(EXIT_SUCCESS);
 }
 /* If execution reaches this point we are the child */
/* disassociating from the controlling terminal */
#if HAVE_SETSID /* if your os have SETSID, use it */
/* Creating a Unique Session ID (SID)*/
    if (setsid() < 0)
{
 syslog(LOG_NOTICE, "I can't create a Unique Session ID ");
        exit(EXIT_FAILURE);
}
#elif defined(TIOCNOTTY) /* if  the os dont have SETSID use IOCNOTTY*/
int fd;
    fd = open("/dev/tty", O_RDWR);
    if (fd >= 0) {
        if (ioctl(fd, TIOCNOTTY, NULL) < 0)
{
syslog(LOG_NOTICE, "cant disassociate from the terminal");
       exit(EXIT_FAILURE);
}
        close(fd);
    }
#endif /* defined(TIOCNOTTY) */
    //catch/ignore signals
    signal(SIGCHLD,SIG_IGN);
    signal(SIGHUP,SIG_IGN);
        /* Fork off the parent process */
pid_t pid1;
 pid1 = fork();
 /* If the pid1 is less than zero, something went wrong when forking */
 if (pid1 < 0) 
{
/* Now we will tell the log server can't fork*/
 syslog(LOG_NOTICE, "Can't fork\n");
 exit(EXIT_FAILURE);
 }
 /* If the pid1 we got back was greater than zero, then the clone was successful and we are the parent. */ 
if (pid1 > 0)
 {
 exit(EXIT_SUCCESS);
 }
 /* Now we will set the umask to zero */ 
umask(0);
 /* Now we will Change the current working directory to root */
 chdir("/");
/* Close all Files */
 close(STDIN_FILENO);
 close(STDOUT_FILENO);
 close(STDERR_FILENO);
/* Now we will tell the log server it's ok now */
 syslog(LOG_NOTICE, "Successfully started daemon\n");
 /* close a connection to the syslog server */
 closelog();
/* make new file to save last commit */
FILE *fp = fopen("/tmp/q.txt", "ab+");
fclose(fp);
write_pid("/var/run/tabannusi.pid");

while (1)
{

/* run runcmd function in new thread */
pthread_create (&thread_id, NULL, &runcmd, NULL);
sleep(10);
}
}
void start()
{
int scann = check_pid("/var/run/tabannusi.pid");
puts("Starting tabannusi daemon:\n");

if(scann!=0)
{
puts("tabannusi daemon already started\n");
exit(1);
}
run();
}
void stop()
{
pid_t pid=read_pid("/var/run/tabannusi.pid");
int scann = check_pid("/var/run/tabannusi.pid");
puts("Stopping tabannusi daemon\n:");
if(scann==0)
{
puts("tabannusi daemon is not running\n");
exit(1);
}
 kill(pid, SIGKILL);
}
void restart()
{
stop();
start();
}

void usage(void) {
    fprintf(stderr, "Usage: tabannusi [options]\n");
    fputs("start\n" "restart\n" "stop\n", stderr);
    exit(1);
}
int main(int argc, char *argv[])
{
 /* Open a connection to the syslog server */
 openlog(argv[0],LOG_NOWAIT|LOG_PID,LOG_USER);
if(argc==1)
{
usage();
}
if (strcmp(argv[1], "start") == 0) 
{
  // do something
start();
} 
else if (strcmp(argv[1], "stop") == 0)
{
  // do something else
stop();
}
else if (strcmp(argv[1], "restart") == 0)
{
  // do something else
restart();
}

    return 0;
}
