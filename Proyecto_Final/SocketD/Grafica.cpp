#include "Grafica.h"
#include "Funciones.h"

int casilla_1 = 160;
int casilla_2 = 120;
int casilla_3 = 80;
int margen_1 = 10;
int offset = 50;

Grafica::Grafica() 
{ 
}

void Grafica::tablero5x5()
{
    gfx_function.gfx_fill_rectangle(50,50,10,860); 
    gfx_function.gfx_fill_rectangle(220,50,10,860); 
    gfx_function.gfx_fill_rectangle(390,50,10,860); 
    gfx_function.gfx_fill_rectangle(560,50,10,860); 
    gfx_function.gfx_fill_rectangle(730,50,10,860); 
    gfx_function.gfx_fill_rectangle(900,50,10,860); 
 

    //Grafica y
    gfx_function.gfx_fill_rectangle(50,50,860,10); 
    gfx_function.gfx_fill_rectangle(50,220,860,10); 
    gfx_function.gfx_fill_rectangle(50,390,860,10); 
    gfx_function.gfx_fill_rectangle(50,560,860,10); 
    gfx_function.gfx_fill_rectangle(50,730,860,10); 
    gfx_function.gfx_fill_rectangle(50,900,860,10); 
    
  
   
}

void Grafica::tablero7x7()
{
    //char *a;
    //memcpy(&a,'A',sizeof(a));
    gfx_function.gfx_fill_rectangle(50,50,10,910); 
    gfx_function.gfx_fill_rectangle(180,50,10,910); 
    gfx_function.gfx_fill_rectangle(310,50,10,910); 
    gfx_function.gfx_fill_rectangle(440,50,10,910); 
    gfx_function.gfx_fill_rectangle(570,50,10,910); 
    gfx_function.gfx_fill_rectangle(700,50,10,910);
    gfx_function.gfx_fill_rectangle(830,50,10,910);
    gfx_function.gfx_fill_rectangle(960,50,10,910); 
    //gfx_function.gfx_text(25,64,a);

    //Grafica y
    gfx_function.gfx_fill_rectangle(50,50,910,10); 
    gfx_function.gfx_fill_rectangle(50,180,910,10); 
    gfx_function.gfx_fill_rectangle(50,310,910,10); 
    gfx_function.gfx_fill_rectangle(50,440,910,10); 
    gfx_function.gfx_fill_rectangle(50,570,910,10); 
    gfx_function.gfx_fill_rectangle(50,700,910,10); 
    gfx_function.gfx_fill_rectangle(50,830,910,10); 
    gfx_function.gfx_fill_rectangle(50,960,910,10); 
    
  
   
}

void Grafica::tablero10x10()
{
    gfx_function.gfx_fill_rectangle(50,50,5,905); 
    gfx_function.gfx_fill_rectangle(140,50,5,905); 
    gfx_function.gfx_fill_rectangle(230,50,5,905); 
    gfx_function.gfx_fill_rectangle(320,50,5,905); 
    gfx_function.gfx_fill_rectangle(410,50,5,905); 
    gfx_function.gfx_fill_rectangle(500,50,5,905); 
    gfx_function.gfx_fill_rectangle(590,50,5,905); 
    gfx_function.gfx_fill_rectangle(680,50,5,905); 
    gfx_function.gfx_fill_rectangle(770,50,5,905); 
    gfx_function.gfx_fill_rectangle(860,50,5,905); 
    gfx_function.gfx_fill_rectangle(950,50,5,905); 
 

    //Grafica y
    gfx_function.gfx_fill_rectangle(50,50,905,5); 
    gfx_function.gfx_fill_rectangle(50,140,905,5); 
    gfx_function.gfx_fill_rectangle(50,230,905,5);
    gfx_function.gfx_fill_rectangle(50,320,905,5); 
    gfx_function.gfx_fill_rectangle(50,410,905,5); 
    gfx_function.gfx_fill_rectangle(50,500,905,5); 
    gfx_function.gfx_fill_rectangle(50,590,905,5);
    gfx_function.gfx_fill_rectangle(50,680,905,5); 
    gfx_function.gfx_fill_rectangle(50,770,905,5); 
    gfx_function.gfx_fill_rectangle(50,860,905,5); 
    gfx_function.gfx_fill_rectangle(50,950,905,5); 
   
}

