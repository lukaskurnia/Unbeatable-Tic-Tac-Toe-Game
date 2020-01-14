/* Nama: Lukas Kurnia Jonathan
	NIM : 13517006
	Kelas : K-03
	Deskripsi	: Tubes 1 TBFO TIC TAC TOE
*/

#include "tictactoe.h"
#include <stdio.h>


int main() 
{
	/*Kamus*/
	int i,j;
	int giliran; // input user untuk menentukan player or computer first
	int now,input; //now untuk mengetahui state berapa, input untuk melihat masukkan dari user;
	int neff; // jumlah neff array untuk menuliskan states yang dilalui
	int tryagain; // untuk command replay game
	int testpenuh; // penanda untuk menyalin papan tictactoe dari computer.
	transition T;
	states S,CState,CopyCState;
	int StatesDilewati[10];
	boolean MainLagi; // true jika user ingin bermain lagi.

	/*Algoritma*/
	MainLagi=true;
	while(MainLagi)
	{
		MainLagi=false;
			printf("=========================================\n");
			printf("Selamat Datang di permainan TIC  TAC TOE\n");
			printf("Selamat bermain !!\n");
			printf("credit: Lukas Kurnia Jonathan / 13517006\n");
			printf("=========================================\n\n");
			printf("Cara Bermain: Masukkan angka 1 - 9 ke layar untuk meletakkan simbol 'X'\n");
			printf("Catatan: Pada awal permainan, anda hanya bisa memulai dari tengah papan. yaitu input '5'\n");
			printf("Untuk memulai permainan, silakan ketik:\n");
			printf("	'1' untuk Player First\n");
			printf("	'2' untuk Computer First\n");
		 	
		 	do
			  {
			  	printf("Pilih mode: ");
				   scanf("%d",&giliran); // memilih computer or player first
				   if(giliran != 1 && giliran != 2)
				    {
				      printf("Maaf, hanya bisa memasukkan '1' atau '2' , silakan coba lagi\n");
				    }

				  }
			 while((giliran != 1) && (giliran != 2));

			IsiData(&S,&T,giliran); //Mengisi Matriks dan Array dari fle eksternal

			now =0;
			neff=1;
			StatesDilewati[neff] = 0; // nomor states mula mula disimpan di array
			CState = MakeFirstState(S); // membuat Current State

			while(Kondisi(CState,now) != 'd' && Kondisi(CState,now) !='w')
			{
				if(giliran == 1) // (Player duluan)
				{
				

					if(now==0) //Hanya dilakukan ketika turn pertama
					{
					printf("Giliran Anda !! Pada giliran pertama ini Anda hanya boleh memasukkan angka 5\n");
					printf("Masukkan angka: ");
					scanf("%d",&input);
						if (input < 1 || input > 9)
							{
								printf("Maaf, input hanya 1-9. Anda hanya bisa memasukkan angka 5. Sistem otomatis mengganti menjadi angka 5. \n");
								input=5;
							}
						else if(input != 5 )
							{
								printf("Maaf, Anda hanya bisa memasukkan angka 5. Sistem otomatis mengganti menjadi angka 5. \n");
								input=5;
							}
					}
					else //now > 0 , turn kedua dan seterusnya
					{
						do
						{
							printf("Masukkan angka: ");
							scanf("%d",&input);
							if(!IsInputValid(S,now,input))
								{	
									printf("Sudah diisi/input salah, silakan pilih angka lain\n");}
						}
						while(!IsInputValid(S,now,input));
					}
				}
				else //giliran ==2 (Komputer duluan)
				{
					if(now==0) // hanya dilakukan ketika turn pertama
						{
							printf("Komputer Terlebih dahulu!\n");
							printf("Giliran Komputer: \n");
							TulisPapan(CState,now);
							do
							{
								printf("Masukkan angka: ");
								scanf("%d",&input);
								if(!IsInputValid(S,now,input))
									{	
										printf("Sudah diisi/input salah, silakan pilih angka lain\n");}
							}
							while(!IsInputValid(S,now,input));
						}
						
					else //now >0 , turn kedua dan seterusnya
					{
						do
							{
								printf("Masukkan angka: ");
								scanf("%d",&input);
								if(!IsInputValid(S,now,input))
									{	
										printf("Sudah diisi/input salah, silakan pilih angka lain\n");}
							}
							while(!IsInputValid(S,now,input));
					}
				}



					printf("Giliran Anda: \n");
					CopyStatesInfo(CState,&CopyCState,now); 
					UpdateCopyState(&CopyCState,now,input);
					TulisPapan(CopyCState,now); //menuliskan papan tictactoe setelah dimasukkan user
					testpenuh=now;

					
					Update(&CState,S,T,input,&now);
					neff+=1;
					StatesDilewati[neff] = now;
					if(!IsFull(CopyCState,testpenuh))
					{
						printf("Giliran Komputer: \n");
						TulisPapan(CState,now); //menuliskan papan tictactoe setelah giliran computer
					}

				
				
			}// Kondisi(CState,now) == 'd' || Kondisi(CState,now) == 'f'
			if(Kondisi(CState,now)== 'd')
			{
				printf("Game Seri ! Terimakasih sudah bermain :)\n");
			}
			else // Kondisi(CState,now) == 'f'
			{
				printf("Anda kalah! Komputer Anda tidak dapat dikalahkan ! \n");
			}
			TulisStatesDilewati(StatesDilewati,neff); //menampilkan ke layar states yang sudah dilalui selama permainan.
			printf("\n");
			
			do
			{
				printf("Try Again? Write '1' for play again. '0' for end the game\n");
				scanf("%d",&tryagain);
				if(tryagain!=1 && tryagain!=0)
					{printf("Perintah Salah\n");}
			}
			while(tryagain!=1 && tryagain!=0);

			if(tryagain == 1)
			{
				MainLagi=true;
			}
		}
	return 0;
}

