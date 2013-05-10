#include <string.h>

const char* get_file_extension(const char* file){
	return strchr(file, '.') + 1 ;
}

void clean_string(char* s){
	
	int i=0;
	while( s[i] != '\0' ){
		if(s[i] == '/')
			s[i] = '-';
		else
			s[i]=tolower(s[i]);
		i++;
	}
	s[0]=toupper(s[0]);
}


