#include "flag.h"
#include "read_u.h"
#include <sys/types.h>
#include <sys/stat.h>
	
#include <fcntl.h>
#include <stdio.h>
	
#include <stdlib.h> 
#include <string.h>
	
#include <unistd.h> // pour lseek
	
	
 /* 
$XX XX XX char ID3[4]
$XX XX u16  version
$XX   u8   flags
$XX XX XX XX  u32  size
*/	
int tag_read_id3_header(int fd, id3v2_header_t *header){
	u8 verif = 0x01;

    read_string(fd,header->ID3,4 ,0); // possibilité que sa ne fonctionne pas sur d'autre machine ???

    verif &= read_u16(fd,&(header->version)); 
    verif &= read_u8(fd,&(header->flags)); 
    verif &= read_u32(fd,&(header->size)); 
    
     //suppression des 4 bits de poid fort   
    header->size = convert_size(header->size);
	
	// verif a verifier
	if( !verif ||  strcmp("ID3",header->ID3) ||  header->version >0x0300 )
		return -1;
	return 0;
}		
	
/*	
	$XX XX XX XX \0 ID
	$XX XX XX XX   SIZE
	$XX XX FLAGS
	$XX Encodage ISO
	$XXX XXX XXX TEXTE
*/
int tag_read_one_frame(int fd, id3v2_frame_t *frame){
	if(fd==-1)
		return -1; 
// voir si mettre les valeurs dans une variable tmp ??
    char* valide ; u8 encodage; 
	u8 verif=0X01;
	
    	valide=read_string(fd,frame->id,5,0);
	verif&=	read_u32(fd,&(frame->size));	
	if(*valide==NULL)
		return -1;
	    /* si id ne commence pas par T ou bien si id == TXXX 
	    si size est invalide le résultat est imprévisible */
	if(!verif || frame->id[0] & 0xFF != 0x54 || strcmp(frame->id, "TXXX") == 0 ){
		if(lseek(fd,(frame->size)+3,SEEK_CUR) ==-1) // 3 car enc + flag 
       			perror("tag_read_one_frame erreur lseek: "); 
		if(strcmp(frame->id,"TXXX")==0){
			*frame->text=NULL;
			printf("TXXX\n");
			return 0;
			
		}
		return -1;
	}
	
	verif&=read_u16(fd,&(frame->flags));	
	
	//recuperation de l'encodage 00 acsi 01 unicode 
	verif&=read_u8(fd,&encodage);
	frame->text= read_string(fd,NULL,frame->size,encodage);
	if(!verif || frame->text==NULL)
		return -1;
    	return 0;
}																	
