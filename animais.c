/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "areasc.h"
#include "animais.h"

//Ler Ficheiro dos animais inicio da execucao VERIFICAR SE ESTá a ler corretamente
int le_fich(char *nomeFich,area pv,int *tam){
    FILE *f;
    struct animais c;
    animas aux;
    int i;
    
    if((f = fopen(nomeFich,"rb")) == NULL){
        printf("ERRO A ABRIR O FICHEIRO dos animais para leitura!\n");
        return 0;
    }
    
    while(fread(&c,sizeof(struct animais),1,f)){
        
        for(i = 0;i<*tam;i++){
           if(strcmp(c.area,(pv+i)->nome) == 0){
               //compara peso
               if((pv+i)->ocupacao + c.peso <= (pv+i)->capacidade){
                   
               //Implementar  caso o peso da area ultrupasse a capacidade
               aux = malloc(sizeof(struct animais));
             
            if(aux == NULL){
                   printf("Erro a alocar memoria!\n");
                   return 0;
               }
               
                
               (pv+i)->ocupacao += c.peso;
               aux->peso = c.peso;
               strcpy(aux->area,c.area);
               strcpy(aux->especie,c.especie);
               strcpy(aux->mae,c.mae);
               strcpy(aux->n_serie,c.n_serie);
               strcpy(aux->nome,c.nome);
               strcpy(aux->pai,c.pai);
               
               
               if((pv+i)->lista == NULL){
                   (pv+i)->lista = aux;
               }else{
                   
                   aux->prox = (pv+i)->lista;
                   (pv+i)->lista = aux;
                   
                   
               }
               
           }
           }
        }

        
        
    }

    
    
    fclose(f);
    return 1;
}

//Grava informação sobre animais fim da execução
void grava_fich(char *nomeFich,area pv,int *tam){
    FILE *f;
    struct animais *c;
    struct animais aux;
    
    if(remove(nomeFich) == 0){
        printf("sucesso a remover!\n");
    }
    
    if((f = fopen(nomeFich,"wb")) == NULL){
        printf("ERRO A CRIAR O %s para escrita!\n",nomeFich);
        return;
    }
    
    for(int i = 0;i<*tam;i++){
        if((pv+i)->lista != NULL){
            c = (pv+i)->lista;
            while(c != NULL){
                 
                               
               
                strcpy(aux.area,c->area);
                strcpy(aux.especie,c->especie);
                strcpy(aux.mae,c->mae);
                strcpy(aux.pai,c->pai);
                strcpy(aux.n_serie,c->n_serie);
                strcpy(aux.nome,c->nome);
                aux.peso = c->peso;
                  
                
                //escreve no ficheiro
                fwrite(&aux,sizeof(struct animais),1,f);
                //passa para a proxima
                printf("Passado o animal: %s\n",aux.nome);
                c = c->prox;
               
            }
            
        }
        
    }
    
    printf("Guardado os animais com sucesso!\n");
    
    fclose(f);
}

