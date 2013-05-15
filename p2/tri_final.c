#include <stdlib.h>
#include <stdio.h>
#include "header.h"
#include "../p1/flag.h"
#include <string.h>

//a quoi sert size??
const char *get_file_name(char *buffer, int size, const sort_info_t *info, const char *ext){
	snprintf(buffer,size,"%s.%s",info->titre,ext);
	return buffer;
}

int sort_file(const char* root_folder,const char* source_file){
	//VERIF QUE LE FICHIER SOURCE_FILE EST BIEN UN MP3
	if(strcmp(get_file_extension(source_file),".mp3")!=0)
		return -1;
	//RECUPERATION DES INFO ID3V2
	sort_info_t* info= (sort_info_t*) malloc (sizeof(sort_info_t));
	if(!info){
		perror(" sort_file: erreur alloc mem sort_info_t\n");
		return -1;
	}
	get_file_info(source_file,info);
	//verification des info
	if(!info->titre || !info->album || !info->numero || !info->genre ||  !info->artiste )
		return -1;

	//CREATION DES CHAINE DE CARAC CONTENANT LES CHEMINS VERS ARTIST , GENRE +FILE_NAME 
	// declaration des variables: 
	int taille=(strlen(root_folder) + strlen(info->artiste)*2 + strlen(info->album) + 1);//pk du rajouter 1??
	int size_artist= taille+ strlen("by_artist/L// - /l") , size_genre = taille+ strlen("by_genre/// - /mel/");// pk du rajouter des lettre??
	int size_file_name= (5 + strlen(info->titre));// verifier si il faut compter le caractere de fin ?

	//allocation memoire buffers
	char* buffer_genre=(char*)malloc(sizeof(char)*(size_genre+size_file_name));
	char* buffer_artist=(char*)malloc(sizeof(char)*(size_artist+size_file_name));
	char* file_name= (char*) malloc( sizeof( char) * size_file_name);
	//initiation
	get_genre_folder(buffer_genre , size_genre , root_folder , info) ;
	get_artist_folder(buffer_artist , size_artist , root_folder , info);
	get_file_name(file_name, size_file_name , info, get_file_extension(source_file));
	
	//CREATION DES ARBRE SI NECESSAIRE si fonction invalide source invalide ???
	create_tree(buffer_genre);
	create_tree(buffer_artist);

	//ajout du file_name au buffers
	sprintf(buffer_genre,"%s%s",buffer_genre,file_name);
	sprintf(buffer_artist,"%s%s",buffer_artist,file_name);
	//printf("buffer genre: %s\n buffer artist %s\n file name: %s\n",buffer_genre, buffer_artist, file_name);

	//CREATION DES LIEN DS LES REPERTOIRE + SUPPRESSION DU SOURCE	
	if(!link(source_file,buffer_genre) && !link(source_file,buffer_artist)){
		printf("ok\n");
//		unlink(source_file);
	}
	free(buffer_genre);
	free(buffer_artist);
	free(file_name);
	free(info);
	return 0;
}
