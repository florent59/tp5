# include<sys/types.h>
# include<sys/stat.h> 
# include<fcntl.h>
# include<stdio.h>




int main ( int argc , char ** argv )
{
int fd ;
fd = open ( "/tmp/toto" , O_WRONLY | O_CREAT , 0666);

if ( fd == -1)
	printf ( " Création du fichier / tmp / toto impossible " );
else
	close ( fd );
return 0;
}

