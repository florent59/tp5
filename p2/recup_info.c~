#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "../p1/flag.h"


/**	TALB album TPE1 artiste	TCON genre	TIT2 titre	TRCK numero	TYER ?? */
int get_file_info(const char *source_file, sort_info_t *info){
	int  taille= 0;
	id3v2_frame_t* frames= tag_get_frames(source_file,&taille);
	//si il y a une erreur dans le tag_get_frames(…)
	if(!frames)
		return -1;
	
	int i;
	for(i=0;i<taille;i++){
		char* src= frames[i].text;
		char* dest = (char*) malloc( sizeof( char) * strlen(src));

		// attribution de la destination dans le champ
		// de la structure sort_info_t correspondant:
		if(strcmp( frames[i].id , "TPE1")==0){
			info->artiste=dest;
		}else if( strcmp(frames[i].id , "TALB")==0){
			info->album=dest;
		}else if( strcmp(frames[i].id , "TIT2")==0){
			info->titre=dest;
		}else if( strcmp(frames[i].id , "TCON")==0){
			info->genre=dest;
		}else if( strcmp(frames[i].id , "TRCK")==0){
			info->numero=dest;
		}else{
			printf("def\n");
		}

		//verif malloc :
		if(!dest)
			return 0;
		//copy + nettoyage de la chaine de caractere	
		clean_string( strcpy( dest , src ) );
	}
	
	//suppression de l'espace allouer inutile: 
	tag_free( frames , taille );
	
	//retourne le nombre total de caractere lu pour simplifier 
	return 0;
}

// methode utilitaire pour afficher un sort_info_t* ne sert plus que dans le main
void affiche_info(sort_info_t* t){
	printf("album:%s \nartiste: %s\ngenre: %s\ntitre: %s\nnumero: %s\n",
	 t->album, t->artiste, t->genre, t->titre, t->numero);
}

