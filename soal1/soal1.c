#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/wait.h>

int angkacheck(char isi[]){
   if(strlen(isi) == 1)
        if(isi[0] == '*')
            return 1;
    else{
        for(int i = 0; i < strlen(isi); i+=1){
            if(isi[i] > '0' || isi[i] < '9')
                return 2;
        }
    }

}
int main(int argc, char *argv[]) {
  int jam,menit,detik,detik_tm,menit_tm,jam_tm;

  //cek apabila argumen sama dengan 4

  if(argc != 5){
    printf("Tolong Sesuaikan dengan argumen !!!\n");
    return 0;
  }

//cek detik sesuai argumen yang diinputkan

  if(strcmp(argv[1],"*") == 0) detik = 60;
  else if(angkacheck(argv[1])){
    detik = atoi(argv[1]);
  }
   else  if(detik > 59 || detik < 0){
      printf("Input Angka 0-59 woy\n");
      return 0;
    }
    else{
        printf("Input angka woy\n");
      return 0;
    }


  //cek apakah menit sesuai argumen yang diinputkan

  if(strcmp(argv[2],"*") == 0) menit = 60;
  else if(angkacheck(argv[2])){
    menit = atoi(argv[2]);
  }
  else  if(menit > 59 || menit < 0){
      printf("Input Angka 0-59 woy\n");
       return 0;
        }
    else{
        printf("Input angka woy\n");
      return 0;

    }


  // Mengecek apakah jam sesuai argumen yang diinginkan

  if(strcmp(argv[3],"*") == 0) jam = 24;
  else if(angkacheck(argv[3])){
    jam = atoi(argv[3]);
  }
  else  if(jam > 23 || jam < 0){
      printf("Input Angka 0-23 woy\n");
      return 0;
        }
    else{
    printf("Input angka woy\n");
      return 0;
    }

  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

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
     time_t timer = time(NULL);
     struct tm *tm_info = localtime(&timer);

     detik_tm = tm_info->tm_sec;
     menit_tm = tm_info->tm_min;
     jam_tm = tm_info->tm_hour;

      if ((tm_info->tm_sec == detik || detik == 60) && (tm_info->tm_min == menit || menit == 60)
        && (tm_info->tm_hour == jam || jam == 24))
      {

        pid_t child_id;
        child_id = fork();
int status;
        if (child_id == 0)
        {
          char *args[] = {"bash", argv[4], NULL};
          execv("/bin/bash", args);
        }
        else
           while ((wait(&status)) > 0);
    }

     sleep(1);

  }
}
     
