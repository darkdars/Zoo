/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   estruturas.h
 * Author: jhssi
 *
 * Created on 28 de Abril de 2017, 13:02
 */

#ifndef HHH
#define HHH 
#define DIM 100

typedef struct areas *area,avea;
typedef struct animais animal,*animas;
typedef struct especie *espec;

struct areas{
    char nome[DIM];
    int capacidade;
    int ocupacao;
    int n_areas_adj;
    char aread[3][100];
    animas lista;
    
};

struct animais{
    char especie[50];
    char n_serie[50];
    char nome[100];
    int peso;
    char pai[100];
    char mae[100];
    char area[100];
    animas prox;
    animas filho;
    animas filho_p;
    animas filhom;
    animas filhom_p;
};


struct especie{
    char nome[50];
    char n_serie[50];
};


#endif