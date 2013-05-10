#include "flag.h"
#include "read_u.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include <stdlib.h> 
#include <string.h>


void test_convert(int *fd){
	printf("\n==========essais convert=========\n");
		u32* h = (u32*) malloc(sizeof(u32));
		*h = 0x6d776e6e ; 
    	

    	affiche_u32(h);
		aff_bin((u8*)h);	 printf("\n"); 
	
	    *h=	convert_size(*h);
		aff_bin((u8*)h); printf("\n"); 
	printf("\n=========fin convert===========\n");

}
void test_read_string(int *fd){
	printf("\n=========essais read ===========\n");			
		char* rs = (char*)malloc(sizeof(char)*9);
		read_string(*fd,rs,11,1);
		//char* sr=NULL;
		//sr=read_string(fd,sr,4,1);
		printf("resultat: %s",rs);
	printf("\n=========fin read ===========\n");

}


void test_idv3(int *fd){

	printf("\n=========essais read tag ===========\n");
        id3v2_header_t *header;
        header = (id3v2_header_t*)malloc(sizeof( id3v2_header_t));
        printf("retour fonction: %d" , tag_read_id3_header(*fd,header));
      
        affiche_header(header);
	printf("\n===================================\n");			

}
/*
	$XX XX XX XX \0-> ID
	$XX XX XX XX  -> SIZE
	$XX XX-> FLAGS
	$XX -> Encodage ISO
	$XXX XXX XXX TEXTE
*/
void test_frame(int *fd){
	printf("\n=========essais read fra ===========\n");
		id3v2_frame_t* frame = (id3v2_frame_t*)malloc(sizeof(id3v2_frame_t)); 

       if(tag_read_one_frame(*fd,frame) != -1)
			affiche_frame(frame);
	printf("\n====================================\n");			
}
void main(int argc ,char * argv[]){

		
  	//const char* path="/home/infoetu/delmottf/Documents/ASR/C/TP5/x2.mp3";  
	

/*		 //open
		int fd = open(path,O_RDONLY,0666);
       // int fd = open("/home/infoetu/delmottf/Documents/ASR/C/TP5/x.mp3",O_RDONLY,0666);
		if(fd == -1){
    		printf("erreur ouverture\n");
    		exit(15);
        }
		printf("ouverture fichier réussi\n");
//**/
     //   test_convert(&fd);   
     //  test_read_string(&fd);
                    	
//       /* 
       
	//	char* bpath="/home/marms/Documents/asr/c/tp5/mp3s/00000.mp3";
		char* bpath="/home/infoetu/delmottf/Documents/ASR/C/tp5/mp3s/00000.mp3"; 
		char* path;
		if(argc > 1){
	 		path = argv[1];
			printf("\n%s \n",path);		
	  	}else
	  		path= bpath;
  		
       int* taille= (int*)malloc(sizeof(int));
       *taille=0;

		//recuperation du tableau de frames
        id3v2_frame_t* frame = tag_get_frames(path,taille);
        if(frame == NULL){
         	printf("======== ERREUR FICHIER MP3 ======\n"); 
         	exit(0);
        }
        
        printf("*\n\n============ RESULTAT ===========\n");
		int i= 0;

		//affichage du tableau de frame 
        for(i; i < *taille ;i++){
        	affiche_frame(&frame[i]);
        	printf(" \n");
        }
		
		//libere le tableau de frame 
        tag_free(frame, *taille);
        i= 0;
/**/
        //fermeture fichier
        //close(fd);
}

