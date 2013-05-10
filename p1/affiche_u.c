#include "flag.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//permute quatre octets deux par deux 
void permut4(u32* x){
 *x= (*x>>16) | (*x<<16) ;
}
//permute deux octets 
void permut2(u16* x){
	*x= (*x>>8) | (*x<<8) ;
}

//afficle les nbOctet caractere acsi des  
void aff_carac(void* t, int nb){
	int i= 0;
	u8* d = (u8*)t;
	for(i;i<nb; i++)
		printf("%c",*(d+(sizeof(u8)*i)));	
}

void affiche_u8(u8* d){
    printf("vdec:%d carac: ",*d);
    aff_carac(d,1);
    printf(" hexa: %0X\n",*d);
}

void affiche_u16(u16* d){
    printf("vdec:%d carac: ",*d  );
    aff_carac(d,2); printf(" hexa: %0X\n",*d); 
}

void affiche_u32(u32* d){
  printf("vdec:%d carac: ",*d  );
    aff_carac(d,4); printf(" hexa: %0X\n",*d); 
}


void affiche_bin(u8* u){
	short tmp = (short)*u;
	int i=0;
	for(i=128;i>0; i/=2){
		if( (tmp - i) >= 0){
			printf("1");
			tmp-=i;
		}else 
			printf("0");
	}
}
void aff_bin(u8* u,int nb){
	int i=3;
	for(i;i>=0;i--){
		affiche_bin(&u[i]);printf(" ");
	}
}
void affiche_header(id3v2_header_t* header){
	printf("\n\"%s\"| version %x |flags %0x	 |size %d |\n",header->ID3, header->version ,header->flags, header->size);
}

void affiche_frame(id3v2_frame_t* frame){
	printf("id: %s, size %d flag : %0x text \"%s\"",frame->id,frame->size,frame->flags,frame->text);
//	printf("id%d : %s, size %d flag %d : %0x text %d \"%s\"",*frame->id ,frame->id,frame->size,&frame->flags,frame->flags, &frame->text ,frame->text);
}