void Grafica::Posicionamiento5x5(int x, int y, int c, int m){
    if(x > 1){
        pos_x = (x - 1) * c + c/2 + (x * m);
    }else{
        pos_x = c/2 + m;
    }

    if(y > 1){
        pos_y = (y - 1) * c + c/2 + (y * m);
    }else{
        pos_y = c/2 + m;
    }
    pos_x = pos_x + offset;
    pos_y = pos_y + offset;

}

void Grafica::Barcos_pequenosG(){
    gfx_function.gfx_fill_ellipse(pos_x, pos_y, 20, 20);
   // gfx_function.gfx_fill_ellipse(920, 905, 20, 30);
}

void Grafica::Barcos_medianosG(){
    gfx_function.gfx_fill_ellipse(pos_x, pos_y + 45, 20, 45);
   // gfx_function.gfx_fill_ellipse(780, 500, 20, 80);
}

void Grafica::Barcos_grandesG(){
    gfx_function.gfx_fill_ellipse(pos_x, pos_y + 90, 20, 90);
    
}

void Grafica::Barcos_pequenos(){
    gfx_function.gfx_fill_ellipse(pos_x, pos_y, 20, 30);
   // gfx_function.gfx_fill_ellipse(920, 905, 20, 30);
}

void Grafica::Barcos_medianos(){
    gfx_function.gfx_fill_ellipse(pos_x, pos_y + 65, 20, 65);
   // gfx_function.gfx_fill_ellipse(780, 500, 20, 80);
}

void Grafica::Barcos_grandes(){
    gfx_function.gfx_fill_ellipse(pos_x, pos_y + 130, 20, 130);
    
}

void Grafica::Barcos_pequenos5(){
    gfx_function.gfx_fill_ellipse(pos_x, pos_y, 30, 60);
    //gfx_function.gfx_fill_ellipse(pos_x, pos_y, 30, 60);  
}

void Grafica::Barcos_medianos5(){
    gfx_function.gfx_fill_ellipse(pos_x, pos_y + 85, 30, 85);
    //gfx_function.gfx_fill_ellipse(pos_x, pos_y, 30, 120);
}

void Grafica::Barcos_grandes5(){
   gfx_function.gfx_fill_ellipse(pos_x, pos_y + 170, 30, 170);
    
}

void Grafica::Numeros5x5(){
    gfx_function.gfx_fill_rectangle(25,95,5,40); //1

    gfx_function.gfx_fill_rectangle(10,280,30,5); //2
    gfx_function.gfx_fill_rectangle(10,300,30,5); //2
    gfx_function.gfx_fill_rectangle(10,320,30,5); //2
    gfx_function.gfx_fill_rectangle(35,280,5,20); //2
    gfx_function.gfx_fill_rectangle(10,300,5,20); //2
    
    gfx_function.gfx_fill_rectangle(10,460,30,5); //2
    gfx_function.gfx_fill_rectangle(10,480,30,5); //2
    gfx_function.gfx_fill_rectangle(10,500,30,5); //2
    gfx_function.gfx_fill_rectangle(35,460,5,20); //2
    gfx_function.gfx_fill_rectangle(35,480,5,20); //2

    gfx_function.gfx_fill_rectangle(10,660,30,5); //2
    gfx_function.gfx_fill_rectangle(10,640,5,20); //2
    gfx_function.gfx_fill_rectangle(35,640,5,20); //2
    gfx_function.gfx_fill_rectangle(35,660,5,20); //2

    gfx_function.gfx_fill_rectangle(10,860,30,5); //2
    gfx_function.gfx_fill_rectangle(10,820,30,5); //2
    gfx_function.gfx_fill_rectangle(10,840,30,5); //2
    gfx_function.gfx_fill_rectangle(10,820,5,20); //2
    gfx_function.gfx_fill_rectangle(35,840,5,20); //2  

}

