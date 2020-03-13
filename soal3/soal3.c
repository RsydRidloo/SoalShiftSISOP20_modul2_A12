#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>


int main()
{
	//makedirectory
	pid_t indomie, sedaap; //variabel untuk menyimpan pid

	indomie = fork(); //menyimpan pid child process (indomie)

	//keluar saat fork gagal (nilai variabel pid<0)
	if(indomie < 0)
	{
		exit(EXIT_FAILURE);
	}
	
	if(indomie == 0)
	{
		//child process(indomie) untuk membuat folder indomie di home/angelita/modul2/
		char *argv[] = {"mkdir",  "/home/angelita/modul2/indomie", NULL};
		execv("/bin/mkdir",argv);
	}
	sleep(5); //sleep selama 5 detik untuk jeda pembuatan folder sedaap setelah membuat folder indomie
	
	sedaap = fork(); //menyimpan pid child process(sedaap)
	
	//keluar saat fork gagal (nilai variabel pid<0)
	if(sedaap < 0)
	{
		exit(EXIT_FAILURE);
	}
	if(sedaap == 0)
	{
		//child process(sedaap) untuk membuat folder indomie di home/angelita/modul2/
		char *argv[] = {"mkdir", "/home/angelita/modul2/sedaap", NULL};
		execv("/bin/mkdir",argv);
	}
	
	//unzip
	pid_t anzippu; //variabel untuk menyimpan pid

	anzippu = fork(); // menyimpan pid child process(anzippu)

	//keluar saat fork gagal (nilai variabel pid<0)
	if(anzippu < 0)
	{
		exit(EXIT_FAILURE);
	}
	
	//child process(anzippu) mengekstrak/unzip jpg.zip
	if(anzippu == 0)
	{
		char *argv[] = {"unzip", "/home/angelita/modul2/jpg.zip",  NULL};
		execv("/usr/bin/unzip",argv);
	}


	return 0;

}
