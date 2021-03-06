CC=gcc
CFLAG=-g -W -Wall -ansi -pedantic
LDFLAGS=
EXEC=test
DIR_P1=p1/
DIR_P2=p2/
DIR_OBJS=obj/

all:$(EXEC)

$(EXEC): $(DIR_OBJS)manip_chaine.o $(DIR_OBJS)main.o $(DIR_OBJS)recup_info.o $(DIR_OBJS)read_u.o $(DIR_OBJS)tag_read.o $(DIR_OBJS)tag.o $(DIR_OBJS)affiche_u.o $(DIR_OBJS)gen_arbo.o $(DIR_OBJS)tri_final.o
	$(CC) -o $@ $^ $(LDFLAGS)
	
############ PARTIT DEUX #################
$(DIR_OBJS)manip_chaine.o: $(DIR_P2)manip_chaine.c
	$(CC) -o $@ -c $^  $(CFLAGS) 
 	
$(DIR_OBJS)main.o: $(DIR_P2)main.c $(DIR_P2)header.h 
	$(CC) -o $@ -c $< $(CFLAGS)

$(DIR_OBJS)recup_info.o: $(DIR_P2)recup_info.c
	$(CC) -o $@ -c $^ $(CFLAGS)
	
$(DIR_OBJS)gen_arbo.o: $(DIR_P2)gen_arbo.c
	$(CC) -o $@ -c $^ $(CFLAGS)

$(DIR_OBJS)tri_final.o: $(DIR_P2)tri_final.c
	$(CC) -o $@ -c $^ $(CFLAGS)




############ PARTIT UNE #################
$(DIR_OBJS)read_u.o: $(DIR_P1)read_u.c
	$(CC) -o  $@ -c $^ $(CFLAGS)

$(DIR_OBJS)tag_read.o: $(DIR_P1)tag_read.c
	$(CC) -o $@ -c $^ $(CFLAGS)
 
$(DIR_OBJS)tag.o: $(DIR_P1)tag.c
	$(CC) -o $@ -c $^ $(CFLAGS)

$(DIR_OBJS)affiche_u.o: $(DIR_P1)affiche_u.c
	$(CC) -o $@ -c $^ $(CFLAGS)	

clean:
	rm -rf obj/*.o
	
mrproper: clean
	rm -rf $(EXEC)
	

