#!/usr/bin/env python
# -*- coding: iso-8859-2 -*-
###############################################################################
# projekt: IMS 2008 - Implementace diskretniho simulatoru rizeneho udalostmi
# soubor: simulator.py
# kodovani: iso-8859-2
#
# autori:
#	Petr Matelesko, xmatel00
#	Jakub Dohnal, xdohna00
#
# datum: 11. 12. 2008
#
# popis: 
#
#	
###############################################################################
###############################################################################
# generovani nahodntch cisel

from random import *
from math import exp
from math import sqrt
from math import fabs

#vlastni generator poissonova rozlozeni
def poisson(lam):
	x = y = 0.0
	PSSN = 0
	if (lam <= 0):
		print "Chyba pri pouziti funkce Poisson"
	if (lam <= 9.0):
		y = exp(-lam)
		x = 1.0
		while (1):
			x *= random()
			if (x < y):
				break
			PSSN += 1
	else:
		sl = sqrt(lam)
		PSSN = int(round(gauss(lam, sl) + 0.5))
		while (PSSN < 0):
			PSSN = int(round(gauss(lam, sl) + 0.5))
	return PSSN

	
###############################################################################
""" Simulace """
class Simulation:
	time = 0.0
	
	""" start - startovani cas, end - koncovy cas simulace """
	def __init__(self, start, end):
		self.start = start
		self.end = end
		time = start
	
###############################################################################
""" Statistiky - tvorba a tisk statistik """
class Stat:
	
	def __init__(self, name = "Statistika"):
		self.name = name
		self.sx = 0
		self.sx2 = 0
		self.min = 0
		self.max = 0
		self.n = 0
	
	def addData(self, x):
		self.sx += x
		self.sx2 += (x*x)
		self.n += 1
		if (self.n == 1):
			self.min = x
			self.max = x
		else:
			if (x < self.min):
				self.min = x
			if (x > self.max):
				self.max = x
	
	# vrati 1 pokud jsou k dispozici data pro urceni statistiky,
	# vrati 0 pokud data k dispozici nejsou
	def checkData(self):
		if (self.n > 0):
			return 1
		else:
			return 0
	
	def clear(self):
		self.sx = 0
		self.sx2 = 0
		self.min = 0
		self.max = 0
		self.n = 0
	
	# prumerna hodnota
	def meanValue(self):
		if (self.n == 0):
			print "!Stat (meanValue): nedostatecny pocet zaznamu"
			return 0
		return self.sx/self.n
	
	# standardni odchylka
	def stdDev(self):
		if (self.n < 2):
			print "!Stat (stdDev): nedostatecny pocet zaznamu"
			return 0
		return sqrt(fabs((self.sx2-self.sx*self.sx/self.n)/(self.n-1)))
	
	def out(self):
		print "\n================== %s ==================" % self.name
		print " Pocet zaznamu:       %i" % self.n
		print " Prumerna hodnota:    %f" % self.meanValue()
		print " Smerodatna odchylka: %f" % self.stdDev()
		print " Maximalni hodnota:   %f" % self.max
		print " Mininimalni hodnota: %f" % self.min
	
	def count(self):
		print "================== %s ==================" % self.name
		print " Pocet zaznamu: %i" % self.n

###############################################################################
""" Zarizeni - vylucny pristup """
""" - ma dva stavy: volne a obsazeno """
class Facility:
		
	""" Inicializace """
	def __init__(self, name):
		self.name = name		# jmeno zarizeni
		self.busy = False		# obsazeni zarizeni
	
	""" DEBUG: tisk informaci"""
	def info(self):
		print "Facility: %s\nbusy = %d" % (self.name, self.busy)
		
	""" Jmeno zarizeni """	
	def name(self):
		return self.name
		
	""" Status zarizeni - obsazene nebo volne"""
	""" Vraci True, kdyz je zarizeni obsazene, False kdyz je volne """
	def isBusy(self):
		return self.busy
	
	""" Obsazeni zarizeni """
	def seize(self):
		self.busy = True
	
	""" Uvolneni zarizeni """
	def release(self):
		self.busy = False

""" FIFO fronta """
class Queue:
	
	""" Inicializace """
	def __init__(self):
		self.queue = []
		
	""" Test prazdnosti fronty """
	def isEmpty(self):
		if len(self.queue) == 0:
			return True
		else:
			return False
		
	""" Vlozeni prvku do fronty """
	def enqueue(self, item):
		self.queue.append(item)
	
	""" Vybrani prvku z fornty """
	def pop(self):
		return self.queue.pop(0)

""" Kalendar udalosti - prioritni fronta """
""" POZOR: pred operacemi findMin() a deleteMin() nutno testovat, jestli
    neni fronta prazdna pomoci isEmpty() """
