#include "flag.h"
#include "read_u.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include <stdlib.h> 
#include <string.h>
// ex 2.4 tp5

id3v2_frame_t *tag_get_frames(const char *file, int *frame_array_size){
	//ouverture du fichier + controle 
	int fd = open(file,O_RDONLY, 0666);
	if(fd == -1 ){
		perror("erreur ouverture fichier");
		return NULL;
	}
	//recuperation du header:
    	id3v2_header_t* head=(id3v2_header_t*)malloc(sizeof(id3v2_header_t));
	if(tag_read_id3_header(fd, head) == -1){
        	close(fd);
		printf("ERREUR HEADER\n");
		return NULL;
	}

	int taille_tab=2;		
	id3v2_frame_t* tab = (id3v2_frame_t*) malloc(sizeof(id3v2_frame_t)*taille_tab);
	
	int i=0;  
	//continus tant qu'il n'y a pas d'erreur dans une frame 
	while( tag_read_one_frame(fd, &tab[i++]) == 0 ){
		if(i == taille_tab-1){
			taille_tab+=2;//
			
			//augmentation de la taille du tableau + verification si realloc OK:
			tab= realloc(tab,sizeof(id3v2_frame_t)*taille_tab );
			if(tab==NULL ){
				return NULL;
			}
		}
	}
	*frame_array_size=--i;

	//fermeture du fichier
	close(fd);	
	return tab;
}

// supprime les frame_count premiere valeur du tableau frames
void tag_free(id3v2_frame_t *frames, int frame_count){
	int i=frame_count;
    id3v2_frame_t* t;
      
    //libere les char* de chaques frames contenus dans le tableau        
    for(i=0;i<frame_count; i++){
//    	printf(" \t efface: "); affiche_frame(frames+i); printf("\n");
	  free(frames[i].text);
    }
    //libere le tableau
    free(frames);
}
