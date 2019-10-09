CC=gcc
CFLAGS=
LDFLAGS=

HUFF=huff
MAINH=mainCompression.c

DEHUFF=dehuff
MAIND=mainDecompression.c

SRCH = $(MAINH) compression.c
SRCD = $(MAIND) decompression.c

HEADERS = compression.h decompression.h
OBJH= $(SRCH:.c=.o)
OBJD= $(SRCD:.c=.o)

all: huff dehuff

huff: $(HUFF)

$(HUFF) : $(OBJH) $(HEADERS)
	@$(CC) -o $(HUFF) $(OBJH) $(LDFLAGS) && echo "$(HUFF) created" || echo "Fail"

dehuff: $(DEHUFF)

$(DEHUFF) : $(OBJD) $(HEADERS)
	@$(CC) -o $(DEHUFF) $(OBJD) $(LDFLAGS) && echo "$(DEHUFF) created" || echo "Fail"


compression.o : compression.c
	@$(CC) -o compression.o -c compression.c $(CFLAGS)


decompression.o : decompression.c
		@$(CC) -o decompression.o -c decompression.c $(CFLAGS)

mainCompression.o : mainCompression.c
	@$(CC) -o mainCompression.o -c mainCompression.c $(CFLAGS)

mainDecompression.o : mainDecompression.c
	@$(CC) -o mainDecompression.o -c mainDecompression.c $(CFLAGS)




.PHONY : clean mrproper

clean :
	rm $(OBJH) $(OBJD) -rvf

mrproper :	clean
	@rm $(HUFF) $(DEHUFF) -rvf
