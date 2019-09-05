# Metodos-TP1

## Notas para la ejecución princial:

Para ejecutar el _main_ se sigue el protocolo de la cátedra una vez generado el ejecutable con **g++ -o ejec main.cpp** desde el directorio principal. 

## Experimentación

En **experimentacion.cpp** se cuenta con distintas herramientas para verificar los resultados del informe. Para ejecutarlas alcanza con descomentarlas, compilar y ejecutar el **.cpp**. Se recomienda no ejecutar varias en simultáneo. Estas son:

* **TestCatedra**: Compara los resultados con todos los tests de la cátedra. Imprimer por consola el vector de diferencias junto a su norma infinito y su norma 1.
* **TeamCount**: Realiza la experimentación en la cual la cantidad de partidos se mantiene fija mientrasque la cantidad de equipos aumenta. Sus parámetros pueden ajustarse desde la función.
* **MatchesCount**. Realiza la experimentación en la cual la cantidad de equipos se mantiene fija mientras que la cantidad de equipos aumenta. Idem anterior.
* **TeamMatchesCount**: Realiza la experimentación en la cual se modifican tanto la cantidad de partidos como la cantidad de equipos. Idem anterior.
* **testAtp(i)**: Imprime los rankings de la ATP 2015 o 2016 (i=0 o i=1) de acuerdo a los distintos métodos junto con información adicional del torneo.
* **testNBA**: Imprime los rankings de la NBA con los distintos métodos jun con información adicional del torneo.
* **ELOVsCMM**: Genera un torneo siguiendo la idea del informe en cual los resultados de ambos rankings sea diferente. Imprime el resultado en pantalla.
* **Estrategia**: Genera un torneo al azar y sigue la estrategia planteada en el informe para alcanzar el primer puesto.
* **EstrategiaPromediada**: Repite una cantidad de veces parametrizable la función anterior y devuelve el promedio de iteraciones necesarias para obtener el primer puesto.



