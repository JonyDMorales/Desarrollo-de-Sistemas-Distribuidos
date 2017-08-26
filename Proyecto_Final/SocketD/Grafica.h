#ifndef GRAFICA_H_
#define GRAFICA_H_

#include <iostream>
#include <vector>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include "Funciones.h"
using namespace std;

class Grafica{

  private:
    Funciones gfx_function;
    bool tecla[6];  //Arreglo para saber si una tecla de dirección se ha presionado
  public: 
    int pos_x, pos_y;
    int barcos[5][4];
    int coordenadas[9][3];
    int level;
    Grafica();
    int inicializaGrafica(int level);
    void print_time();
    int impresion();
    void tablero5x5();
    void tablero7x7();
    void tablero10x10();
    void Barcos_medianosG();
    void Barcos_grandesG();
    void Barcos_pequenosG();
    void Barcos_medianos();
    void Barcos_grandes();
    void Barcos_pequenos();
    void Barcos_medianos5();
    void Barcos_grandes5();
    void Barcos_pequenos5();
    void Numeros5x5();
    void Numeros7x7();
    void Numeros10x10();
    void barco_Bomba(int x, int y);
    void Posicionamiento5x5(int x, int y, int c, int m);
    //void dispSiete(char val_num);
    void gfx_clear();
};

#endif