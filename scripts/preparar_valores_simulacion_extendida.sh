#!/bin/bash

EXPERIMENT_PATH=$1
PHARO_PATH="../../PharoLauncher/pharo-vm/"
SCRIPT="../../TP2/scripts/subdividir_presupuesto.st"

cd $PHARO_PATH
./pharo Pharo.image eval --save Smalltalk at: \'fullPath\' asSymbol put: $EXPERIMENT_PATH,\'/log/\'.
./pharo Pharo.image st --quit --save $SCRIPT
