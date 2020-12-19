#include<stdio.h>
#include <math.h>
#include <string.h>
#include "Miller_Rabin.c"
#include "inverse.c"

int p,q;
int n,phi;
int e,d;
char text[1000],decrypt[1000];
unsigned long int cypher[1000];
int sizecount=0;

//Basic Euclidean Algorithm for GCD
int gcd(int a, int b) 
{ 
    if (a == 0) 
        return b; 
    return gcd(b%a, a); 
} 

void generate_keypair(){
	
	jumb:
	system("cls");
	printf("\n-------------------------------------------------------------------------------------");
	printf("\nEnter Two Prime Numbers (Larger Pairs More Secure): ");
	scanf("%d%d",&p,&q);
	if(isPrime(p,4)==0 && isPrime(q,4)==0){
		printf("\nBoth Inputs Not Prime... Please Enter two Prime Numbers!");
		sleep(2);
		goto jumb;
	}else if(isPrime(p,4)==0 || isPrime(q,4)==0){
		printf("\nOne of the Inputs Not Prime... Please Enter two Prime Numbers!");
		sleep(2);
		goto jumb;
	}else if(p*q<33){
		printf("\nPrime Numbers too Small... Please Enter two larger Prime Numbers!");
		sleep(2);
		goto jumb;
	}
	
	printf("\n-------------------------------------------------------------------------------------");
	//n=pq
	n=p*q;
	//Phi is the totient of n
	phi=(p-1)*(q-1);
	
	int style;
	char word0[25]="Generating Key Pairs...";
	printf("\n");
	for(style=0;style<strlen(word0);style++){
		printf("%c",word0[style]);
		usleep(100000);
	}
	
	sleep(1);
	int i;
	do{
		i=rand();
		if(isPrime(i,4)==1 && (i<phi)){
			e = i;
			break;
		}
	}while ((gcd(phi,e) != 1));
	d = modInverse(e, phi);
	
	printf("\n");
	char word1[100]="Please Take Note of the Public and Private Key Pairs: ";
	for(style=0;style<strlen(word1);style++){
		printf("%c",word1[style]);
		usleep(100000);
	}
	sleep(1);
	printf("\n\nEncryption Key (e,n) = (%d,%d)",e,n);
	printf("\nDecryption Key (d,n) = (%d,%d)\n",d,n);
}

int encryption(int e, int n, int text){
	unsigned long int cypher;
	cypher =power(text,e,n);
	return cypher;
}

int decryption(int d, int n, int text){
	unsigned long int decrypt;
	decrypt = power(text,d,n);
	return decrypt;
}
int noofdigits(int a){
	int num=0;
	while(a!=0){
		a/=10;
		num+=1;
	}
	return num;
}
void encryptText(){
	printf("\n-------------------------------------------------------------------------------------");
	int style;
	char word0[25]="Encryption Process...";
	printf("\n");
	for(style=0;style<strlen(word0);style++){
		printf("%c",word0[style]);
		usleep(100000);
	}sleep(1);
	
	unsigned long int x,y;
	printf("\n\nEnter Encryption Key Pairs (e,n): ");
	scanf("%d%d",&x,&y);
	printf("\nEnter Message: ");
	gets(text);
	gets(text);
	
	
	int i=0,temp,tempcyp;
	for (i=0;i<sizeof(text);i++){
		temp=text[i]-'0'+48;

		tempcyp=encryption(x,y,temp);
		//printf("Ascii: %d Tempcyp: %d Size: %d\n\n",temp,tempcyp,noofdigits(tempcyp));
		cypher[i]=tempcyp;
		sizecount++;
		if(text[i+1]=='\0')
			break;
	}
	printf("\nCypher: ");
	for(i=0;i<sizecount;i++)
		printf("%d ",cypher[i]);
}

void decryptText(){
	printf("\n-------------------------------------------------------------------------------------");
	int style;
	char word0[25]="Decryption Process...";
	printf("\n");
	for(style=0;style<strlen(word0);style++){
		printf("%c",word0[style]);
		usleep(100000);
	}sleep(1);
	
	unsigned long int x,y;
	printf("\n\nEnter Decryption Key Pairs (d,n): ");
	scanf("%d%d",&x,&y);
	
	unsigned long int value;
	int i;
	char tempdecyp;
	printf("\nDecypher: ");
	for(i=0;i<sizecount;i++){
		value=decryption(x,y,cypher[i]);
		tempdecyp=(char)value;
		printf("%c",value,tempdecyp);
		}
	printf("\n");
}

void menu(){
	jumb:
	printf("\n-------------------------------------------------------------------------------------");
	printf("\nMenu - Rivest Shamir Adleman (RSA) Encryption");
	printf("\n-------------------------------------------------------------------------------------");
	printf("\n1. Key Pair Generation");
	printf("\n2. Encrypt Text");
	printf("\n3. Decrypt Text");
	printf("\n4. Clear Screen");
	printf("\n5. Exit");
	int menu;
	printf("\n\nEnter your choice: ");
	scanf("%d",&menu);
	switch(menu){
		case 1: generate_keypair();break;
		case 2: encryptText();break;
		case 3: decryptText();break;
		case 4: system("cls");break;
		case 5: exit(0);
		default: printf("\nWrong Input!");
				 sleep(1);
				 goto jumb;
	}
}
	
int main(){
	while(1){
		menu();
	}
	return 0;
}
