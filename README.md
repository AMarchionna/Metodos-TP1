# Metodos-TP1

## Notas para la ejecución princial:

Para ejecutar el _main_ se sigue el protocolo de la cátedra una vez generado el ejecutable con **g++ -o ejec main.cpp** desde el directorio principal. En experimentación se cuenta con distintas herramientas para evaluar resultados.

## Experimentación

En **experimentacion.cpp** se cuenta con distintas herramientas para verificar los resultados del informe. Estas son:

* **TestCatedra**: Compara los resultados con todos los tests de la cátedra. Imprimer por consola el vector de diferencias junto a su norma infinito y su norma 1.
* **TeamCount**: Realiza la experimentación en la que la cantidad de partidos se mantiene fija mientrasque la cantidad de equipos aumenta. Sus parámetros pueden ajustarse desde la función.
* **MatchesCount**. Realiza la experimentación en la que la cantidad de equipos se mantiene fija mientras que la cantidad de equipos aumenta. Idem anterior.
* **TeamMatchesCount**: Realiza la experimentación en la que se modifican tanto la cantidad de partidos como la cantidad de equipos. Idem anterior.
* **testAtp(i)**: Imprime los rankings de la ATP 2015 o 2016 (i=0 o i=1) de acuerdo a los distintos métodos.
* **testNBA**: Imprime los rankings de la NBA con los distintos métodos.
* **Estrategia**: Genera un torneo al azar y sigue la estrategia planteada en el informe para alcanzar el primer puesto.
* **EstrategiaPromediada**: Repite una cantidad de veces la función anterior y devuelve el promedio de iteraciones necesarias para obtener el primer puesto.