//Adicionar animais via ficheiro
espec add_animais(area pv,int *tam,espec dx,int *dime){
   
   FILE *f;
   char nome[100],ola[100];
   animas c;
   struct animais aux;
   int confirma = 0,pos;

   int i,conf = 0;
   
   limpa_ecra();
   
   printf("BEM VINDO AO ADICIONA ANIMAIS!\n\n");
   
   printf("Insira o nome do ficheiro: ");
   scanf(" %99[^\n]",nome);
   
   if((f = fopen(nome,"rt")) == NULL){
       printf("ERRO A ABRIR O FICHEIRO!\n");
       return dx;
   }
  
  

   while(fscanf(f,"%s %s %d %s\n",aux.especie,aux.nome,&aux.peso,aux.area) == 4){
            conf = 0;
            confirma = 0;
       for(i = 0;i<*tam;i++){
           if(strcmp(aux.area,(pv+i)->nome) == 0){

  if((pv+i)->ocupacao + aux.peso <= (pv+i)->capacidade){

                c = malloc(sizeof(struct animais));
                if(c == NULL){
                    printf("Erro a abrir alocar memoria!\n");
                    fclose(f);
                    return dx;
                }
                   
                strcpy(c->nome,aux.nome);
                strcpy(c->especie,aux.especie);
                strcpy(c->area,aux.area);
                c->peso = aux.peso;
                
                //Verificar especie e se nao existir criar um vetor dinamico
                for(int x = 0;x<*dime;x++){
                    
                   if(strcmp((dx+x)->nome,c->especie) == 0){
                       confirma = 1;
                       pos = x;
                    }
                   
                }
                
                if(confirma == 1){
                    strcpy(c->n_serie,(dx+pos)->n_serie);
                }else{
                    (*dime)++;
                    dx = realloc(dx,*dime * sizeof(struct especie));
                    if(dx == NULL){
                        printf("ERRO a alocar memoria!\n");
                        fclose(f);
                        return dx;
                    }
                    
                    
                    
                    //fazer confirmacao
                    do{

                     printf("Intruduza o n_serie desejado para a especie %s: ",c->especie);
                     scanf(" %[^\n]",ola);
                   confirma = 0;
                  for(int y = 0;y<*dime;y++){
                   if(strcmp((dx+y)->n_serie,ola) == 0){
                       confirma = 1;
                       printf("Ja existe o Numero de Serie %s!\n",ola);
                    }
                   
                }
                     
                     
                     
                    }while(confirma == 1);
                    
                    
                    strcpy((dx+(*dime)-1)->nome,c->especie);
                    strcpy((dx+(*dime)-1)->n_serie,ola);
                    strcpy((c->n_serie),ola);
                    
                    
                    
                }
                
                
                
                       
                
           
                if((pv+i)->lista == NULL){
                    c->prox = NULL;
                  
                }else{
                    c->prox = (pv+i)->lista;  
                }
                
                (pv+i)->lista = c;
                (pv+i)->ocupacao += c->peso;
                conf = 1;
                i = *tam + 1;
 }
               
               
           
               
           }
           

           
       }
            
             if(conf == 0){
            printf("ERRO a criar animal %s\n",aux.nome);
           }else{
               printf("Sucesso a criar animal %s\n",aux.nome);
           }


       
       
       
   }
   
 
   
    
   fclose(f); 
   printf("\nA sair da funcao adicionar animais!\n");
   system("Pause");
   return dx;

}

//Listagem completa de todos os animais do zoo
void listar_animais(area pv,int *tam){
    
    animas c;
    
    limpa_ecra();
    printf("Listagem de animais!\n");
    for(int i = 0;i<*tam;i++){
        //percorre todas as areas e imprime todos os animais que se encontram nelas
        if((pv+i)->lista != NULL){
            c = (pv+i)->lista;
            while(c != NULL){
             printf("Nome: %s\tN_Serie: %s\tEspecie: %s\t%s\tPeso: %dKg\n",c->nome,c->n_serie,c->especie,c->area,c->peso);
             c = c->prox;
            }           
            
        }
        
        
    }
    system("Pause");
    
    
}

//Listagem dos animais que se encontram numa determinada localizacao
void listar_local(area pv,int *tam){
    
    char nome[100];
    int i = 0;
    struct animais *c;
    limpa_ecra();
    
    printf("Nome da area: ");
    scanf(" %[^\n]",nome);
    
 printf("Listagem da area: %s\n",nome);
    for(i = 0;i<*tam;i++){
//encontra AREA e depois imprime a informacao sobre os animais dessa area
        if(strcmp(nome,(pv+i)->nome) == 0){
            if((pv+i)->lista != NULL){
                c = (pv+i)->lista;
                while(c != NULL){
                    printf("Nome: %s\tN_Serie: %s\tEspecie: %s\t%s\tPeso: %dKg\n",c->nome,c->n_serie,c->especie,c->area,c->peso);
                    c = c->prox;
                }
                
                
                
            }
            
        }
        
    }
    
    system("Pause");
    
}

//Listagem dos animais de uma determinada especie
void listar_especie(area pv,int *tam){
    
    char nome[100];
    struct animais *c;
    int i = 0;
    
    printf("Nome da especie: ");
    scanf(" %[^\n]",nome);
    
    limpa_ecra();
    
    printf("Lista de Animais da especie %s!\n",nome);
    for(i = 0;i<*tam;i++){
        
        if((pv+i)->lista != NULL){
            
            c = (pv+i)->lista;
            
            while(c != NULL){
                if(strcmp(c->especie,nome) == 0){
                    printf("Nome: %s\tN_Serie: %s\tEspecie: %s\t%s\tPeso: %dKg\n",c->nome,c->n_serie,c->especie,c->area,c->peso);
                }
                c = c->prox;
                
                
            }
            
            
        }
        
        

    }
            putchar('\n');
    
    
        system("PAUSE");
    
}

