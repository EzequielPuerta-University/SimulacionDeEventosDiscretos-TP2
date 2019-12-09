#!/bin/bash

EXPERIMENT_PATH=$1
PHARO_PATH="/home/ezequiel/PharoLauncher/pharo-vm/"
FIRST_SCRIPT="/home/ezequiel/GIT/SimulacionDeEventosDiscretos/TP2/scripts/subdividir_logs.st"
SECOND_SCRIPT="/home/ezequiel/GIT/SimulacionDeEventosDiscretos/TP2/scripts/extraer_valores.st"

cd $PHARO_PATH
./pharo Pharo.image eval --save Smalltalk at: \'fullPath\' asSymbol put: $EXPERIMENT_PATH,\'/log/\'.
./pharo Pharo.image st --quit --save $FIRST_SCRIPT
./pharo Pharo.image st --quit --save $SECOND_SCRIPT
