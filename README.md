## Angelita Titiandes Br. Silalahi (05111840000088)
## Rasyid Ridlo W (05111840000135)


# Laporan Penjelasan

1. Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan ketentuan sebagai berikut:

    a. Program menerima 4 argumen berupa:
    
        i. Detik: 0-59 atau * (any value)
      
        ii. Menit: 0-59 atau * (any value)
      
        iii. Jam: 0-23 atau * (any value)
      
        iv. Path file .sh
    
    b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai
  
    c. Program hanya menerima 1 config cron
  
    d. Program berjalan di background (daemon)
  
    e. Tidak boleh menggunakan fungsi system()
    
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
       		
		
		
       		int checkangka(char isi[]){                                                                                             
			if(strlen(isi) == 1) // panjang string adalah 1                                                                              
			if(isi[0] == '*')// jika isi indeks 0 adalah *                                                                              
				return 1; // maka return 1                                                                                      
			else{//jika isi indeks tidak *                                                                                 	
				for(int i = 0; i < strlen(isi); i+=1){//untuk perulangan sebanyak panjang karakter                                          
			    	if(isi[i] > '0' || isi[i] < '9')//jika isi indeks berisikan angka 0-9                                                       
					return 2;                                                                                                       
			   	 }                                                                                                                   				}                                                                                                                                                                                                                                           			}        
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
     				time_t timer = time(NULL);//time_t(tipe data ) , time(NULL) memasukkan waktu sekarang ke timer
     				struct tm *tm_info = localtime(&timer//struct tm  ,nama struct yaitu tim_info 

     				detik_tm = tm_info->tm_sec;
     				menit_tm = tm_info->tm_min;
     				jam_tm = tm_info->tm_hour;
				
				//Pengondisian untuk menjalankan jika telah memnuhi persyaratan misal 
				"if ((tm_info->tm_sec == detik || detik == 60)" Jika waktu detik sekarang == waktu detik input atau detik = 				     * == 60
				
      				if ((tm_info->tm_sec == detik || detik == 60) && (tm_info->tm_min == menit || menit == 60)
        				&& (tm_info->tm_hour == jam || jam == 24))
      				{

        				pid_t child_id;
        				child_id = fork();
					int status;
        				if (child_id == 0)
        				{
          					char *args[] = {"bash", argv[4], NULL};//untuk bash argv4
          					execv("/bin/bash", args);//menjalankan program bash dan menggantikan program yg sedang 										   berjalan
        				}
        				else
           				while ((wait(&status)) > 0);
    				}

     				sleep(1);//untuk mengulang setiap detik

  			}
		}

Penjelasan	: 
* if(strlen(isi) == 1) = jika panjang string adalah 1                                                                              
* if(isi[0] == '*') = jika isi indeks 0 adalah *                                                                                                                                                                                                                                              
* for(int i = 0; i < strlen(isi); i+=1){ = untuk perulangan sebanyak panjang karakter                                          
* if(isi[i] > '0' || isi[i] < '9') = jika isi indeks berisikan angka 0-9    
* if(strcmp(argv[1],"*") == 0) detik = 60;  = membandingkan jikan string 1 & 2 sama maka detik berubah menjadi 60                                                                           
  else if(checkangka(argv[1])){             = mengecek angka yg diinput                                                                              
  detik = atoi(argv[1]);                    = mengubah string menjadin integer                                                   
}                                                                                                                        
* else  if(detik > 59 || detik < 0){       = jika detik tidak sesuai 0-59 maka keluar peringatan                                                                                 
  printf("Input Angka 0-59 woy\n"); 
* time_t timer = time(NULL); = time_t(tipe data ) , time(NULL) memasukkan waktu sekarang ke timer
* struct tm *tm_info = localtime(&timer = struct tm  ,nama struct yaitu tim_info 
     



  
2. Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat sebuah program.

    a. Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat sebuah program C yang per 30 detik membuat sebuah folder dengan nama timestamp [YYYY-mm-dd_HH:ii:ss].
  
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

			pid_t child_id;

			child_id = fork();
	
			time_t t = time(NULL);

			struct tm tm = *localtime(&t); //untuk mengambil localtime

			char datestr[100];

			sprintf(datestr, "%d-%02d-%02d_%02d:%02d:%02d",tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec); //untuk print string format tanggal ke variabel datestr

			char path[100] = "/home/angelita/modul2/"; //tempat directory akan dibuat

			strcat(path, datestr); //menggabungkan tempat tujuan dan nama directory yang akan dibuat

			if(child_id < 0)
			{
  				exit(EXIT_FAILURE);
  			}

  			if(child_id == 0)
  			{	
				//membuat directory dengan format yang sudah ditentukan yang disimpan di variabel path
				char *mkdir[] = {"mkdir", "-p", path, NULL}; 
  				execv("/bin/mkdir", mkdir);
  			}	
    			sleep(30); //menunggu 30 detik sebelum membuat folder berikutnya
  		}
		}
	Penjelasan : 
	* Membuat folder
		* child_id = fork(); --> membuat proses
		* struct tm tm = *localtime(&t); --> mengambil local time untuk nama folder nantinya
		* sprintf(datestr, "%d-%02d-%02d_%02d:%02d:%02d",tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec); --> menyimpan isi dari struct tm tm yang berisi localtime dari perangkat ke char datestr dengan format [YYYY-mm-dd_HH:ii:ss]
		* char path[100] = "/home/angelita/modul2/"; --> membuat variabel char path yang berisi alamat dimana folder akan dibuat nantinya
		* strcat(path, datestr); --> menggabungkan path dengan datestr sehingga path akan menyimpan /home/angelita/modul2/[YYYY-mm-dd_HH:ii:ss] sesuai dengan time pada perangkat pada saat dijalankan
		* if(child_id == 0)
  			{	
				char *mkdir[] = {"mkdir", "-p", path, NULL}; 
  				execv("/bin/mkdir", mkdir);
  			}
  		   melakukan make directory dengan menggunakan exec 
	* Menjalankan secara otomatis setiap 30 detik
		* Menggunakan template daemon default dengan sleep(30); untuk membuat program berjalan setiap 30 detik sekali
    b. Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss].
 
    c. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan folder akan di delete(sehingga hanya menyisakan .zip).

    d. Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men- generate sebuah program "killer" yang siap di run(executable) untuk menterminasi semua operasi program tersebut. Setelah di run, program yang menterminasi ini lalu akan mendelete dirinya sendiri.
  
    e. Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen -b. Ketika dijalankan dalam MODE_A, program utama akan langsung menghentikan semua operasinya ketika program killer dijalankan. Untuk MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua folder terisi gambar, terzip lalu di delete).
  
    Kiwa lalu terbangun dan sedih karena menyadari programnya hanya sebuah mimpi.
    Buatlah program dalam mimpi Kiwa jadi nyata!



3. Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan (multiprocessing).

    a. Program buatan jaya harus bisa membuat dua direktori di “/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu lima detik kemudian membuat direktori yang kedua bernama “sedaap”.
    
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
	    	    char *argv[] = {"mkdir", "home/angelita/modul2/indomie", NULL};
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
	    	    char *argv[] = {"mkdir", "home/angelita/modul2/sedaap", NULL};
	    	    execv("/bin/mkdir",argv);
	        }
        
  
    b. Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori “/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak hanya itu tugasnya.
    
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
    		
  
    c. Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan pengelompokan, semua file harus dipindahkan ke “/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke “/home/[USER]/modul2/indomie/”.
  
    d. Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/” harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu 3 detik kemudian membuat file bernama “coba2.txt”. (contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”). 
  
   
