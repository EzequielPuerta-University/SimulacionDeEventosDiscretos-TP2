#!/bin/bash

#SE EJECUTA LA SIMULACION
cp ../../macros.inc macros.inc
../../bin/cd++ -m mercados.ma -o out/output -l log/log -t 00:00:36:500
rm macros.inc
find ./log/ ! -name log01 -type f -delete

#SE LLAMA A LOS SCRIPTS QUE SEPARAN Y PREPARAN LOS VALORES PRODUCIDOS POR LA SIMULACION (REQUIERE DE PHARO SMALLTALK)
EXPERIMENT_PATH=$(pwd)
cd ../../scripts/
./preparar_valores_simulacion_extendida.sh \'$EXPERIMENT_PATH\'
