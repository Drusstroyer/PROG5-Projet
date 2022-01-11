#!/bin/bash
if [[ $# -ne 2 && $# -ne 3 ]] || [[ $# -eq 1 ]]
    then
    echo "./run.sh <option> <fichiertest>"
    echo "Les options sont : 
            -h: Afficher l'en-tête du fichier elf
            -S: afficher l'en-tête des sections
            -x <string>: Afficher le contenu de la section avec le <string> en hexadécimal.
            -r: Afficher les réadresages (si présents)
            -s: Afficher la table des symboles"
else 
    echo $2
    if [[ $# -eq 2 || $# -eq 3 ]]
    then 
        if [ $1 = "-h" ]
        then
            echo " ========================== READELF LINUX ============= "
            readelf -h $2
            echo "
            
            ================== READELF GROUPE ==============
            "
            ./read_elf -h $2
        fi
        if [ $1 = "-S" ]
        then 
            echo " ========================== READELF LINUX ============= "
            readelf -S $2
            echo "
            
            ================== READELF GROUPE ==============
            "
            ./read_elf -S $2
        fi
        if [ $1 = "-x" ]
        then 
            echo " ========================== READELF LINUX ============= "
            readelf -x $2 $3
            echo "
            
            ================== READELF GROUPE ==============
            "
            ./read_elf -x $2 $3
        fi
        if [ $1 = "-r" ]
        then 
            echo " ========================== READELF LINUX ============= 
            "
            readelf -r $2
            echo "
            
            ================== READELF GROUPE ==============
            "
            ./read_elf -r $2
        fi
        if [ $1 = "-s" ]
        then 
            echo " ========================== READELF LINUX ============= "
            readelf -s $2
            echo " 
            
            ================== READELF GROUPE ==============
            "
            ./read_elf -s $2
        fi
    fi 
fi