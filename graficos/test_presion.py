import sys
import pylab as pl

arguments = len(sys.argv) - 1
print ("The script is called with %i arguments" % (arguments))

datos = []
for argument in sys.argv[1:]:
	datos.append(float(argument))

pl.ylabel("presion en Pa")
pl.xlabel("tiempo en min")
pl.title("presion")
tiempo = pl.arange(0, 15*len(datos), 15)
pl.plot(tiempo, datos, '.-')

pl.grid()
pl.show()