void Grafica::Numeros7x7(){
    gfx_function.gfx_color(2);
    gfx_function.gfx_fill_rectangle(25,95,5,30); //1

    gfx_function.gfx_fill_rectangle(10,220,30,5); //2
    gfx_function.gfx_fill_rectangle(10,240,30,5); //2
    gfx_function.gfx_fill_rectangle(10,260,30,5); //2
    gfx_function.gfx_fill_rectangle(35,220,5,20); //2
    gfx_function.gfx_fill_rectangle(10,240,5,20); //2
    
    gfx_function.gfx_fill_rectangle(10,340,30,5); //2
    gfx_function.gfx_fill_rectangle(10,360,30,5); //2
    gfx_function.gfx_fill_rectangle(10,380,30,5); //2
    gfx_function.gfx_fill_rectangle(35,340,5,20); //2
    gfx_function.gfx_fill_rectangle(35,360,5,20); //2

    
    gfx_function.gfx_fill_rectangle(10,480,30,5); //2
    gfx_function.gfx_fill_rectangle(10,460,5,20); //2
    gfx_function.gfx_fill_rectangle(35,460,5,20); //2
    gfx_function.gfx_fill_rectangle(35,480,5,20); //2


    gfx_function.gfx_fill_rectangle(10,600,30,5); //2
    gfx_function.gfx_fill_rectangle(10,620,30,5); //2
    gfx_function.gfx_fill_rectangle(10,640,30,5); //2
    gfx_function.gfx_fill_rectangle(10,600,5,20); //2
    gfx_function.gfx_fill_rectangle(35,620,5,20); //2
    
    gfx_function.gfx_fill_rectangle(10,720,30,5); //2
    gfx_function.gfx_fill_rectangle(10,740,30,5); //2
    gfx_function.gfx_fill_rectangle(10,760,30,5); //2
    gfx_function.gfx_fill_rectangle(10,720,5,20); //2
    gfx_function.gfx_fill_rectangle(10,740,5,20); //2
    gfx_function.gfx_fill_rectangle(35,740,5,20); //2

    gfx_function.gfx_fill_rectangle(10,840,30,5); //2
    gfx_function.gfx_fill_rectangle(35,840,5,20); //2
    gfx_function.gfx_fill_rectangle(35,860,5,20); //2
    

}

