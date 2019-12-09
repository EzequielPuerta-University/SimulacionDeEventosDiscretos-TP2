TP2 - Simulación de Eventos Discretos
=====================================

En principio se espera que este repositorio se clone en
un directorio ubicado al mismo nivel que la carpeta de 
la distribución original de CD++.

Es decir si dicha distribución (que al descargarse se ubica 
en CDPP_ExtendedStates-codename-Santi) está ubicada en una 
carpeta llamada "foo", clonar este repo (TP2) en:

foo
* CDPP_ExtendedStates-codename-Santi
* TP2
 
Dentro de TP2 se provee:

1. el informe en formato pdf.

2. el directorio experimentos, con los 6 experimentos realizados en el informe.
   Cada uno tendrá su modelo acoplado, su archivo de valores iniciales y un
   simulacion.sh que correrá la simulación y otros scripts de post procesamiento.
   El experimento preliminar además tiene su propio archivo de macros. Esto es
   porque los experimentos restantes usan otro archivo de macros, con una 
   modificación a este mismo.
	   
3. el directorio paletas, con dos paletas de colores, útiles para el graficador
   de CellDEVS.

4. el directorio scripts posee dos .sh para ser llamados desde los simulacion.sh.
   Todos usan al preparar_valores.sh, excepto por el experimento de mercados
   imperfectos extendido. Este utiliza preparar_valores_simulacion_extendida.sh.
   Estos dos scripts bash sirven para separar los valores de las tuplas de estado
   y para generar archivos aptos para realizar graficos. De no utilizarse (ya sea
   porque se tiene otra herramienta o porque no se necesita graficar) se puede
   comentar la referencia en los simulacion.sh. Si se utilizan, se llamaran a otros
   scripts escritos en smalltalk y provistos en la misma carpeta. Se necesita por
   esto, una distribución de Pharo Smalltalk para ejecutarlos. Una vez descargada,
   hay que indicar el directorio donde se encuentra en la variable PHARO_PATH de
   sendos archivos .sh. (Se realizaron en este lenguaje para poder tener material
   andando rápido, ya que es el lenguaje que mejor domino después de 5 años de
   usarlo jaja)

5. el archivo de macros, utilizado por casi todos los experimentos, excepto por
   el primer experimento, el preliminar.

6. el reg.cpp y el Makefile para generar el binario necesario para correr las
   simulaciones. Acá es donde se utilizará el directorio del CD++, en la variable
   KERNEL_SRC.

7. este README.
