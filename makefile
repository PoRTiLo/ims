#makefile
  # IPK-1.projekt, 30.3.2009
  # Autor: Jaroslav Sendler, FIT
  # Prelozeno gcc 4.2
  #

PROGRAM=calendr

SRC=calendr.cc

CCM=g++
CCMFLAGS=-std=c++98 -Wall -pedantic
	
all:  ${PROGRAM} clean


deb:  calendr.cc
	$(CCM) $(CCMFLAGS) -DNDEBUG calendr.cc -o calendr 

calendr: calendr.cc
	$(CCM) $(CCMFLAGS) calendr.cc -o $@

clean: 
	rm -f *.o

remove: 
	rm -f ${PROGRAM} ${PROGRAM}.tar.gz

zip:
	tar -c ${SRC} makefile README > ${PROGRAM}.tar; \
	gzip ${PROGRAM}.tar
