/*
Servidor.cpp
Es la clase principal del servidor
se ejecuta: ./Game
*/

#include "SocketD/SocketDatagrama.h"
#include "SocketD/Jugador.cpp"
#include "SocketD/header.h"
#include "SocketD/Grafica.h"
#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fstream>
#include <sstream> 
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <list>
using namespace std;

string ips[4];
int k;
int mi_nivel;
int mi_id = 0 ;
bool turno;
int mi_pos;
string mi_ip = "192.168.1.64";
Grafica graph;
Jugador Yo = Jugador((char*)"JonyD",1, 2);;

GtkWidget *entry;
GtkWidget *entry2;

void Crea_Jugador(char* name, int id, int level){
    cout << "Usuario: "<< name << endl;
    cout << "Nivel: " << level << endl;
    mi_nivel = level;
    Yo = Jugador(name, id, level);
}

static void print_hello (GtkWidget *widget, gpointer   data){

  const gchar *text1;
  const gchar *text2;

  text1 = gtk_entry_get_text (GTK_ENTRY (entry));
  text2 = gtk_entry_get_text (GTK_ENTRY (entry2));

  string usuario = string(text1);
  int nivel = atoi(text2);

  Crea_Jugador((char*)usuario.c_str(), mi_id, nivel);
}

static void activate (GtkApplication *app, gpointer user_data){
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button_box;
  
  
  GtkWidget *label;

  GtkWidget *label2;

  GtkWidget *label3;
  GtkWidget *label4;
  GtkWidget *label5;


  GtkWidget *table;
  GtkWidget *table2;


  GtkWidget *image;


  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 300, 200);

  //button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  //gtk_container_add (GTK_CONTAINER (window), button_box);

  button = gtk_button_new_with_label ("Jugar");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);


  table = gtk_table_new (4, 3, TRUE);
  table2 = gtk_table_new (3, 1, TRUE);
  gtk_widget_set_margin_top (table,50);
  gtk_container_add (GTK_CONTAINER (window), table);

  /* create a new label. */
  label = gtk_label_new ("Ingresa un usuario:" );
  gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
  gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 1, 2);

  //create a text box
  entry = gtk_entry_new ();
  gtk_entry_set_max_length (GTK_ENTRY (entry),0);
  gtk_table_attach_defaults (GTK_TABLE (table), entry, 1, 2, 1, 2);



  /* create a new label. */
  label2 = gtk_label_new ("Ingresa el nivel:" );
  gtk_table_set_homogeneous(GTK_TABLE (table), TRUE);
  gtk_table_attach_defaults (GTK_TABLE (table), label2, 0, 1, 2, 3);

  //create a text box
  entry2 = gtk_entry_new ();
  gtk_entry_set_max_length (GTK_ENTRY (entry),0);
  gtk_table_attach_defaults (GTK_TABLE (table), entry2, 1, 2, 2, 3);

  /* create a new label. */
  label3 = gtk_label_new ("*Nivel 1 - Tablero 5x5" );
  gtk_table_set_homogeneous(GTK_TABLE (table2), TRUE);
  gtk_table_attach_defaults (GTK_TABLE (table2), label3, 0, 1, 0, 1);

  label4 = gtk_label_new ("*Nivel 2 - Tablero 7x7" );
  gtk_table_set_homogeneous(GTK_TABLE (table2), TRUE);
  gtk_table_attach_defaults (GTK_TABLE (table2), label4, 0, 1, 1, 2);

  label5 = gtk_label_new ("*Nivel 3 - Tablero 10x10" );
  gtk_table_set_homogeneous(GTK_TABLE (table2), TRUE);
  gtk_table_attach_defaults (GTK_TABLE (table2), label5, 0, 1, 2, 3);


  gtk_table_attach_defaults (GTK_TABLE (table), table2, 0, 1, 3, 4);

  
  gtk_table_attach_defaults (GTK_TABLE (table), button, 2, 3, 3, 4);

  image = gtk_image_new_from_file("rsz4_escom.png");
  gtk_image_set_pixel_size (GTK_IMAGE(image), 200);
  gtk_table_attach_defaults (GTK_TABLE (table), image, 1, 2, 0, 1);

  

  gtk_widget_show_all (window);
}


SocketDatagrama sock  = SocketDatagrama(9000);
SocketDatagrama sock1 = SocketDatagrama(9100);
SocketDatagrama sock2 = SocketDatagrama(9200);
SocketDatagrama sock3 = SocketDatagrama(9300);
SocketDatagrama sock4 = SocketDatagrama(9400);


