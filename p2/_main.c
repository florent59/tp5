#include "../p1/flag.h"
#include "header.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



void main(){
//Q1
  /*      char* s= (char*)malloc(sizeof(char)*10);
        s[0]='a';s[1]='a';s[02]='a';s[03]='/';s[04]='s';s[5]='/';s[6]='.';s[7]='p';s[8]='3';;s[9]='\0';
        printf("%s\n",s);
        printf("essais get_file_extension: %s\n", get_file_extension(s));
        clean_string(s);
        printf("essais clean_string: %s\n\n", s);
**/
// TEST 2.2 Q2

        char* path="/home/marms/Documents/asr/c/tp5/mp3s/00000.mp3";
        sort_info_t t;
        get_file_info(path,&t);
        affiche_info(&t);
// TEST 3.3 Q1
        const char* root_folder="/home/marms/Documents/asr/c/tp5/root_folder/";
        //Q1 CLASSEMENT PAR ARTISTE

        int size=strlen((&t)->artiste)*2 + strlen((&t)->album)+ sizeof(char)+ strlen("by_artiste//// - ")+strlen(root_folder)+sizeof(char);
//        printf("taille: %d\n\n",size);
 
        char* buffer= (char*)malloc(size * sizeof(char));
 /*       get_artist_folder(buffer,size,root_folder,&t);
        printf("%s \n\n",buffer);

        //Q2 CLASSEMENT PAR GENRE
//        size=strlen((&t)->genre) + strlen( (&t)->artiste)*2  + strlen((&t)->album) + strlen(root_folder) + strlen("by_genre/// - /")+sizeof(char);
        printf("taille: %d\n\n",size);
        get_genre_folder(buffer,size,root_folder,&t);
        printf("%s \n",buffer);
*/
        //Q3 CHECK 
   //     check_and_create_folder(root_folder);
//      sprintf(buffer,"%s/este",root_folder);
//      check_and_create_folder(buffer);        

        //Q4 CREATION ARBORESCENCE
     //   create_tree(buffer);
	//EX 2.4
	//Q2
	sort_file(root_folder, path);
	

}
