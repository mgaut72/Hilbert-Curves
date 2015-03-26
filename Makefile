#EXEC   = analysis.exe

OPTIMIZE =  -O2

OBJS   = hilbert_generation.o hil_xy_from_s.o timer.o lam_shapiro.o parallel_prefix.o

CFLAGS = #-Wall -Werror

CC     = gcc $(CFLAGS)

INCL   = hilbert_generation.h hil_xy_from_s.h timer.h lam_shapiro.h parallel_prefix.h

LIBS   = -lm -lrt

all: analysis

analysis: $(OBJS) analysis.o
		 $(CC) $(OBJS) $(LIBS) analysis.o -o analysis.exe

analysis.o: $(OBJS)

$(OBJS): $(INCL)

#the following lines enable us to easily remove object files
.PHONY : clean

clean:
		 rm -f analysis.exe *.o