//listagem completa dos animais
void listar_completa(area pv,int *tam){
    
    int i,conf = 0,j,d;
    char nome[100];
    animas aux = NULL,seg = NULL,dig = NULL,outro = NULL;
    limpa_ecra();
    printf("Bem Vindo a Listagem completa da informacao sobre um animal!\n");

    printf("Intruduza o nome do animal: ");
    scanf(" %[^\n]",nome);
    
    //percorrer as areas
    for(i = 0;i<*tam;i++){
        if((pv+i)->lista != NULL){ 
            aux = (pv+i)->lista; //aux aponta para a lista
            while(aux != NULL){ // enquanto o aux for diferente de NULL ,ou seja possuir animais na area
               
                if(strcmp(nome,aux->nome) == 0){ // comparar com o nome introduzido pelo o utilizador
                    
                    
                    //em seguida imprimir informacao !
                    conf = 1;
                    printf("Nome: %s\tN_Serie: %s\tEspecie: %s\t%s\tPeso: %dKg\n",aux->nome,aux->n_serie,aux->especie,aux->area,aux->peso);
                    
                  
                    printf("Familia: Mae: %s\tPai: %s\n",aux->mae,aux->pai);
                    
                    printf("Resto da familia: ");
                    dig = aux->filho;
                    while(dig != NULL){
                        printf("%s\t",dig->nome);
                        dig = dig->filho_p;
                    }
                    seg = aux->filhom;
                    while(seg != NULL){
                         printf("%s\t",seg->nome);
                        seg = seg->filhom_p;
                    }
                    
                    putchar('\n');
                    
                    for(j = 0;j<*tam;j++){
                        if((pv+j)->lista != NULL){
                            outro = (pv+j)->lista;
                            while(outro != NULL){
                                
                                if(strcmp(aux->mae,outro->nome) == 0){
                                    
                                    printf("Avos: %s\t %s",outro->mae,outro->pai);
                                      putchar('\n');
                                     seg = outro->filho;
                                    printf("Restante da Familia: ");
                                    while(seg != NULL){
                                        
                                        printf("%s\t",seg->nome);
                                        
                                        seg = seg->filho_p;
                                    }
                                    
                                    
                                    seg = outro->filhom;
                                    
                                    while(seg != NULL){
                                        
                                        printf("%s\t",seg->nome);
                                        
                                        seg = seg->filhom_p;
                                    }
                                    
                                    
                                }
                                
                                outro = outro->prox;
                            }
                            
                        }
                        
                    }
                    putchar('\n');
                    
                    
 
                    
                      for(j = 0;j<*tam;j++){
                        if((pv+j)->lista != NULL){
                            outro = (pv+j)->lista;
                            while(outro != NULL){
                                
                                if(strcmp(aux->pai,outro->nome) == 0){
                                    
                                    printf("Avos: %s\t %s\n",outro->mae,outro->pai);
                                    putchar('\n');
                                    seg = outro->filho;
                                    while(seg != NULL){
                                        
                                        printf("%s\t",seg->nome);
                                        
                                        seg = seg->filho_p;
                                    }
                                    
                                    
                                    seg = outro->filhom;
                                    
                                    while(seg != NULL){
                                        
                                        printf("%s\t",seg->nome);
                                        
                                        seg = seg->filhom_p;
                                    }
                                    
                                    
                                   
                                }
                                
                                outro = outro->prox;
                            }
                            
                        }
                        
                    }
                    
                }
                aux = aux->prox;
                
            }
     
        }
    
    }
    
    if(conf == 0){
        printf("ANIMAL NAO ENCONTRADO!\n");
    }
    
    system("PAUSE");
}

