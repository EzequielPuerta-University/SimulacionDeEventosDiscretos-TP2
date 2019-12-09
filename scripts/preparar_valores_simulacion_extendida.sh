#!/bin/bash

EXPERIMENT_PATH=$1
PHARO_PATH="/home/ezequiel/PharoLauncher/pharo-vm/"
SCRIPT="/home/ezequiel/GIT/SimulacionDeEventosDiscretos/TP2/scripts/subdividir_presupuesto.st"

cd $PHARO_PATH
./pharo Pharo.image eval --save Smalltalk at: \'fullPath\' asSymbol put: $EXPERIMENT_PATH,\'/log/\'.
./pharo Pharo.image st --quit --save $SCRIPT
