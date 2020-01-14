/* Nama: Lukas Kurnia Jonathan
	NIM : 13517006
	Kelas : K-03
	Deskripsi	: Tubes 1 TBFO TIC TAC TOE
*/

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <stdio.h>

#include "boolean.h"

/*Kamus untuk TICTACTOE*/
#define MaxIsi 9
#define MaxStatus 1
#define MaxNomor 200
#define Alfabet 9
#define BLANK ' '
#define enter '\n'
#define MARK '.'


typedef struct{
	char isi[MaxIsi+1]; // isi berupa string dari sebuah states
	char status; //status apakah win, draw, or not final state dari sebuah states
}info ;

typedef struct{
	info nama[MaxNomor+1]; //nama states
}states;


typedef struct{
	int tabel[MaxNomor+1][Alfabet+1]; //matriks berisi transition table
} transition;


#define StateInfo(S,i,j) (S).nama[(i)].isi[(j)]  //Isi data dari states S
#define Kondisi(S,i) (S).nama[(i)].status // Kondisi dari state S, apakah win, draw, atau not final state
#define Transisi(T,i,j) (T).tabel[(i)][(j)] // melihat isi tabel transisi, digunakan untuk melihat next state setelah iput dari user.



 /* State Mesin Karakter untuk membaca file external */
/*================================================================================*/
extern char CC; //current character
extern boolean EOP; //bernilai true jika sudah di akhir file, yaitu CC = Mark

void START();
 /*Mesin siap dioperasikan. Pita(file) disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita(file).
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita(file)
          Jika CC = MARK maka EOP(true)*/

void ADV();
/* Pita(file) dimajukan satu karakter. 
   I.S. : Karakter lama = CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama, 
          CC mungkin = MARK
          Jika  CC = MARK maka EOP (true) */

/* State Mesin Kata untuk membaca file external */
/*=================================================================================*/
typedef struct {
	char TabKata[50];  //container penyimpan kata, indeks yang dipakai [0..50] 
    int Length; //panjang kata yang diakuisisi
} Kata;

/* State Mesin Kata */
extern boolean EndKata;
extern Kata CKata;

void IgnoreBlankEnter();
/* Mengabaikan satu atau beberapa BLANK dan enter
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC ≠ enter atau CC = MARK */

 void STARTKATA(int i);
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVKATA();
 /*I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void SalinKata();
/* Mengakuisisi kata, menyimpan dalam typedata yang sudah tersedia
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK atau CC= enter; 
          Data terisi
          */
void IsiData(states *S, transition *T, int file);
/* I.S : Tabel Transisi dan States belum terisi
	F.S: Tabel Transisi dan States sudah terisi dengan bantuan mesin kata dan karakter
*/

/*Kumpulan Fungsi dan Prosedur selama permainan berlangsung*/
void TulisPapan (states S,int i);
/*I.S : states terdefinisi, i merupakan nomor states
	F.S : Menuliskan states ke layar dengan format papan tictactoe */

states MakeFirstState (states S);
/* I.S : S  sembarang
	F.S : S  diisi dengan kondisi pertama (q0)*/

void TulisStatesDilewati(int S[10],int neff);
/*I.S : Array S terdefinisi 
 F.S : Menuliskan isi array ke layar dari indeks ke 1 sampai neff*/

void CopyStatesInfo(states S, states *newS,int i);
/*I.S : S terdefinisi
 F.S : newS adalah salinan dari S dengan nomor states i
*/

boolean IsInputValid(states S,int now, int input);
/*Mengirimkan true jika input bisa diisi(slot masih kosong,belum ada X atau O)*/

void Update(states *CState, states S, transition T, int input, int* now);
/*I.S: S dan T terdefinisi, input adalah alfabet masukkan user, now adalah nomor states
F.S : CState terupdate sesuai input dan now dari data S dan T 
      now terupdate sesuai tabel transisi
*/

void UpdateCopyState(states *CopyCState,int now, int input);
/*I.S: CopyCState sudah terdefinisi
 F.S: Mengganti indeks input dari CopyCState dengan sebuah 'X'
*/
boolean IsFull (states CState,int now);
/* mengirimkan true jika CState penuh(sudah penuh terisi X dan O)*/

#endif