string siguiente_turno(){
    int pos;
    for (int i = 0; i < k; ++i){
        if(ips[i] == mi_ip){
            pos = i + 1;
        }
       }   
    return ips[pos];
}

int insertar(){
    list <string> aux;
    for (int i = 0; i < k; ++i)
        aux.push_back(ips[i]);
    aux.sort();
    list<string>::iterator it = aux.begin();
    for(int i = 0; it != aux.end(); i++){
      ips[i] = *it++; 
    }
    for(int j = 0; j < k ; j++){
        if(ips[j] == mi_ip){
            return j;
        } 
    }
}

bool Gane(){
    for (int j = 0; j < (k+1); j++){
        if(ips[k] != "0")
            return false;
    }
    return true;
}

void* Tirar(void*){
    struct Tiro_Jugador mi_tiro;
    while(true){
        /*Obtener el tiro de las ventanas y vaciarlo*/
        cout << "A que jugador le quieres tirar" << endl;
        cin >> mi_tiro.id;
        mi_tiro.nivel = Yo.getNivel();
        cout << "Coordenada X" << endl;
        cin >> mi_tiro.x;
        cout << "Coordenada y" << endl;
        cin >> mi_tiro.y;
        mi_tiro.turno = true;
        for (int i = 0; i < k; i++){
            PaqueteDatagrama msj = PaqueteDatagrama((char *)&mi_tiro, sizeof(mi_tiro), ips[i].c_str(), 9200);
            sock2.envia(msj);
        }
    }
}

void empezar(){
    struct Tiro_Jugador jugador;
    jugador.id;
    jugador.nivel = Yo.getNivel();
    jugador.x;
    jugador.y;
    jugador.turno = true;
    PaqueteDatagrama msj = PaqueteDatagrama((char *)&jugador, sizeof(jugador), mi_ip.c_str(), 9200);
    sock2.envia(msj);
}

void* Alguien_Murio(void*){
    while(true){
        PaqueteDatagrama movimiento = PaqueteDatagrama(sizeof(int));
        sock4.recibe(movimiento);
        char* ip = movimiento.obtieneDireccion();
        int* num = (int*)movimiento.obtieneDatos();
        ips[num[0]] = "0";
        if(Gane){
            /*Ventana Ganadora*/
            cout << "Eres el ganador n_n" << endl;
        }else{
            /*Crear ventana diciendo que murio*/ 
            cout << "Murio :(  " << ip << endl;    
        }
    }
}

void* Le_Di(void*){
    while(true){
        PaqueteDatagrama movimiento = PaqueteDatagrama(sizeof(bool));
        sock3.recibe(movimiento);
        char* ip = movimiento.obtieneDireccion();
        /*Crear ventana con le di*/
        cout << "le diste :D a " << ip << endl;
    }
}

void* Recibe_Movimiento(void*){
    struct Tiro_Jugador jugador;
    while(true){
        PaqueteDatagrama movimiento = PaqueteDatagrama(sizeof(jugador));
        sock2.recibe(movimiento);
        memcpy((char *)&jugador, movimiento.obtieneDatos(), sizeof(jugador));
        char* ip = movimiento.obtieneDireccion();
        
        if(jugador.nivel == Yo.getNivel()){
            if(jugador.id == Yo.getId()){
                Coordenada tiro = Coordenada(jugador.x, jugador.y);
                bool pego = Yo.buscaCoordenada(tiro);
                if (pego){
                    graph.barco_Bomba(jugador.x, jugador.y);
                    if(Yo.getMuerte()){
                        int aux = mi_pos;
                        sock4.setBroadcast();
                        PaqueteDatagrama mori = PaqueteDatagrama((char *)&aux, sizeof(aux), "192.168.1.255", 9400);
                        sock4.envia(mori);
                        exit(-1);
                    }else{
                        cout << "Me dio :(" << endl;
                        PaqueteDatagrama dio = PaqueteDatagrama((char *)&pego, sizeof(pego), ip, 9300);
                        sock2.envia(dio);
                    }
                }else{
                    cout << "No me dio :) " << endl;
                }
            }
        }
    }
}

void* Responder_Usuario(void *){
    PaqueteDatagrama peticion = PaqueteDatagrama(2*sizeof(int));
    int* arr;
    char* ip;
    int res[2];
    while(true){
        sock1.recibe(peticion);
        arr = (int *) peticion.obtieneDatos();
        ip = peticion.obtieneDireccion();
        res[0] = arr[0] + arr[1];
        res[1] = mi_nivel;
        PaqueteDatagrama respuesta = PaqueteDatagrama((char *)&res, sizeof(int)*2, ip, 9000);
        sock1.envia(respuesta);
    }
}

