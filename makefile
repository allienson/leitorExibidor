CC = gcc
CFLAGS = -m32 -std=c99 
OUTFILE = LeitorExibidor
OBJS = exibidor.o leitor.o decodificador.o main.o
SRCS = exibidor.c leitor.c decodificador.c main.c

$(OUTFILE): $(OBJS)
	$(CC) $(CFLAGS) -o $(OUTFILE) $(OBJS)
$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)
