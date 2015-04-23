OPTIMIZE =  -O2

OBJS   = 3D_hilbert_generation.o turtle3D.o

CFLAGS = #-Wall -Werror

CC     = gcc $(CFLAGS)

INCL   = 3D_hilbert_generation.h turtle3D.h

LIBS   = -lm

all: recursive_3D

recursive_3D: $(OBJS) recursive_3D.o
	$(CC) $(OBJS) $(LIBS) recursive_3D.o -o recursive_3D.exe

recursive_3D.o: $(OBJS)


$(OBJS): $(INCL)

#the following lines enable us to easily remove object files
.PHONY : clean

clean:
		 rm -f *.exe *.o
