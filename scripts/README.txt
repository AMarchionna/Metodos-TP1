Para correr los scripts, desde una consola ejecutar:

$ python metnum.py opcion

donde opcion puede ser:

compile: Compila todos los *.cpp que hayan en el directorio.
link: Genera el ejecutable en base a los *.o generados previamente.
build: compile + link
clean: borra los *.o y el ejecutable.
test: hace el build, busca lo archivos *.in en la carpeta tests/, ejecuta el programa y guarda el
resultado para cada corrida en el correspondiente .out. Despues, chequea que el resultado sea el "mismo" que el
.expected, tambien del directorio test. En este caso, la comparacion es por tolerancia coordenada a coordeanda del vector
solucion.