class Calendar(Simulation):
	""" Inicializace """
	def __init__(self):
		self.calendar = []	# seznam pro aktivacni cas
		self.data = []		# seznam pro udalosti
	
	""" DEBUG: tisk kalendare """
	def info(self):
		print self.calendar
		print self.data
	
	""" Testuje, jestli je kalendar prazdny """
	""" - je prazdny   - True """
	""" - neni prazdny - False """
	def isEmpty(self):
		if (len(self.calendar) == 0):
			return True
		else:
			return False
	
	""" Vrati nejmensi prvek """
	def findMin(self):
		__acttime = min(self.calendar)
		__i = self.calendar.index(__acttime)
		__event = self.data[__i]
		return (__acttime, __event)
	
	""" Odstrani nejmensi prvek """
	def deleteMin(self):
		__acttime = min(self.calendar)
		__i = self.calendar.index(__acttime)
		del self.calendar[__i]
		del self.data[__i]
	
	""" Naplanuje udalost """
	def schedule(self, acttime, event):
		if acttime < Simulation.time:
			print "Chyba: planovani do minulosti"
		else:
			self.calendar.append(acttime)
			self.data.append(event)

###############################################################################
# popis modelu

def event10():
	# pacient opousti ordinaci zubniho lekare
	print "Pacient opousti ordinaci zubniho lekare",
	zubni.release()
	
	# jestli je v cekarne dalsi pacient, prijde na radu
	if cekarna_zubni.isEmpty() == False:
		print "V cekarne je pripraven dalsi pacient"
		c.schedule(sim.time, cekarna_zubni.pop())
	else:
		print ""
		
def event9():
	# pacient opousti ordinaci praktickeho lekare
	print "Pacient opousti ordinaci praktickeho lekare",
	prakticky.release()
	
	# jestli je v cekarne dalsi pacient, prijde na radu
	if cekarna_prakticky.isEmpty() == False:
		print "V cekarne je pripraven dalsi pacient"
		c.schedule(sim.time, cekarna_prakticky.pop())
	else:
		print ""

def event8():
	# pacient opousti ordinaci detskeho lekare
	print "Pacient opousti ordinaci detskeho lekare",
	detsky.release()
	
	# jestli je v cekarne dalsi pacient, prijde na radu
	if cekarna_detsky.isEmpty() == False:
		print "V cekarne je pripraven dalsi pacient"
		c.schedule(sim.time, cekarna_detsky.pop())
	else:
		print ""

def event7():
	# je v ordinaci zubniho lekare
	print "Pacient je v ordinace zubniho lekare"
	zubni.seize()
	# je v ordinaci exp(20) min
	c.schedule(sim.time + expovariate(20)*100, e10)
	
def event6():
	# je v ordinaci praktickeho lekare
	print "Pacient je v ordinace praktickeho lekare"
	prakticky.seize()
	# je v ordinaci exp(15) min
	c.schedule(sim.time + expovariate(15)*100, e9)

def event5():
	# je v ordinaci detskeho lekare
	print "Pacient je v ordinace detskeho lekare"
	detsky.seize()
	# je v ordinaci 15 min
	c.schedule(sim.time + expovariate(15)*100, e8)

def event4():
	# pacient jde do cekarny zubniho lekare
	print "Pacient je v cekarne zubniho lekare: ",
	# v ordinaci je jiny pacient, pacient si sedne do cekarny
	if zubni.isBusy() == True:
		print "je obsazeno, pacient si sedne"
		cekarna_zubni.enqueue(e7) # POZOR
	# ordinace je prazdna, pacient jde do ordinace
	else:
		print "je volno, jde k lekari"
		c.schedule(sim.time, e7)
		
def event3():
	# pacient jde do cekarny praktickeho lekare
	print "Pacient je v cekarne praktickeho lekare: ",
	# v ordinaci je jiny pacient, pacient si sedne do cekarny
	if prakticky.isBusy() == True:
		print "je obsazeno, pacient si sedne"
		cekarna_prakticky.enqueue(e6) # POZOR
		
	# ordinace je prazdna, pacient jde do ordinace
	else:
		print "je volno, jde k lekari"
		c.schedule(sim.time, e6)

def event2():
	# pacient jde do cekarny detskeho lekare
	print "Pacient je v cekarne detskeho lekare: ",
	
	# v ordinaci je jiny pacient, pacient si sedne do cekarny
	if detsky.isBusy() == True:
		print "je obsazeno, pacient si sedne"
		cekarna_detsky.enqueue(e5) # POZOR
		
	# ordinace je prazdna, pacient jde do ordinace
	else:
		print "je volno, jde k lekari"
		c.schedule(sim.time, e5)

def event1():
	# prichod pacientu na polikliniku
	print "Prichod pacienta na polikliniku: ",
	
	i = randint(0,100)
	#i = 90
	# s pravdepodobnosti 35 % jde pacient k detskemu lekari
	if i < 35:
		print "jde k detskemu lekari"
		c.schedule(sim.time, e2)

	# s pravdepodobnosti 20 % jde pacient k zubnimu lekari
	elif i > 80:
		print "jde k zubnimu lekari"
		c.schedule(sim.time, e4)
		
	# s pravdepodobnosti 45 % jde pacient k praktickemu lekari
	else:
		print "jde k praktickemu lekari"
		c.schedule(sim.time, e3)

	# dalsi pacient prijde za expovariate(10)*100
	c.schedule(sim.time + expovariate(10)*100, e1)

