#makefile
  # IMS- Implementace diskr. simulatoru zalozeneho na rizeni UDALOSTMI(opak procesne orientovaneho pristupu)
  # 12.12.2009
  # Autor: Jaroslav Sendler, FIT, xsendl00@stud.fit.vutbr.cz
  #        Dusan Kovacic, FIT, xkovac21@stud.fit.vutbr.cz
  # Prelozeno gcc 4.2
  #

PROGRAM=calendr

OBJ=calendr.o dblist.o simulation.o
SRC=calendr.cc dblist.cc simulation.cc
HEAD=dblist.h simulation.h

CCM=g++
CCMFLAGS=-std=c++98 -Wall -pedantic 
	
all:  ${PROGRAM} clean


deb:  ${OBJ}
	$(CCM) $(CCMFLAGS) ${OBJ} -o ${PROGRAM} #-DDEBUG -DNDEBUG

calendr:  ${OBJ}
	$(CCM) ${CCMFLAGS} ${OBJ} -o ${PROGRAM}

${OBJ}:${HEAD}

clean: 
	rm -f *.o

remove: 
	rm -f *.o ${PROGRAM} ${PROGRAM}.tar.gz

zip:
	tar -c ${SRC} ${HEAD} makefile README > ${PROGRAM}.tar; \
	gzip ${PROGRAM}.tar
