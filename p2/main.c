#include "header.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h> // DIR opendir readdir closedir… 

void traitement(char* root, char* source);
void trait_DIR(char* source,char* root);

void main(int argc, char**argv){
	if(argc <= 1)
		printf("rien a faire\n");
	
	char* root_folder=argv[1];
	int cmp=2;
	for(cmp; cmp<argc; cmp++){
		//verif que le fichier exist:
		if(!access(argv[cmp],F_OK)){
			printf("fichier exist\n");	
			traitement(root_folder,argv[cmp]);
		}else
			printf("fichier inexiste\n");
	}
}
void traitement(char* root, char* source){
	struct stat* fichier = (struct stat*) malloc (sizeof(struct stat));
	stat(source,fichier);
	if(S_ISDIR(fichier->st_mode )){
		printf("est un repertoire \n");
		trait_DIR(source,root);
	}else{
	//	printf("n'est pas un dossier\n");
		sort_file(root,source);			
	}
}

char* path(char*,char*);

void trait_DIR(char* source,char* root){
	//ouvrir fichier 
	DIR* dir=opendir(source);
	if(!dir)
		printf(" ERROR trait_DIR\n");
	//tant que fichier non vide 
	struct dirent* fichier= (struct dirent*) malloc(sizeof(struct dirent));
	fichier=readdir(dir);
	while(fichier!=NULL){
		//si le fichier n'est pas caché ou si fichier './' '../'
		if(fichier->d_name[0] != '.'){
			//allocation du chemin du source 
			char* chemin= path(source,fichier->d_name);		
			printf("chemin :%s\n",chemin);
			traitement(root,chemin);
			free(chemin);
		}
			fichier=readdir(dir);		
	}
	//fermer fichier
	closedir(dir);
}

//allou un char* de taille suffisante et renvois la chaine "source/nom" 
char* path(char* source,char* nom){
	int taille = strlen(source)+strlen(nom)+2;
	char* path= (char*)malloc(sizeof(char)*taille);
	sprintf(path,"%s/%s",source,nom);
	return path;	
}

