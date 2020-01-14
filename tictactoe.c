/* Nama: Lukas Kurnia Jonathan
  NIM : 13517006
  Kelas : K-03
  Deskripsi : Tubes 1 TBFO TIC TAC TOE
*/


#include <stdio.h>
#include "tictactoe.h"

char CC;
boolean EndKata;
boolean EOP;
Kata CKata;

static FILE *filetransisi;
static int retval;

void START(int i) {
 /*Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : i dipastikan 1 atau 2
   F.S. : CC adalah karakter pertama pada pita(file). Jika CC != MARK maka EOP akan padam (false).
          Jika CC = MARK maka EOP akan menyala (true) */

	/* Algoritma */
  if(i==1) //jika player duluan yang bermain
        {
          filetransisi = fopen("playerstates.txt","r");
          ADV();
        }
	 if(i==2) // jika computer duluan yang bermain
        {
          filetransisi = fopen("computerstates.txt","r");
          ADV();
        }
  }

void ADV() {
 /*Pita dimajukan satu karakter. 
   I.S. : Karakter pada jendela = 
          CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama, 
          CC mungkin = MARK.
		  Jika  CC = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	retval = fscanf(filetransisi,"%c",&CC);
	EOP = (CC == MARK);
	if (EOP) {
       fclose(filetransisi);
 	}
}

void IgnoreBlankEnter()
/* Mengabaikan satu atau beberapa BLANK dan enter
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC ≠ enter atau CC = MARK */
{
  while((CC == BLANK || CC == enter) && CC != MARK)
  {
    ADV();
  }
}

 void STARTKATA(int i)
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
 {
  START(i);
  IgnoreBlankEnter();
  if(CC== MARK)
    {EndKata = true;}
  else
    {
      EndKata = false;
      SalinKata();
    }
 }

void ADVKATA()
 /*I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EOP = true.     
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{
  IgnoreBlankEnter();
  if(CC == MARK)
    {EndKata = true;}
  else
    {SalinKata();}
}


 void SalinKata()
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK atau CC = enter; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
  */
{ 
/* Kamus Lokal */
  int i = 1; /* inisialisasi */
  /* Algoritma*/
    for (;;) {
      CKata.TabKata[i] = CC;
      ADV();
      if ((CC == MARK) ||(CC==enter) || (CC == BLANK)) 
      {
        break;
      } 
      else 
      {
        i++;
      }
    } /* CC = MARK or CC = BLANK or CC = enter*/
  CKata.Length = i;
  if(!EOP)
  {
    IgnoreBlankEnter();
  }
}

void IsiData(states *S, transition *T,int file)
/* I.S : Tabel Transisi dan States belum terisi
  F.S: Tabel Transisi dan States sudah terisi dengan bantuan mesin kata dan karakter
*/
{
  /*Kamus*/

  int tipe; //Untuk memisahkan array atau matriks yang akan diisi oleh data di kolom pada file eksternal 
  int nomor; //penanda nomor states
  int temp;
  int i,j;
  /*Algoritma*/

 

  tipe =1;
  j=1;
  nomor = 0;

  STARTKATA(file);
  
  while(!EOP)
  {
    if(tipe == 1) // kolom ke 1 pada file eksternal diproses, mengisi Matriks StateInfo
    {
      for(i=1 ; i<= CKata.Length ; i++)
      {
        StateInfo(*S,nomor,i) = CKata.TabKata[i];
      }

      if(tipe > 10)
      {
        tipe=1;
        nomor+=1;
      }
      else
        {tipe+=1;}
    }

    else if(tipe == 2) // kolom ke 2 pada file eksternal diproses, mengisi array Kondisi
    {
      Kondisi(*S,nomor) = CKata.TabKata[1];
      if(tipe > 10)
      {
        tipe=1;
        nomor+=1;
      }
      else
        {tipe+=1;}
    }
    else if(tipe > 2 && tipe <=11) // kolom ke 3 sampai 11 pada file eksternal diproses, mengisi matriks Transisi
    {
      temp=0;
      for(i=1; i<= CKata.Length ; i++)
      {
        
        temp = temp*10 + (CKata.TabKata[i] - '0'); 
      }
      Transisi(*T,nomor,j) = temp;
      
      if(tipe > 10)
      {
        tipe=1;
        nomor+=1;
        j=1;
      }
      else
        {
          tipe+=1;
          j+=1;
        }
    }
      ADVKATA();
  }
}
/*================================================================*/
/*Kumpulan Fungsi dan Prosedur selama permainan berlangsung*/
void TulisPapan (states S,int i)
/*I.S : states terdefinisi
	F.S : Menuliskan states ke layar dengan format papan tictactoe */
{
	/*Kamus*/
	int count;
	int j;

	/*Algoritma*/
	count=0;
	for (int j = 1; j<= 9 ; j++)
	{
		if(StateInfo(S,i,j)=='-')
		{
			printf("   ");
		}
		else
		{
			printf(" %c ",StateInfo(S,i,j));
		}
		count+=1;
		if(count <3)
		{
			printf("|");
		}
		else //count = 3
		{
			printf("\n");
			count=0;
		}
	}
}

void TulisStatesDilewati(int S[10],int neff)
/*I.S : Array terdefinisi 
 F.S : Menuliskan isi array ke layar dari indeks ke 1 sampai neff*/
{
	printf("States yang dilewati: ");
		for(int i=1 ; i<= neff;i++)
		{
			
			printf("q%d ",S[i]);
		}
		printf("\n");
}

/*==============================*/
/*Konstruktor*/
states MakeFirstState (states S)
/* I.S : S  sembarang
	F.S : S  diisi dengan kondisi pertama (q0)*/
{
	/*Kamus*/
		int i=0;
		states S1;
	/*Algoritma*/
		for(int j=1;j<=9;j++)
		{
			StateInfo(S1,i,j)= StateInfo(S,i,j);
		}
		Kondisi(S1,i) = Kondisi(S,i);
		return S1;
}
/*===============================================*/

void CopyStatesInfo(states S, states *newS, int i)
/*I.S : S terdefinisi
 F.S : newS adalah salinan dari S dengan nomor states i
*/
{
  for (int j = 1 ; j<=9 ; j++)
  {
    StateInfo(*newS,i,j) = StateInfo(S,i,j);
  }
}

void Update(states *CState, states S, transition T, int input, int* now)
/*I.S: S dan T terdefinisi, input adalah alfabet masukkan user, now adalah nomor states
F.S : CState terupdate sesuai input dan now dari data S dan T 
      now terupdate sesuai tabel transisi
*/

{
  /*Kamus*/

  /*Algoritma*/
  *now= Transisi(T,*now,input);
  for(int j=1;j<=9;j++)
  { 
    StateInfo(*CState,*now,j) = StateInfo(S,*now,j);
  }
  Kondisi(*CState,*now) = Kondisi(S,*now);
}

boolean IsInputValid(states S,int now, int input)
/*Mengirimkan true jika input masih bisa diisi(slot masih ada yang kosong,belum ada X atau O)*/
{
  return (StateInfo(S,now,input) =='-')&& (input >=1 && input<=9) ;
}

void UpdateCopyState(states *CopyCState,int now,int input)
/*I.S: CopyCState sudah terdefinisi
 F.S: Mengganti indeks input dari CopyCState dengan sebuah 'X'
*/

{
  StateInfo(*CopyCState,now,input) = 'X';
}

boolean IsFull (states CState,int now)
/* mengirimkan true jika CState penuh(sudah penuh terisi X dan O)*/
{
  int i;
  boolean penuh;

  penuh=true;
  i=1;
  while(i<=9 && penuh)
  {
    if(StateInfo(CState,now,i) == '-')
      {penuh=false;}
    else
      {i++;}
  }
  return penuh;
}