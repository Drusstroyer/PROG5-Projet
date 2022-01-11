<<<<<<< HEAD
# PROG5-Projet

1 : Make

    La structure du Makefile est assez simple, une simple commande, make, devrait générer les fichier exécutable. read_elf et les différents tests.

2 : Read_elf

L’exécutable read_elf accepte plusieurs paramètre :
    « -h », permet l’affichage du header du fichier ELF donné.
    « -S », permet l’affichage des header des différentes sections du fichier ELF donné.
    « -x », avec le nom d’une section contenu pour en afficher le contenu en hexadécimal.
    « -r », affiche les réadressages (si présents)
    « -s », affiche la table des symboles

3 : Test symbole

Cet exécutable, lancé avec un fichier ELf en paramètres affiche le contenu de la section contenant la table de symbole.

exemple d'utilisation : ./read_elf -S elf_linker-1.0Examples_loader/example1
                        ./read_elf -x 14 elf_linker-1.0/Examples_loader/example3



                        
            

