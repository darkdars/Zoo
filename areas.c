/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "areasc.h"
#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Funcao para limpar ecra
void limpa_ecra(){
    system("cls");
}

//LE Areas a partir do ficheiro
area le_ficheiro(char *nomeFich,int *total){
    FILE *f;
    area v = NULL;
    int c,i = 0,j = 0,num = 0;
    char ch;
    *total = 1;   
      
    if((f = fopen(nomeFich,"rt")) == NULL){
        printf("Erro a abrir o ficheiro %s de texto para leitura!\n",nomeFich);
        return v;
    }
    
    //Contar linhas
   while( (ch=fgetc(f))!= EOF ){
			if(ch == '\n'){
                            (*total)++;
                        }
			  
                  
}
    
    fclose(f);
    
      if((f = fopen(nomeFich,"rt")) == NULL){
        printf("Erro a abrir o ficheiro %s de texto para leitura!\n",nomeFich);
        return v;
    }
     
       v = realloc(v,sizeof(avea)*(*total));
      if(v == NULL){
            printf("Erro a Alocar Memoria!\n");
            fclose(f);
            return v;
        }     
       for(int d = 0;d<*total;d++){
        fscanf(f,"%s %d %d",(v+i)->nome,&(v+i)->capacidade,&(v+i)->n_areas_adj);
        (v+i)->ocupacao = 0; 
        for(j = 0;j<(v+i)->n_areas_adj;j++){
            fscanf(f,"%s",((v+i)->aread[j]));
        }
        
        fscanf(f,"\n");
        i++;
       }
     
    fclose(f);
    return v;
}

//IMPRIME AREAS
void imprime(area pv,int tam){
       limpa_ecra();
    for(int i = 0;i<tam;i++){
         printf("Nome: %s\nCapadidade: %d\nNumero de Areas Adjacentes: %d\t",(pv+i)->nome,(pv+i)->capacidade,(pv+i)->n_areas_adj);
         printf("Areas adjacentes: ");
         for(int j = 0;j<(pv+i)->n_areas_adj;j++){
             printf(" %s ",(pv+i)->aread[j]);
         }
         putchar('\n');
         putchar('\n');
    }
    system("PAUSE");
   
}

//Guarda FICHEIRO
void guarda_ficheiro(area pv,char *nomeFich,int *total){
    FILE *f;
    int ret,rec;
    
    if((f = fopen("seg.txt","wt")) == NULL){
        printf("Erro a abir o ficheiro seg.txt para escrita!\n");
        return;
    }
    //passar tudo para o ficheiro, tudo o que está no vetor dinamico para um fichero auxiliar
    for(int i = 0;i<*total;i++){
        fprintf(f,"%s %d %d",(pv+i)->nome,(pv+i)->capacidade,(pv+i)->n_areas_adj);
        
        for(int j = 0;j<(pv+i)->n_areas_adj;j++){
            fprintf(f," %s",(pv+i)->aread[j]);
        }
        if(i != *total-1){
            fprintf(f,"\n");
        }
        
    }
    fclose(f);
    //Remove o ficheiro e depois renomeia o nome para o nomeFich
    ret = remove(nomeFich);
    if(ret == 0){
        printf("Ficheiro Apagado!\n");
    }else{
        printf("Erro a apagar Ficheiro!\n");
    }
    
    rec = rename("seg.txt",nomeFich);
     if(rec == 0){
        printf("Nome Mudado!\n");
    }else{
        printf("Erro a renomear Ficheiro!\n");
    }
}

//cria area
area cria_area(area pv,int *tam){
    int d,i,teste = 0,area_ad = 0;
    char string[DIM];
    limpa_ecra();
    printf("Intruduz o nome da nova area: ");
    scanf(" %[^\n]",string);
    
    for(i = 0;i<*tam;i++){
        if(strcmp((pv+i)->nome,string) ==  0){
            printf("Ja existe a area escolhida!\n");
            return pv;
        }
    }
    (*tam)++;
    
    pv = realloc(pv,(*tam) * sizeof(avea));
    
    d = *tam;
    d--;
    strcpy((pv+d)->nome,string);
    
    printf("Capacidade: ");
    scanf("%d",&(pv+d)->capacidade);
    
    do{
    printf("Numero de Areas adjacentes(Maximo 3): ");
    scanf("%d",&area_ad);
    }while(area_ad < 0 || area_ad > 3);
    
    (pv+d)->n_areas_adj = area_ad;
    
    for(i = 0;i<((pv+d)->n_areas_adj);i++){
        teste = 0;
        do{
            printf("Area Adjacente numero %d: ",(i+1));
            scanf(" %[^\n]",string);
            
            for(int j = 0;j<*tam;j++){
                if(strcmp((pv+j)->nome,string) == 0){ //verificar se existe uma aera com esse nome
                    //teste = 1;
                    //strcpy((pv+d)->aread[i],string);
                    
                  if((pv+j)->n_areas_adj < 3){
                     strcpy((pv+d)->aread[i],string);
                     strcpy((pv+j)->aread[(pv+j)->n_areas_adj],(pv+d)->nome);
                     (pv+j)->n_areas_adj += 1;
                      teste = 1;
                  }
                    
                    
                    
                }
            }
            
            if(teste == 0){
                printf("Area Nao existe!\n");
            }
            
        }while(teste == 0);
        
    }
    
    printf("Sucesso a criar area!\n");
    
    system("pause");
    return pv;
    
}

//eliminar area existente
area elimina_area(area pv,int *tam){
    
    area aux = NULL;
    char nome[100];
    
    int i,j,confirma = 0;
    
    limpa_ecra();
    printf("Insira o nome da area que pretende eliminar: ");
    scanf(" %[^\n]",nome);

    for(i = 0;i<*tam;i++){
        if(strcmp((pv+i)->nome,nome) == 0){
            if((pv+i)->lista == NULL){
                
                
                
                //Eliminar areas adjacentes nas outras areas
                
                for(int j = 0;j<(pv+i)->n_areas_adj;j++){
                    
                    for(int c = 0;c<*tam;c++){ //percorrer array dinamico das areas
                        if(strcmp((pv+c)->nome,(pv+i)->aread[j]) == 0){ // encontrar area que esta na adjacencia
                            for(int d = 0;d<(pv+c)->n_areas_adj;d++){
                                
                                if(strcmp((pv+i)->nome,(pv+c)->aread[d]) == 0){ // encontrar area adjacente e retirar e decrementar
                                    (pv+c)->n_areas_adj -= 1;
                                    strcpy((pv+c)->aread[d],(pv+c)->aread[(pv+c)->n_areas_adj]);
                                    
                                }
                                
                            }
                            
                            
                            
                            
                            
                            
                        }
                        
                    }
                     
                }
                
                (*tam)--;
                (pv+i)->n_areas_adj = (pv+*tam)->n_areas_adj;
                (pv+i)->capacidade = (pv+*tam)->capacidade;
                (pv+i)->lista = (pv+*tam)->lista;
                for(j = 0;j<(pv+i)->n_areas_adj;j++){
                strcpy((pv+i)->aread[j],(pv+*tam)->aread[j]);
                }
                strcpy((pv+i)->nome,(pv+*tam)->nome);
                
                
                
                
                
                
                pv = realloc(pv,sizeof(avea)* (*tam));
                printf("%s Eliminada com sucesso!\n",nome);
                confirma = 1;
            }
        }
    }
    
    if(confirma == 0){
        printf("Area Nao pode Ser Eliminada!\n");
    }
    
    aux = pv;
    system("PAUSE");
    
   return aux;
}