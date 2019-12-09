#!/bin/bash

#SE EJECUTA LA SIMULACION
../../bin/cd++ -m mercados.ma -o out/output -l log/log -t 00:00:00:365
find ./log/ ! -name log01 -type f -delete

#SE LLAMA A LOS SCRIPTS QUE SEPARAN Y PREPARAN LOS VALORES PRODUCIDOS POR LA SIMULACION (REQUIERE DE PHARO SMALLTALK)
EXPERIMENT_PATH=$(pwd)
cd ../../scripts/
./preparar_valores.sh \'$EXPERIMENT_PATH\'
