EXEC   = analysis.exe

OPTIMIZE =  -O2

OBJS   = hilbert_generation.o hil_xy_from_s.o timer.o lam_shapiro.o parallel_prefix.o analysis.o

CFLAGS = #-Wall -Werror

CC     = gcc $(CFLAGS)


INCL   = hilbert_generation.h hil_xy_from_s.h timer.h lam_shapiro.h parallel_prefix.h

LIBS   = -lm -lrt

#the following lines build an executable from the object files
$(EXEC): $(OBJS)
		 $(CC) $(OBJS) $(LIBS) -o $(EXEC)

$(OBJS): $(INCL)

#the following lines enable us to easily remove object files
.PHONY : clean

clean:
		 rm -f $(OBJS) $(EXEC)
