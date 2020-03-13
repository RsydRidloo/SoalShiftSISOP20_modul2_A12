#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main() {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while (1) {
    // Tulis program kalian di sini
	pid_t child_id;

	child_id = fork();
	
	time_t t = time(NULL);

	struct tm tm = *localtime(&t);

	char datestr[100];

	sprintf(datestr, "%d-%02d-%02d_%02d:%02d:%02d",tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

	char path[100] = "/home/angelita/modul2/";

	strcat(path, datestr);

	if(child_id < 0)
	{
  		exit(EXIT_FAILURE);
  	}

  	if(child_id == 0)
  	{	
		char *mkdir[] = {"mkdir", "-p", path, NULL};
  		execv("/bin/mkdir", mkdir);
  	}	
    sleep(30);
  }
}