//transferir animal
void transfer_animal(area pv,int *tam){
    
    char nome[100],area[100];
    int i = 0,confirma = 0;
    char c;
    animas aux,seg,dig;
    
    limpa_ecra();
    printf("Bem Vindo ao Transfere Animal!\n");
    
    printf("Intruduza o nome do animal que pretende mover: ");
    scanf(" %[^\n]",nome);
    
    //Percorre as Areas
    for(i = 0;i<*tam;i++){
        
        //Se a area tiver lista     
    if((pv+i)->lista!= NULL){
            //igualo aux ao inicio da lista
        aux = (pv+i)->lista;
        seg = NULL;
            //enquanto ouver lista
            while(aux != NULL){
                //comparo o nome do animal com o nome do aux
                if(strcmp(aux->nome,nome) == 0){
                    dig = aux;
                    //Faco enquanto Confirma != 1
                    do{
                     //peco o nome da area para onde quer mover
                    printf("Insira o nome da area: ");
                    scanf(" %99[^\n]",area);
                    //percorro o vetor das areas adjc
                    for(int j = 0;j<((pv+i)->n_areas_adj);j++){
                      //se encontrar a area
                        if(strcmp(area,(pv+i)->aread[j]) == 0){
                            //percorro agora a area para encontrar a area para mover
                            for(int d = 0;d<*tam;d++){
                                //encontrei
                                if(strcmp(area,(pv+d)->nome) == 0){
                                    //verifico se cabe na area
                                    if((pv+d)->ocupacao + dig->peso <= (pv+d)->capacidade){
                                        
                              //Printf Vou Remover da primeira area 
                            if(seg == NULL){
                             (pv+i)->lista = dig->prox;     
                            }else{
                                seg->prox = dig->prox; 
                            }
                            //retiro ocupacao
                            (pv+i)->ocupacao -= dig->peso;
                            
                            //comparo se a area tem lista
                            if((pv+d)->lista == NULL){
                                (pv+d)->lista = dig;
                                dig->prox = NULL;
                            }else{
                                dig->prox = (pv+d)->lista;
                                (pv+d)->lista = dig;
                                
                            }
                            strcpy(dig->area,(pv+d)->nome);
                             
                            (pv+d)->ocupacao += dig->peso;
                            limpa_ecra();
                            printf("Animal com o nome %s, foi movido com sucesso para a area %s\n",nome,area);
                            system("Pause");
                            return;
                                        
                                        
                                        
                                    }
                                    
                                }
                            }
                            
                            
                            
                            
                        }
                    }
                    
                    limpa_ecra();
                    printf("Tem de inserir outra area!\n");
                    printf("O problema pode ser por a area nao ser adjacente, ou por nao ter capacidade para outro animal!\n");
                    
                    printf("Deseja sair(S para sair)?  ");
                    scanf(" %c",&c);
                    limpa_ecra();
                    if(c == 'S' || c == 's'){
                        return;
                    }
   
                    }while(confirma != 1);                    
                    
                }
                
                seg = aux;
                aux = aux->prox;
            }
            
            
            
        }
        
        
    }
    
    
    
    
}

//ler ficheiro de especies
espec le_especie(int *dime,char *nomeFich){
    
    FILE *f;
    espec pv = NULL;
    struct especie c;
    *dime = 0;
    
    if((f = fopen(nomeFich,"rb")) == NULL){
        printf("ERRO A ABRIR O FICHEIRO PARA LEITURA!\n");
        return pv;
    }
    
    //enqaunto ler o ficheiro
    while(fread(&c,sizeof(struct especie),1,f)){
        (*dime)++;
        //incrementa a dimensao da especie
        
        pv = realloc(pv,(*dime) * sizeof(struct especie)); // alocar memoria do tamanho da dimensao da especie
        if(pv == NULL){
            printf("ERRO A REALOCAR MEMORIA!\n");
            fclose(f);
            return pv;
        }
        
        
        //copiar para o array a especie guardada em ficheiro binario
        strcpy((pv+(*dime) - 1)->nome,c.nome);
        strcpy((pv+(*dime) - 1)->n_serie,c.n_serie);
        
    }
    
    
    
    fclose(f);
    return pv;
}

