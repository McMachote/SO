#!/bin/bash
make clean
make
rmdir tmp
mkdir tmp
chmod 777 tmp
echo Starting simulation...
read -p "File name: " filename
read -p "Max. number of CPUs: " maxCPUs

#RR
echo EJECUTANDO ROUND-ROBIN:
cd /tmp/
#rmdir RR
mkdir RR
cd ..
for (( i=1 ; i<=maxCPUs; i++ )) #uno para cada planificador, cada iteracion una CPU mas ejecutandolo
do
   echo $i CPUs
   ./schedsim -i examples/$filename -n $i
   echo hola
   cd tmp
   mkdir /RR/$iCPUs
   cd ..
   echo adios
   mv CPU_* /tmp/RR/$iCPUs
   cd ../gantt-plot
   for (( j=0 ; j<i; j++ ))
   do
      ./generate_gantt_chart ../schedsim/CPU_$j.log
   done
   cd ../schedsim
done


#FCFS
echo EJECUTANDO FCFS:
mkdir /tmp/FCFS
for (( i=1 ; i<=maxCPUs; i++ )) #uno para cada planificador, cada iteracion una CPU mas ejecutandolo
do
   echo $i CPUs
   ./schedsim -i -n FCFS examples/$filename -n $i 
   mkdir /tmp/FCFS/$iCPUs
   mv CPU_?.log /tmp/FCFS/$iCPUs
   cd ../gantt-plot
   for (( j=0 ; j<i; j++ ))
   do
      ./generate_gantt_chart ../schedsim/CPU_$j.log
   done
   cd ../schedsim
done

#SJF
echo EJECUTANDO SJF:
mkdir /tmp/SJF
for (( i=1 ; i<=maxCPUs; i++ )) #uno para cada planificador, cada iteracion una CPU mas ejecutandolo
do
   echo CON $i CPUs
   ./schedsim -i -n SJF examples/$filename -n $i
   mkdir /tmp/SJF/$iCPUs
   mv CPU_?.log /tmp/SJF/$iCPUs
   cd ../gantt-plot
   for (( j=0 ; j<i; j++ ))
   do
      ./generate_gantt_chart ../schedsim/CPU_$j.log
   done
   cd ../schedsim
done

#PRIO
echo EJECUTANDO PRIO
mkdir /tmp/PRIO
for (( i=1 ; i<=maxCPUs; i++ )) #uno para cada planificador, cada iteracion una CPU mas ejecutandolo
do
   echo $i CPUs
   ./schedsim -i -n PRIO examples/$filename -n $i
   mkdir /tmp/PRIO/$iCPUs
   mv CPU_?.log /tmp/PRIO/$iCPUs
   cd ../gantt-plot
   for (( j=0 ; j<i; j++ ))
   do
      ./generate_gantt_chart ../schedsim/CPU_$j.log
   done
   cd ../schedsim
done