void* Registrar_Usuario(void *){
    bool esta;
    k = 0;
    sleep(1);
    while(true){
        sock.setTimeout(60,0);
        esta = true;
        PaqueteDatagrama respuesta = PaqueteDatagrama(sizeof(int)*2);
        int conectados = sock.recibeTimeout(respuesta);
        if(conectados != -1) {
            string ip = respuesta.obtieneDireccion();
            int* resul = (int *)respuesta.obtieneDatos();

            for (int j = 0; j < (k+1); j++){
                if ((ips[j] == ip) || (resul[0] != 5)){
                    esta = false;
                }
            }
            if (esta){
                ips[k] = ip;
                cout << "Se agrego: " << ips[k] << endl;
                k++; 
                mi_pos = insertar();
                //cout << mi_pos << endl;
            }
        }else{
            //cout << "Se agoto tiempo de espera para jugador" << endl;
        }
    }
}

void* Envia_Usuario(void *){
    int arreglo[2] = {2,3};
    while(true){
        sock.setBroadcast();
        PaqueteDatagrama peticion = PaqueteDatagrama((char *)&arreglo, sizeof(arreglo), "192.168.1.255", 9100);
        sock.envia(peticion);
        sleep(5);
    }
}

void* Interfaz(void*){
    sleep(10);
    graph.inicializaGrafica(mi_nivel);
}

int main(int args, char *argv[]) {
    
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), args, argv);
    g_object_unref (app);

    int x = 0, y = 0;
    Coordenada aux = Coordenada(x,y);

    /*Barcos Chicos*/
    cout << "Introduce una coordenada(x) BC:" << endl;
    cin >> x;
    cout << "Introduce una coordenada(y) BC:" << endl;
    cin >> y;
    aux = Coordenada(x,y);
    graph.barcos[0][0] = x;
    graph.barcos[0][1] = y;
    graph.barcos[0][2] = 1;
    Yo.cargaCoordenadas(aux);

    cout << "Introduce una coordenada(x) BC:" << endl;
    cin >> x;
    cout << "Introduce una coordenada(y) BC:" << endl;
    cin >> y;
    aux = Coordenada(x,y);
    graph.barcos[1][0] = x;
    graph.barcos[1][1] = y;
    graph.barcos[1][2] = 1;
    Yo.cargaCoordenadas(aux);

    /*Barcos Medianos*/
    cout << "Introduce una coordenada(x) BM:" << endl;
    cin >> x;
    cout << "Introduce una coordenada(y) BM:" << endl;
    cin >> y;
    aux = Coordenada(x,y);
    graph.barcos[2][0] = x;
    graph.barcos[2][1] = y;
    graph.barcos[2][2] = 1;
    Yo.cargaCoordenadas(aux);

    cout << "Introduce una coordenada(x) BM:" << endl;
    cin >> x;
    cout << " Introduce una coordenada(y) BM:" << endl;
    cin >> y;
    aux = Coordenada(x,y);
    graph.barcos[3][0] = x;
    graph.barcos[3][1] = y;
    graph.barcos[3][2] = 1;
    Yo.cargaCoordenadas(aux);

    /*Barco Grande*/
    cout << "Introduce una coordenada(x) BG:" << endl;
    cin >> x;
    cout << "Introduce una coordenada(y) BG:" << endl;
    cin >> y;
    aux = Coordenada(x,y);
    graph.barcos[4][0] = x;
    graph.barcos[4][1] = y;
    graph.barcos[4][2] = 1;
    Yo.cargaCoordenadas(aux);


    pthread_t th1, th2, th3, th4, th5, th6, th7, th8;

    pthread_create(&th1, NULL, Envia_Usuario, NULL); 
    pthread_create(&th2, NULL, Registrar_Usuario, NULL); 
    pthread_create(&th3, NULL, Responder_Usuario, NULL);
    pthread_create(&th4, NULL, Recibe_Movimiento, NULL);
    pthread_create(&th5, NULL, Le_Di, NULL); 
    pthread_create(&th6, NULL, Alguien_Murio, NULL); 
    pthread_create(&th7, NULL, Interfaz, NULL);
    pthread_create(&th8, NULL, Tirar, NULL);

    empezar();
    pthread_join(th1,NULL);
    pthread_join(th2,NULL);
    pthread_join(th3,NULL);
    pthread_join(th4,NULL);
    pthread_join(th5,NULL);
    pthread_join(th6,NULL);
    pthread_join(th7,NULL);
    pthread_join(th8,NULL);

return status;
}