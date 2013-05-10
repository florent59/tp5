#include "header.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
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
		printf("n'est pas un dossier\n");
		sort_file(root,source);			
	}
}

void trait_DIR(char* source,char* root){
//	printf("%s pwd: :  \n",getenv("PWD"));
//	DIR* dir = (DIR*) malloc(sizeof(DIR));
//	if(!dir)return;
	//ouvrir fichier 
	DIR* dir=opendir(source);
	if(!dir)
		printf(" ERROR trait_DIR\n");
	//tant que fichier non vide 
	struct dirent* dossier= (struct dirent*) malloc(sizeof(struct dirent));
	dossier=readdir(dir);
	while(dossier!=NULL){
		printf("result:  %s\n",dossier->d_name);
		//allocation du chemin du source 
		traitement(root,dossier->d_name);
		dossier=readdir(dir);		
	}
	//fermer fichier
	closedir(dir);
}

