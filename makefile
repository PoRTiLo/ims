#makefile
  # IMS- Implementace diskr. simulatoru zalozeneho na rizeni UDALOSTMI(opak procesne orientovaneho pristupu)
  # 12.12.2009
  # Autor: Jaroslav Sendler, FIT, xsendl00@stud.fit.vutbr.cz
  #        Dusan Kovacic, FIT, xkovac21@stud.fit.vutbr.cz
  # Prelozeno gcc 4.2
  #

PROGRAM=sim

OBJ=sim.o mainxx.o sgen.o#poisson.o# dblist.o simulation.o stat.o
SRC=sim.cpp mainxx.cpp sgen.cpp#poisson.cc# dlist.cc simulation.cc stat.cc
HEAD=sim.h sgen.h# dblist.h simulation.h stat.h

CCM=g++
CCMFLAGS=-std=c++98 -Wall -pedantic 
	
all:  ${PROGRAM} clean


deb:  ${OBJ}
	$(CCM) $(CCMFLAGS) ${OBJ} -o ${PROGRAM} #-DDEBUG -DNDEBUG

sim:  ${OBJ}
	$(CCM) ${CCMFLAGS} ${OBJ} -o ${PROGRAM}

${OBJ}:${HEAD}

clean: 
	rm -f *.o

remove: 
	rm -f *.o ${PROGRAM} ${PROGRAM}.tar.gz

zip:
	tar -c ${SRC} ${HEAD} makefile README > ${PROGRAM}.tar; \
	gzip ${PROGRAM}.tar
