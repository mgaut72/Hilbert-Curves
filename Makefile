OPTIMIZE =  -O2

OBJS   = hilbert_generation.o hil_xy_from_s.o timer.o lam_shapiro.o \
		 parallel_prefix.o hil_s_from_xy.o reverse_lam_shapiro.o

CFLAGS = #-Wall -Werror

CC     = gcc $(CFLAGS)

INCL   = hilbert_generation.h hil_xy_from_s.h timer.h lam_shapiro.h \
		 parallel_prefix.h hil_s_from_xy.h reverse_lam_shapiro.o

LIBS   = -lm

all: analysis verify parallel_prefix_derivation

verify: $(OBJS) verify.o
	$(CC) $(OBJS) $(LIBS) verify.o -o verify.exe

verify.o: $(OBJS)


analysis: $(OBJS) analysis.o
	$(CC) $(OBJS) $(LIBS) -lrt analysis.o -o analysis.exe

analysis.o: $(OBJS)


parallel_prefix_derivation:
	$(CC) parallel_prefix_derivation.c -o parallel_prefix_derivation.exe


$(OBJS): $(INCL)

#the following lines enable us to easily remove object files
.PHONY : clean

clean:
		 rm -f *.exe *.o
