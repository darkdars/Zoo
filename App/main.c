/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Hugo Silva 21240009
 * Trabalho Pratico de P 2016/2017
 * Created on 31 de Março de 2017, 14:47
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "areasc.h"
#include "animais.h"



//MENU
int menu(){
    //limpa_ecra();
    int op;
    printf("****MENU****\n\n");
    printf("****Areas****\n\n");
    printf("1- Criar Nova Area\n");
    printf("2- Eliminar Area Existente\n");
    printf("3- Listar Areas\n\n");
    printf("****Animais****\n\n");
    printf("4- Adicionar animais\n");
    printf("5- Mover animal!\n");
    printf("6- Nascimento de um animal\n");
    printf("7- Eliminar animal!\n");
    printf("8- Listagem de animais\n");
    printf("9- Listagem de animais por areas!\n");
    printf("10- Listagem de animais por especie!\n");
    printf("11- Listagem completa acerca de um animal!\n\n");
    printf("****SAIR****\n\n");
    printf("12 - Terminar\n");
    do{
        printf("\nEscolha uma opcao: ");
        scanf(" %d", &op);
    }while(op<1 || op>12);
    
    return op;
    
}

int main(int argc, char** argv) {
    int tam = 0,fim,dime = 0;
    int conf;
    char nomeFich[100] = {"areas.txt"};
    char nomeAnim[100] = {"animais.dat"};
    char nomeEspecie[100] = {"especie.dat"};
    area array = NULL;
    espec esp = NULL;
    
    
    array = le_ficheiro(nomeFich,&tam);
    if(array == NULL){
        printf("Erro a ler ficheiro!\n");
        return 0;
    }
    
    //chama funcao para ler animais
    if(le_fich(nomeAnim,array,&tam) == 0){
        printf("Nao existem animais!\n");
        system("Pause");
    }
    //Ler especie e passar para vetor dinamico
    esp = le_especie(&dime,nomeEspecie);
    
    //associar familia depois de ler os animais todos
    associa_fam(array,&tam);
    
    limpa_ecra();
    
    
    

    do{
       fim = menu();       
        switch(fim){
            case 1: array = cria_area(array,&tam);
            break;
            case 2: elimina_area(array,&tam);
            break;
            case 3: imprime(array,tam);
            break;
            case 4: esp = add_animais(array,&tam,esp,&dime);
            break;
            case 5: transfer_animal(array,&tam);
            break;
            case 6: nasc_animal(array,&tam);
            break;
            case 7: eliminar_animal(array,&tam);
            break;
            case 8: listar_animais(array,&tam);
            break;
            case 9: listar_local(array,&tam);
            break;
            case 10: listar_especie(array,&tam);
            break;
            case 11: listar_completa(array,&tam);
            break;
        }
        if(fim == 7){
             associa_fam(array,&tam);
        }
        limpa_ecra();
    }while(fim!=12);
    
    
    
    //guarda especies
    grava_especie(esp,&dime,nomeEspecie);
    
    
    //Guarda animais
    grava_fich(nomeAnim,array,&tam);
    
    //Guarda areas
    guarda_ficheiro(array,nomeFich,&tam);
    //Liberta memoria das areas
    free(array);
    printf("\n\nFim do Programa!\n");
    system("pause");
    return (EXIT_SUCCESS);
}

