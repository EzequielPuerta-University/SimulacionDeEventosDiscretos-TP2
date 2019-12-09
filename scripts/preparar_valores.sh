#!/bin/bash

EXPERIMENT_PATH=$1
PHARO_PATH="../../PharoLauncher/pharo-vm/"
FIRST_SCRIPT="../../TP2/scripts/subdividir_logs.st"
SECOND_SCRIPT="../../TP2/scripts/extraer_valores.st"

cd $PHARO_PATH
./pharo Pharo.image eval --save Smalltalk at: \'fullPath\' asSymbol put: $EXPERIMENT_PATH,\'/log/\'.
./pharo Pharo.image st --quit --save $FIRST_SCRIPT
./pharo Pharo.image st --quit --save $SECOND_SCRIPT