void Grafica::Numeros10x10(){
    gfx_function.gfx_color(3);
    gfx_function.gfx_fill_rectangle(25,75,5,30); //1

    gfx_function.gfx_fill_rectangle(10,160,30,5); //2
    gfx_function.gfx_fill_rectangle(10,180,30,5); //2
    gfx_function.gfx_fill_rectangle(10,200,30,5); //2
    gfx_function.gfx_fill_rectangle(35,160,5,20); //2
    gfx_function.gfx_fill_rectangle(10,180,5,20); //2
    
    gfx_function.gfx_fill_rectangle(10,245,30,5); //2
    gfx_function.gfx_fill_rectangle(10,265,30,5); //2
    gfx_function.gfx_fill_rectangle(10,285,30,5); //2
    gfx_function.gfx_fill_rectangle(35,245,5,20); //2
    gfx_function.gfx_fill_rectangle(35,265,5,20); //2

    gfx_function.gfx_fill_rectangle(10,370,30,5); //2
    gfx_function.gfx_fill_rectangle(10,350,5,20); //2
    gfx_function.gfx_fill_rectangle(35,350,5,20); //2
    gfx_function.gfx_fill_rectangle(35,370,5,20); //2

    gfx_function.gfx_fill_rectangle(10,440,30,5); //2
    gfx_function.gfx_fill_rectangle(10,460,30,5); //2
    gfx_function.gfx_fill_rectangle(10,480,30,5); //2
    gfx_function.gfx_fill_rectangle(10,440,5,20); //2
    gfx_function.gfx_fill_rectangle(35,460,5,20); //2
    
    gfx_function.gfx_fill_rectangle(10,520,30,5); //2
    gfx_function.gfx_fill_rectangle(10,540,30,5); //2
    gfx_function.gfx_fill_rectangle(10,560,30,5); //2
    gfx_function.gfx_fill_rectangle(10,520,5,20); //2
    gfx_function.gfx_fill_rectangle(10,540,5,20); //2
    gfx_function.gfx_fill_rectangle(35,540,5,20); //2

    gfx_function.gfx_fill_rectangle(10,620,30,5); //2
    gfx_function.gfx_fill_rectangle(35,620,5,20); //2
    gfx_function.gfx_fill_rectangle(35,640,5,20); //2

    gfx_function.gfx_fill_rectangle(10,700,30,5); //2
    gfx_function.gfx_fill_rectangle(10,720,30,5); //2
    gfx_function.gfx_fill_rectangle(10,740,30,5); //2
    gfx_function.gfx_fill_rectangle(35,700,5,20); //2
    gfx_function.gfx_fill_rectangle(35,720,5,20); //2
    gfx_function.gfx_fill_rectangle(10,700,5,20); //2
    gfx_function.gfx_fill_rectangle(10,720,5,20); //2
    
    gfx_function.gfx_fill_rectangle(10,800,30,5); //2
    gfx_function.gfx_fill_rectangle(10,820,30,5); //2
    gfx_function.gfx_fill_rectangle(10,840,30,5); //2
    gfx_function.gfx_fill_rectangle(35,800,5,20); //2
    gfx_function.gfx_fill_rectangle(35,820,5,20); //2
    gfx_function.gfx_fill_rectangle(10,800,5,20); //2
    
    gfx_function.gfx_fill_rectangle(20,880,20,3); //2
    gfx_function.gfx_fill_rectangle(20,930,20,3); //2
    gfx_function.gfx_fill_rectangle(40,880,3,52); //2    
    gfx_function.gfx_fill_rectangle(20,880,3,50); //2
    gfx_function.gfx_fill_rectangle(10,880,3,50); //1

}

