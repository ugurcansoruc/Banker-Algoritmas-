#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>

int **pkmax,**pksuan,**pkihtiyac;
int *tkaynak,*tpksuan,*tfark,*ttfark,*processkont,*sonuc,*tmp;
int tkkaydir=2,pkmkaydir=13,toplam=0,t=0,s=1;
int process,kaynak,i,j,k,kontrol,kontrol2=0;

void matrisciz(int,int,int);
void mciz(int,int);
void matrisverial(int,int,int);
void gotoxy(int,int);
void matrisolustur();
void sonucfonk();
void gkki();
void satk();
void kkm();
void yazilar();

int main(int argc, char *argv[]) {

	matrisolustur();
	
	//Sistemdeki her bir kaynagin toplam miktari kýsmýnýn görseli ve verilerinin alýnmasý;
	printf("\n\n-> Sistemdeki her bir kaynagin toplam miktari\n\n ");
	
	mciz(0,7);
	
	tkkaydir=2;
	for(i=0;i<kaynak;i++){
		gotoxy(tkkaydir,7);
		scanf("%d",&tkaynak[i]);
		tkkaydir+=4;
	}
	tkkaydir=2;
	// bitti
	
	//Proseslerin her bir kaynaga olan maksimum ihtiyaçlari
	matrisciz(0,13,1);
	matrisverial(2,13,1);
	//bitti
	
	//Proseslere su an atanmis kaynaklar
	
	matrisciz(50,13,2);
	matrisverial(52,13,2);
	//bitti
	
	//Proseslerin geriye kalan kaynak ihtiyaclar -> gkki
	sleep(1);
    matrisciz(100,13,3);
	gkki();
	//bitti
	
	//Proseslere su an atanmis toplam kaynaklar -> satk
	sleep(1);
	mciz(50,7);
	satk();
	//bitti
	
	//Prosesler tarafindan kullanilmayan kaynak miktarlari -> kkm
	sleep(1);
	mciz(100,7);
	kkm();
	//bitti
	sleep(1);
	sonucfonk();
    
    while(kontrol2==0){
    int prosesno,a;
	gotoxy(0,20);
    printf("-> Lutfen process nosu giriniz             ");
    gotoxy(33,20);
    scanf("%d",&prosesno);
    gotoxy(0,21);
    printf("-> Lutfen process ek kaynak ihtiyaclarýný giriniz            ");
    
	for(i=0;i<kaynak;i++){
		tmp[i]= pksuan[prosesno][i];
		gotoxy(50+i*2,21);
		scanf("%d",&a);
		pksuan[prosesno][i]+=a;
	}
	
    int z = 52;//p=0;
    int p = 13;
    sleep(1);
    for(i=0;i<kaynak;i++){
    	gotoxy(z,p+prosesno);
    	printf("%d",pksuan[prosesno][i]);
    	z+=4;
	}
	sleep(1);
    gkki();
    sleep(1);
    satk();
    sleep(1);
	kkm();
	sleep(1);
	sonucfonk();
	for(i=0;i<kaynak;i++){
		pksuan[prosesno][i]=tmp[i];
	}

	}
    
    
    mfree();
    
	return 0;
}


void matrisolustur(){
	printf("Process sayisi: ");
    scanf("%d", &process);
	
	printf("Kaynak sayisi : ");
    scanf("%d", &kaynak);
	
	pkmax = (int **) calloc(process*2, sizeof(int));
	pksuan = (int **) calloc(process*2, sizeof(int));
	pkihtiyac = (int **) calloc(process*2, sizeof(int));
	
	for(i = 0; i < process*2; i++){
	pkmax[i] = (int *) calloc(kaynak*2, sizeof(int));	
	pksuan[i] = (int *) calloc(kaynak*2, sizeof(int));	
	pkihtiyac[i] = (int *) calloc(kaynak*2, sizeof(int));	
	}
	
	tkaynak = (int *)malloc (kaynak * sizeof(int));  
	tpksuan = (int *)malloc (kaynak * sizeof(int));  
	tfark = (int *)malloc (kaynak * sizeof(int));  
	processkont = (int *)malloc (kaynak * sizeof(int));	
	//sonuc = (int *)malloc (kaynak * sizeof(int));	
	tmp = (int *)malloc (kaynak * sizeof(int));	
	ttfark = (int *)malloc (kaynak * sizeof(int));	

}

