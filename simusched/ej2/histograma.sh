#!/bin/bash 

LC_NUMERIC="en_US.UTF-8"

iteraciones=1


while getopts 'ha:' opt; do
  case $opt in
    a) iteraciones=$OPTARG ;;
    h) echo ""
       echo "    Histograma"
       echo ""
       echo "    Opciones disponibles:"
       echo "        -h        Imprime este texto de ayuda."
       echo "        -a <núm>  Cantidad de iteraciones - por defecto 1"
       echo ""
       exit 0 ;;
  esac
done

printf "%d " 1 >> $(dirname $0)/histograma.txt
printf "\n" >> $(dirname $0)/histograma.txt

for h in $(seq 1 $iteraciones); do
  $(dirname $0)/../simusched $(dirname $0)/lote2.tsk 1 1 1 SchedFCFS >> $(dirname $0)/histograma.txt
  for k in $(seq 1 1000000); do
    echo "1"
  done
done

#octave -q $(dirname $0)/exp1.m