void Grafica::barco_Bomba(int x, int y){
    
    for(int i = 0; i < 9; i++){
        if(coordenadas[i][0] == x && coordenadas[i][1] == y && coordenadas[i][2] == 1){
            if(level == 1){
                
                    gfx_function.gfx_color(4);
                    Posicionamiento5x5(coordenadas[i][0], coordenadas[i][1], casilla_1, margen_1);
                    gfx_function.gfx_line(coordenadas[i][0], coordenadas[i][1] - (casilla_1/2),coordenadas[i][0], coordenadas[i][1] + (casilla_1/2));
                    coordenadas[i][2] = 0;
                    for(int j = 0; j < 9; j++){
                        if(coordenadas[j][0] == i){
                            coordenadas[j][2] = 0;
                            Posicionamiento5x5(coordenadas[j][0], coordenadas[j][1], casilla_1, margen_1);
                            gfx_function.gfx_line(coordenadas[j][0], coordenadas[j][1] - (casilla_1/2),coordenadas[j][0], coordenadas[j][1] + (casilla_1/2));
                        }
                    }
                
            }else if(level == 2){
                
                    gfx_function.gfx_color(4);
                    Posicionamiento5x5(coordenadas[i][0], coordenadas[i][1], casilla_2, margen_1);
                    gfx_function.gfx_line(coordenadas[i][0], coordenadas[i][1] - (casilla_2/2),coordenadas[i][0], coordenadas[i][1] + (casilla_2/2));
                    coordenadas[i][2] = 0;
                    for(int j = 0; j < 9; j++){
                        if(coordenadas[j][0] == i){
                            coordenadas[j][2] = 0;
                            Posicionamiento5x5(coordenadas[j][0], coordenadas[j][1], casilla_1, margen_1);
                            gfx_function.gfx_line(coordenadas[j][0], coordenadas[j][1] - (casilla_1/2),coordenadas[j][0], coordenadas[j][1] + (casilla_1/2));
                        }
                    }
                
            }else{
                
                    gfx_function.gfx_color(4);
                    Posicionamiento5x5(coordenadas[i][0], coordenadas[i][1], casilla_3, margen_1);
                    gfx_function.gfx_line(coordenadas[i][0], coordenadas[i][1] - (casilla_3/2),coordenadas[i][0], coordenadas[i][1] + (casilla_3/2));
                    coordenadas[i][2] = 0;
                    for(int j = 0; j < 9; j++){
                        if(coordenadas[j][0] == i){
                            coordenadas[j][2] = 0;
                            Posicionamiento5x5(coordenadas[j][0], coordenadas[j][1], casilla_1, margen_1);
                            gfx_function.gfx_line(coordenadas[j][0], coordenadas[j][1] - (casilla_1/2),coordenadas[j][0], coordenadas[j][1] + (casilla_1/2));
                        }
                    }
                
            }
             
        }else if(coordenadas[i][0] == x && coordenadas[i][1] == y && coordenadas[i][2] == 0){
            cout << "Ese barco ya está bombardeado" << endl;
        }
    }
}

int Grafica::inicializaGrafica(int level){
    
    int i;
    int pos_x;
    bool flag = 0;
    Grafica reloj;

    //LETRAS
    
    
    gfx_function.gfx_open(ANCHURA, ALTURA, "Tablero Jueguito :)");
        
    while(1){
        //Dibuja el tablero
        if(flag == 0){
            if(level == 1){
            gfx_function.gfx_color(1);
            reloj.tablero5x5();
            reloj.Numeros5x5();
            for(int i = 0 ; i < 5 ; i++){
                reloj.Posicionamiento5x5(barcos[i][0],barcos[i][1],casilla_1,margen_1);
                if(i == 0 || i == 1){
                    reloj.Barcos_pequenos5();
                }else if(i == 2 || i == 3){
                    reloj.Barcos_medianos5();
                }else{
                    reloj.Barcos_grandes5();
                }
            }
              
            gfx_function.gfx_flush();
            usleep(18000);
       }else if(level == 2) {
           gfx_function.gfx_color(2);
            reloj.tablero7x7();
            reloj.Numeros7x7();
            for(int i = 0 ; i < 5 ; i++){
                reloj.Posicionamiento5x5(barcos[i][0],barcos[i][1],casilla_2,margen_1);
                if(i == 0 || i == 1){
                    reloj.Barcos_pequenos();
                }else if(i == 2 || i == 3){
                    reloj.Barcos_medianos();
                }else{
                    reloj.Barcos_grandes();
                }
            }
              
            gfx_function.gfx_flush();
            usleep(18000);

       }else if(level == 3){
            gfx_function.gfx_color(3);
            reloj.tablero10x10();
            reloj.Numeros10x10();
            for(int i = 0 ; i < 5 ; i++){
                reloj.Posicionamiento5x5(barcos[i][0],barcos[i][1],casilla_3,margen_1);
                if(i == 0 || i == 1){
                    reloj.Barcos_pequenosG();
                }else if(i == 2 || i == 3){
                    reloj.Barcos_medianosG();
                }else{
                    reloj.Barcos_grandesG();
                }
            }

            gfx_function.gfx_flush();
            usleep(18000);
        }else{
           cout << "No hay ese nivel, tonto" << endl;
        }
        flag = 1;

        }
              
        
    }     
}


void Grafica::gfx_clear(){
        XClearWindow(gfx_display,gfx_window);
    }
}