#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "flag.h"


void main( int argc, char ** argv){
	int cmp=1;
	if(argc <= 1){
		printf("aucun fichier a lire ");
		return;
	}
	
	char* current_path= getenv("PWD");

	for(cmp; cmp< argc; cmp++){
		char* path= (char*)malloc( sizeof(char*)*(strlen(current_path) + strlen(argv[cmp])));
		sprintf(path,"%s/%s", current_path, argv[cmp]);
		
	
		printf("***********Fichier******************\n:%s\n*********************************\n",path);
		
		int taille=0;
		id3v2_frame_t* frames = tag_get_frames(path,&taille);
		
		if(frames == NULL){
			printf("aucune frames a lire\n");
		}else{
			int i=0;
			for(i;i<taille;i++){
				affiche_frame(&frames[i]); printf("\n");
			}
			tag_free(frames,taille);
		}
		free(path);
		printf("*********FIN ID3V2*********************\n\n");
	}
}
