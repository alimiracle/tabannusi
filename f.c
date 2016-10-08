#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <syslog.h>
#include <unistd.h>
int main(int argc, char *argv[])
{
 /* Open a connection to the syslog server */
 openlog(argv[0],LOG_NOWAIT|LOG_PID,LOG_USER);
 pid_t pid;
 pid = fork();
 /* If the pid is less than zero, something went wrong when forking */
 if (pid < 0) 
{
/* Now we will tel the  log server hi cant fork*/
 syslog(LOG_NOTICE, "Cant Fork\n");
 exit(EXIT_FAILURE);
 }
 /* If the pid we got back was greater than zero, then the clone was successful and we are the parent. */ 
if (pid > 0)
 {
 exit(EXIT_SUCCESS);
 }
 /* If execution reaches this point we are the child */
 /* Now we will Set the umask to zero */ 
umask(0);
 /* Now we will  create our own process group */
 pid_t sid;
 /* Try to create our own process group */
 sid = setsid();
/* its seme ok now/*
 /* Now we will Change the current working directory to root */
 chdir("/");
/* Close all io /*
 close(STDIN_FILENO);
 close(STDOUT_FILENO);
 close(STDERR_FILENO);
    //catch/ignore signals
    signal(SIGCHLD,SIG_IGN);
    signal(SIGHUP,SIG_IGN);
/* Now we will tel the log server its ok now */
 /* Sends a message to the syslog daemon */
 syslog(LOG_NOTICE, "Successfully started daemon\n");
 closelog();
/* make new file to save last commit */
FILE *fp = fopen("scores.dat", "ab+");
fclose(fp);

while (1)
{
system("bash /home/ali/run.sh");
}
}