//gravar especies
void grava_especie(espec pv,int *dime,char *nomeFich){
    
    FILE *f,*p;
    struct especie c;

    
    
    if((p = fopen("auxiliar.dat","wb")) == NULL){
        printf("ERRO A ABRIR O FICHEIRO !");
        return;
    }
    
   
    //enquanto tiver especie grava
    for(int i = 0;i<*dime;i++){
        strcpy(c.nome,(pv+i)->nome);
        strcpy(c.n_serie,(pv+i)->n_serie);
        fwrite(&c,1,sizeof(struct especie),p);   
    }
    
    //remove ficheiro no final e depois renomeia para o antigo nomeFich
    if(remove(nomeFich) == 0){
        printf("Sucesso a remover!\n");
    }
    fclose(p);
    rename("auxiliar.dat",nomeFich);
    
}

//Nascimento de um animal
void nasc_animal(area pv,int *tam){
    int animais,i,j,conf = 0,sair = 0,peso = 0;
    char nome_1[100] = {"\0"},nome_2[100] = {"\0"};
    animas aux = NULL,seg = NULL,novo = NULL; 
    
    limpa_ecra();
    printf("Bem vindo ao nascimento de um animal!\n");
    
    do{
    printf("Numero de projenitores(1 ou 2): ");
    scanf("%d",&animais);   
    }while(animais < 0 && animais >2);
    
    //Se for só um pai
    if(animais == 1){
        
        do{
            printf("Nome do projenitor: ");
            scanf(" %[^\n]",nome_1);
            
            //percorrer o vetor areas a procura do projenitor
            for(i = 0;i<*tam;i++){
                if((pv+i)->lista != NULL){
                 aux = (pv+i)->lista;
                 
                 while(aux != NULL){
                     if(strcmp(nome_1,aux->nome) == 0){
                         
                         seg = malloc(sizeof(struct animais));
                         if(seg == NULL){
                             printf("Erro a alocar memoria!\n");
                             return;
                         }
                         
                         
                         printf("Nome do novo animal: ");
                         scanf(" %[^\n]",seg->nome);
                         
                       
                         
                         //verificar erros e ver erros com o peso
                         
                         strcpy(seg->pai,nome_1);
                         strcpy(seg->mae,nome_1);
                         strcpy(seg->area,aux->area);   
                
                         seg->peso = aux->peso * 0.20;


                         aux->peso = aux->peso * 0.80;
                         strcpy(seg->especie,aux->especie);
                         strcpy(seg->n_serie,aux->n_serie);
                         
                         //depois ver de atribuir automaticamente um novo identificar unico dentro da especie a que pertence
                         
                         seg->prox = (pv+i)->lista;
                         (pv+i)->lista = seg;
                         
                         seg->filho_p = aux->filho;
                         aux->filho = seg;
                         
                         
                         conf = 1;
                        
                         printf("Sucesso a criar cria!\n");
                         system("pause");
                         return;
                     }
                     
                 aux = aux->prox;
                    
                }
                
            }
            }
            
            
            
            printf("Nao encontrado o projenitor!\n");
            
            printf("Pretende sair? Prima 1: ");
            scanf(" %d",&sair);
            
                    
            if(sair == 1){
                conf = 1;
            }
            
            system("pause");
        
        }while(conf == 0);
        
              
                
                
        
    }else if(animais == 0){
        return;
    }
  else{ //2 animais
       

        limpa_ecra();
        printf("Nome do primeiro projenitor: ");
        scanf(" %[^\n]",nome_1);
        
        printf("Nome do Segundo projenitor: ");
        scanf(" %[^\n]",nome_2);
        
        //percorrer as areas
        for(i = 0;i<*tam;i++){
            aux = (pv+i)->lista; //Igualar o aux a lista, para percorrer a lista ligada
            seg = (pv+i)->lista; 
            while(aux != NULL){
                //encontrar o nome do projenitor 1
                if(strcmp(nome_1,(aux->nome)) == 0){
                   
                    while(seg != NULL){
                        
                         if(strcmp(nome_2,(seg->nome)) == 0){
                        
                             if(strcmp(aux->especie,seg->especie) == 0){
                                 
                                 novo = malloc(sizeof(struct animais));
                                 //alocar memoria para add o animal
                                 if(novo == NULL){
                                     printf("Erro a alocar memoria!\n");
                                     return;
                                 }
                                
                                 //passar informacao para o novo animal
                                 printf("Nome da Cria: ");
                                 scanf(" %[^\n]",novo->nome);
                                 
                                 strcpy(novo->mae,aux->nome);
                                 strcpy(novo->pai,seg->nome);
                                 strcpy(novo->especie,seg->especie);
                                 strcpy(novo->n_serie,seg->n_serie);
                                 
                                
                                 novo->peso = seg->peso * 0.20 + aux->peso * 0.20;
                                 seg->peso = seg->peso * 0.80;
                                 aux->peso = aux->peso * 0.80;
                                 strcpy(novo->area,seg->area);
                                 
                                 
                                 
                                 novo->prox = (pv+i)->lista;
                                 (pv+i)->lista = novo;      
                                 
                                 //VER COMO LINKAR OS IRMAOS e os filhos
                                novo->filho_p = seg->filho;
                                seg->filho = novo;
                                 
                                novo->filhom_p = aux->filho;
                                aux->filhom = novo;
                                 
                                 
                                 
                                 printf("Sucesso a criar cria!\n");
                                 system("PAUSE");
                                 return;
                                 
                             }else{
                                 
                                 printf("Intruduza diferentes projenitores! Especie e' diferente!\n");
                                 system("Pause");
                                 
                                 
                             }
                        
                        
                             
                        }
                    
                        
                        
                         seg = seg->prox;
                    }
                   
                    
                }
                
                
                 aux = aux->prox; // avancar na lista
            }
            
        }
        
        
        if(conf == 0){
            printf("ERRO ANIMAIS NAO ENCONTRADOS!\n");
        }
        system("PAUSE");
            
    }
    
    
    system("pause");
}

