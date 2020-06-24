/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   areasc.h
 * Author: jhssi
 *
 * Created on 19 de Maio de 2017, 0:21
 */

#ifndef AREASC_H
#define AREASC_H
#include "estruturas.h"
#include "animais.h"



area le_ficheiro(char *nomeFich,int *total);
void imprime(area pv,int tam);
void guarda_ficheiro(area pv,char *nomeFich,int *total);
area cria_area(area pv,int *tam);
void limpa_ecra();
area elimina_area(area pv,int *tam);


#endif /* AREASC_H */

