#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <syslog.h>
#include <unistd.h>
#include <signal.h>
int main(int argc, char *argv[])
{
 /* Open a connection to the syslog server */
 openlog(argv[0],LOG_NOWAIT|LOG_PID,LOG_USER);
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
/* Creating a Unique Session ID (SID)*/
    if (setsid() < 0)
 syslog(LOG_NOTICE, "I can't create a Unique Session ID ");
        exit(EXIT_FAILURE);
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
/* it's the same ok now*/
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
FILE *fp = fopen("scores.dat", "ab+");
fclose(fp);

while (1)
{
system("bash /bin/run.sh");
}
}
