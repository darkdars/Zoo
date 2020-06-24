/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   animais.h
 * Author: jhssi
 *
 * Created on 3 de Junho de 2017, 14:46
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "areasc.h"
      
#ifndef ANIMAIS_H
#define ANIMAIS_H

int le_fich(char *nomeFich,area pv,int *tam);

void grava_fich(char *nomeFich,area pv,int *tam);

//funcao adiciona animais
//void add_animais(area pv,int *tam);
espec add_animais(area pv,int *tam,espec dx,int *dime);

//LISTAGEM COMPLETA DE ANIMAIS
void listar_animais(area pv,int *tam);
    
//LISTAGEM DE animais por AREAS
void listar_local(area pv,int *tam);
    
//LISTAGEM DE animais por especie
void listar_especie(area pv,int *tam);

//listagem completa relativa a um animal
void listar_completa(area pv,int *tam);

//Transfer animais de area para area
void transfer_animal(area pv,int *tam);

//Le especies
espec le_especie(int *dime,char *nomeFich);

//Grava Especies
void grava_especie(espec pv,int *dime,char *nomeFich);

//nascimento de um animal
void nasc_animal(area pv,int *tam);

//Elimina animal
void eliminar_animal(area pv,int *tam);

//associa familia
void associa_fam(area pv,int *tam);



#endif /* ANIMAIS_H */