//eliminar animal
void eliminar_animal(area pv,int *tam){
    char nome[100];
    int i = 0;
    animas aux = NULL,seg = NULL,dig = NULL;
    
    
    limpa_ecra();
    printf("Bem Vindo ao Elimina Animal!\n");
    
    printf("Intruduza O nome do animal que pretende eliminar: ");
    scanf(" %99[^\n]",nome);
    
    for(i = 0;i<*tam;i++){
        if((pv+i)->lista != NULL){
            aux = (pv+i)->lista;
            while(aux != NULL){
                //procura animal e depois apaga-o no final, chama a funcao para linkar familias que é
                //para atualizar e remover todos da familia, menos o nome dele como pai ou mae
                if(strcmp(aux->nome,nome) == 0){
                    
                    if(seg != NULL){  
                      seg->prox = aux->prox;
                    }else{
                        (pv+i)->lista = aux->prox;
                            
                    }
                    
                    (pv+i)->ocupacao -= aux->peso; 
                    free(aux);
                    printf("SUCESSO A REMOVER ANIMAL!\n");
                    system("PAUSE");
                    //CHAMar FUNCAO DE LINKAR FAMILIAS
                    return;
                }
                
                
                
                seg = aux;
                aux = aux->prox;
            }
            
            
        }
        
        
        
    }
    
    
    printf("Intruduza outro animal!\n");
    system("PAUSE");
    
    
    
}


//Associar familia

void associa_fam(area pv,int *tam){
    
    //Funcao auxiliar para associar familia
    animas aux = NULL,seg = NULL;
    int i = 0,j = 0;
    
    
    
    for(i = 0;i<*tam;i++){ //percorrer areas
        
        if((pv+i)->lista != NULL){ //se tiver lista
            aux = (pv+i)->lista;
            while(aux != NULL){ // enquanto houver animal na area
                
                for(j = 0;j<*tam;j++){ //percorrer outra vez a lista
                    
                    if((pv+j)->lista != NULL){
                        //encontrar os pais
                        seg = (pv+j)->lista;
                        while(seg != NULL){
                            if(strcmp(seg->nome,aux->mae) == 0){
                                aux->filhom_p = seg->filhom;
                                seg->filhom = aux;
                                
                                
                                
                            }
                            
                            //verificar se é pai ou mae
                             if(strcmp(seg->nome,aux->pai) == 0){
                                //Linkar listas 
                                aux->filho_p = seg->filho;
                                seg->filho = aux;
                                
                                
                                
                            }
                            //andar para o proximo na lista
                            seg = seg->prox;
                        }
                        
                    }
                    
                    
                }
                
                aux = aux->prox;
            }
            
        }
        
    }
   
    
}