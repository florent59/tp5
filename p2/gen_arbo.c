#include "header.h"
#include <stdlib.h> //malloc
#include <string.h>
#include <stdio.h> // printf
#include <sys/stat.h>//stat mkdir 
#include <sys/types.h>//stat mkdir
#include <unistd.h>//stat access 


/*size: taille du buffer 
 buffer: chaine de caractere representant le répertoire dans lequel le fichier dont les infos données par la structure info sera stocké
*/
//root_folder/By_Artit/Lettre/artiste/artist - album/
const char *get_artist_folder(char *buffer, int size, const char *root_folder, const sort_info_t *info){
        snprintf(buffer,size,"%sBy_artiste/%c/%s/%s - %s/",root_folder,(info->artiste)[0],info->artiste,info->artiste,info->album);
        return buffer;
}

//root_folder/By_Genre/genre/artiste/artiste - album/
const char *get_genre_folder(char *buffer, int size, const char *root_folder, const sort_info_t *info){
        snprintf(buffer,size,"%sBy_Genre/%s/%s/%s - %s/",root_folder,info->genre,info->artiste,info->artiste, info->album);

        return buffer;
}


int check_and_create_folder(const char *path){
        //creation du repertoire si le fichier n'existe pas:
        if(access(path,F_OK) != 0){
 //               printf("creation du repertoire\n");
                mkdir(path, 0777);
                return 0;
        }

        //allocation de la structure qui contiendra les infos sur notre path
        struct stat* etat_fichier=(struct stat*)malloc(sizeof( struct stat));
        if(!etat_fichier)
                perror("erreur alloc mem strut stat\n");
        //ecriture des info dans la structure
        if(stat(path,etat_fichier)==-1){
                perror("erreur stat");
                return -1;
        }
        //verification que notre fichier est bien un repertoire sinon erreur:
        if(!(S_ISDIR(etat_fichier->st_mode))){
                printf("fichier du meme non existe\n");
                return -1;
        }

	//verification que l'utilisateur dispose des droit rwx sinon erreur:
      if(!etat_fichier->st_mode & S_IRWXU == 00700){
                printf("erreur droit usr rwx \n");
		return -1;
      }
  /*      if(etat_fichier->st_mode & S_IRWXG == 00070)
        if(etat_fichier->st_mode & S_IRWXO == 00007)
*/
        return 0;
}

int create_tree(const char *fullpath){
        int index=0;
        int i=1;
        char* next=fullpath;
        char* path=(char*)malloc(sizeof(char)*strlen(fullpath)) ;

        int continu=1;
	while(continu){
		while(( fullpath[i] != '/' && fullpath[i]!='\0'))
			i++;
		if(fullpath[i]=='\0')
			continu=0;
		else
			i++;
		
		path= strncpy(path,fullpath,i);
//              printf("%d nouvo path: %s\n",i,path);
                if(check_and_create_folder(path)==-1)
                        return -1;
      }
       
        return 0;
}
