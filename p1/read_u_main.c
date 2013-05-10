
void main(){
	//ouverture 
	int fd ;
	fd = open("/home/marms/Documents/ASR/C/TP5/x.mp3", O_CREAT |  O_RDONLY, 0666 );
    if( fd == -1 ){
    	printf("erreur ouverture\n");
    	exit(15);
    }	
	
  	printf("\n====ESSAIS PERMUTE======\n");
	  
	  	u16 *x= (u16*)malloc(sizeof(u16)); 
	  	*x=0x4244;//BD
	 	affiche_u16(x);
		permut2(x); //DB 
		affiche_u16(x);
		printf("x, %0x\n",*x);

		u32* g= (u32*)malloc(sizeof(u32));
		*g=0x10203040;
		permut4(g);			
	 	printf("g, %0x\n",*g);
	printf("\n======FIN PERMUTE=======\n");
  
	u8* a = (u8*) malloc(sizeof(u8));
	if(! read_u8(fd,a)){ printf("echec3\n");}
	affiche_u8(a);


	u16* e = (u16*) malloc(sizeof(u16));
	if(! read_u16(fd,e)){ printf("echec3\n");}
	affiche_u16(e);
	
	u32* f = (u32*) malloc(sizeof(u32));
	if(! read_u32(fd,f)){ printf("echec4\n");}
	affiche_u32(f);	



		*h = 0x6d776e6e ; 
		affiche_u32(h);
		aff_bin((u8*)h);	 printf("\n"); 
	    *h=	convert_size(*h);
		aff_bin((u8*)h); printf("\n"); 
	//fermeture
    close(fd);
}
