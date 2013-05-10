#ifndef READ_U_H 
 	#define READ_U_H
 
 
 	
int read_u8(int fd, u8 *val);
int read_u16(int fd, u16 *val);
int read_u32(int fd, u32 *val);
char* read_string(int fd, char *to, int size, int encoding);   
 
#endif 