void matrisciz(int tkkaydir,int pkmkaydir,int k1){
	
	if(k1==1){
	gotoxy(0,8);
	printf("\n\n->Proseslerin her bir kaynaga olan\n  maksimum ihtiyaclari\n");	
	}
	if(k1==2){
	gotoxy(50,10);
	printf("->Proseslere su an atanmis kaynaklar\n");
	}

	
	for(j=0;j<process;j++){
	gotoxy(tkkaydir,pkmkaydir);
	printf("[");
	for(i=0;i<kaynak;i++){
		printf("    ");
	}
	printf("]");	
		pkmkaydir+=1;	
	}
	
}

void mciz(int tkkaydir,int pkmkaydir){
	
	s = tkkaydir+1;
	
	for(i=0;i<kaynak;i++){
		gotoxy(s,pkmkaydir-1);
		printf(" K%d ",i);
		s+=4;
	}
	
	gotoxy(tkkaydir,pkmkaydir);
	printf("[");
	for(i=0;i<kaynak;i++){
		printf("    ");
	}
	printf("]");
}


void matrisverial(int tkkaydir,int pkmkaydir,int k1){
	s = tkkaydir;
	for(j=0;j<process;j++){
			
	for(i=0;i<kaynak;i++){
		gotoxy(tkkaydir,pkmkaydir);
		
		if(k1==1)scanf("%d",&pkmax[j][i]);	
		if(k1==2)scanf("%d",&pksuan[j][i]);

		tkkaydir+=4;
	}
		pkmkaydir+=1;
		tkkaydir=s;
	}
}
void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}

void mfree(){
	
	for(i = 0; i < process; i++){
	free((void *) pkmax[i]);
	free((void *) pksuan[i]);
	free((void *) pkihtiyac[i]);
	}

    /* dýþtaki dizi boþaltýlýyor */
    free((void *) pkmax);
	free((void *) pksuan);
	free((void *) pkihtiyac);
	free((void *) tkaynak);
	free((void *) tpksuan);
	free((void *) tfark);
	free((void *) processkont);
	free((void *) sonuc);
	
}
void sonucfonk(){
	
	sonuc = (int *)malloc (kaynak * sizeof(int));	

	t=0;

	for(i=0;i<process;i++)
	processkont[i]=0;
	
	
	for(k=0;k<process;k++){
		for(i=0;i<process;i++){
			if(processkont[i]==0){
			
				kontrol=0;
				
				for(j=0;j<kaynak;j++){
					if(pkihtiyac[i][j]>tfark[j]){
						kontrol=1;
						break;
					}
				}
					
				if(kontrol==0){
					sonuc[t++]=i;
					for(j=0;j<kaynak;j++){
						tfark[j]+=pksuan[i][j];
					}
					processkont[i]=1;

				}
				
				
			}
			
		}
	}
	gotoxy(0,25);		
	printf("Sonuc = ");
	gotoxy(8,25);		

	kontrol2=0;
	
	for(i=0;i<process;i++){
		if(ttfark[i]<0){
			kontrol2=1;
			break;
		}
	}
	if(kontrol2==0){
	for (i = 0; i < process - 1; i++)
        printf(" P%d ->", sonuc[i]); 
    	printf(" P%d", sonuc[process - 1]); 
	}
	else{
		printf("Guvenli durum degildir     ");
	}
	
	free(sonuc);
}

void gkki(){
	gotoxy(100,10);
	printf("->Proseslerin geriye kalan kaynak ihtiyaclari\n");
	
	pkmkaydir=13;
	tkkaydir=102;
	for(j=0;j<process;j++){
	
	for(i=0;i<kaynak;i++){
		gotoxy(tkkaydir,pkmkaydir);
		pkihtiyac[j][i]= pkmax[j][i]-pksuan[j][i];
		printf("%d",pkmax[j][i]-pksuan[j][i]);  
		tkkaydir+=4;
	}
		pkmkaydir+=1;
		tkkaydir=102;
	}
}

void satk(){
	
	gotoxy(50,4);
	printf("->Proseslere su an atanmis toplam kaynaklar");
	
	tkkaydir=52;
	for(i=0;i<kaynak;i++){
		for(j=0;j<process;j++){
			toplam+=pksuan[j][i];
		}
		tpksuan[i]=toplam;
		toplam=0;
		gotoxy(tkkaydir,7);
		printf("%d",tpksuan[i]);
		tkkaydir+=4;
	}
}

void kkm(){
	gotoxy(100,4);
	printf("->Prosesler tarafindan kullanilmayan kaynak miktarlari");
	tkkaydir=102;
	for(i=0;i<kaynak;i++){
		tfark[i]=tkaynak[i]-tpksuan[i];
		ttfark[i]=tfark[i];
		gotoxy(tkkaydir,7);
		printf("%d",tfark[i]);
		tkkaydir+=4;
	}
}

