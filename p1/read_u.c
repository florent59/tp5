#include "flag.h"
#include <sys/types.h>
#include <sys/stat.h>
//#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

   /*/ petite permutation ne marche pas ???
    u32 mask=0XFF000000;
    u32 out=0;
    
    while(*val){
        out |= mask & val;
        out >>=8;
        *val <<=8;
    } */ 
u32 convert_size(u32 size){
    u32 out, mask;
    mask = 0x7F000000;
    out=0;

    while(mask){
        out>>=1;
        out|= size & mask;
        mask>>=8;
    }

	return out;
}
int read_u8(int fd, u8 *val){
    int err= read(fd, val, 1);
    if( err ==-1){
        perror("erreur read_u8");
        return 0;   
    }
   
    return 1;
}
int read_u16(int fd, u16 *val){
   int err= read(fd, val, 2);
   if( err ==-1){
        perror("erreur read_u16");
        return 0;   
   } 
	*val= (*val>>8) | (*val<<8) ;
   return 1;
}


int read_u32(int fd, u32 *val){
	int err= read(fd, val,4);
    if( err ==-1){
        perror("erreur read_u32");
        return 0;   
    }
//	u16* a=(u16*)val;
//  *a= (*a>>8) | (*a<<8);
   	permut2((u16*)val);
//  	*val= (*val>>16) | (*val<<16);
    permut4(val);
//  	a=(u16*) val; 
//	*a= (*a>>8) | (*a<<8); 
    permut2((u16*)val); 
    return 1;
}


char* read_string(int fd, char *to, int size, int encoding){
	//size ne peut etre <=0 et plus grand que 500 car un nom de fichier
	// unix <= 240 
	//if(size<0 || size>500)
	//æ	return NULL;
	//	printf("size==0%d\n",size);
	 if(encoding != 0)
   		size= size / 2 ; 
  
    if(!to)
      to= (char*)malloc( sizeof(char) *(1 + size) );  
       
   
    //verif des parametre de la fonction + si malloc a fonctionnée
	if(!to | encoding != 1 && encoding != 0 || fd == -1)
	        return NULL;	 
			
	int index=0;
	if(encoding==0)//acsi
	{
		for(index;index<size-1;index++){
			if(!read_u8(fd,to+index)) // erreur dans le fichier 	
				return NULL;
		}
	}
	else //unicode
	{
        	int decalage=0;   
        	u16* val  = (u16*)malloc(sizeof(u16));//pas de verif du retour

			//lecture du BOM        
 	       read_u16(fd,val);
        	if(*val == 0XFFFE) 
            		decalage=8;  

        	for(index; index< size ;index++)
   	     	{
	  		if(!read_u16(fd,val)) // erreur dans le fichier 
               			return NULL;
         
            		*val>>=decalage;
          		*(to+index)= (char)*val;
        	}
    	}
	
	*(to+index)='\0';
	return to;	
}