###############################################################################
# popis simulace

# udalosti
e1 = "e1"
e2 = "e2"
e3 = "e3"
e4 = "e4"
e5 = "e5"
e6 = "e6"
e7 = "e7"
e8 = "e8"
e9 = "e9"
e10 = "e10"


print "*** Inicializace: ***"
# inicializace
sim = Simulation(0, 600)

c = Calendar()

cekarna_detsky = Queue()
cekarna_prakticky = Queue()
cekarna_zubni = Queue()


detsky = Facility("Detsky lekar")
prakticky = Facility("Prakticky lekar")
zubni = Facility("Zubni lekar")

# statistiky
s_detsky_c = Stat("Detsky lekar: prichody do cekarny")
s_prakticky_c = Stat("Prakticky lekar: prichody do cekarny")
s_zubni_c = Stat("Zubni lekar: prichody do cekarny")

s_detsky_o = Stat("Detsky lekar: prichody do ordinace")
s_prakticky_o = Stat("Prakticky lekar: prichody do ordinace")
s_zubni_o = Stat("Zubni lekar: prichody do ordinace")

s_detsky_op = Stat("Detsky lekar: pobyt v ordinaci")
s_prakticky_op = Stat("Prakticky pobyt lekar: v ordinaci")
s_zubni_op = Stat("Zubni lekar: pobyt v ordinaci")

# pomocne promenne udrzuji informaci o case predesle udalosti stejneho typu
tl_detsky_c = 0
tl_prakticky_c = 0
tl_zubni_c = 0

tl_detsky_op = 0
tl_prakticky_op = 0
tl_zubni_op = 0

print "Time = ", sim.time


#c.schedule(expovariate(10)*100, e1)  # naplanujeme prvni udalost v case expovariate(0.6)*100
c.schedule(expovariate(10)*100, e1)

print "*** Zacatek simulace:  cas = ", sim.start

# dokud neni kalendar prazdny
while c.isEmpty != True:
	
	# precteme prvni zaznam z kalendare
	item = c.findMin()
	t = item[0]
	ev = item[1]
	
	#print item

	# odstranime prvni zaznam z kalendare
	c.deleteMin()

	# ukoncovaci podminka
	if t > sim.end:
		sim.time = sim.end
		break
	
	# posun casu na cas aktualni udalosti
	sim.time = t
	
	print "[Time = %f]: " % sim.time
	
	# provedeme udalost
	if ev == "e1":
		event1()
	elif ev == "e2": # detsky lekar cekarna: prichod
		event2()
		s_detsky_c.addData(sim.time - tl_detsky_c)
		tl_detsky_c = sim.time
	elif ev == "e3": # prakticky lekar cekarna: prichod
		event3()
		s_prakticky_c.addData(sim.time - tl_prakticky_c)
		tl_prakticky_c = sim.time
	elif ev == "e4": # zubni lekar cekarna: prichod
		event4()
		s_zubni_c.addData(sim.time - tl_zubni_c)
		tl_zubni_c = sim.time
	elif ev == "e5": # detsky lekar ordinace: prichod
		event5()
		s_detsky_o.addData(sim.time - tl_detsky_op)
		tl_detsky_op = sim.time
	elif ev == "e6": # prakticky lekar ordinace: prichod
		event6()
		s_prakticky_o.addData(sim.time - tl_prakticky_op)
		tl_prakticky_op = sim.time
	elif ev == "e7": # zubni lekar ordinace: prichod
		event7()
		s_zubni_o.addData(sim.time - tl_zubni_op)
		tl_zubni_op = sim.time
	elif ev == "e8": # detsky lekar ordinace: odchod
		event8()
		s_detsky_op.addData(sim.time - tl_detsky_op)
	elif ev == "e9": # prakticky lekar ordinace: odchod
		event9()
		s_prakticky_op.addData(sim.time - tl_prakticky_op)
	elif ev == "e10": # zubni lekar ordinace: odchod
		event10()
		s_zubni_op.addData(sim.time - tl_zubni_op)
	
print "*** Konec simulace:  cas = ", sim.time

#tisk statistik

s_detsky_c.out()
s_detsky_o.out()
print " Prumerny cas straveny v cekarne: %f" % (s_detsky_o.meanValue() - s_detsky_c.meanValue()) 
s_detsky_op.out()


s_prakticky_c.out()
s_prakticky_o.out()
print " Prumerny cas straveny v cekarne: %f" % (s_prakticky_o.meanValue() - s_prakticky_c.meanValue()) 
s_prakticky_op.out()

s_zubni_c.out()
s_zubni_o.out()
print " Prumerny cas straveny v cekarne: %f" % (s_zubni_o.meanValue() - s_zubni_c.meanValue()) 
s_zubni_op.out()
