/*
Cliente_Palabra.java
Clase principal del cliente, se ejecuta:
java Cliente_Palabra direccion puerto palabra_a_buscar
ejemplo:
java Cliente_Palabra "127.0.0.1" 9000 tres
*/
import java.net.*;
import java.io.*;

public class Cliente_Palabra{
    static final int CREATE = 1; 
    static final int READ = 2;   
    static final int WRITE = 3;  
    static final int DELETE = 4; 

    static final int PUERTO = 7000;
    static final int TAM_PAQUETE = 1000;

    static final int OK = 0; 

	public static void main(String[] args) {
		try{
        	InetAddress host = InetAddress.getByName(args[0]);
        	int pto = Integer.parseInt(args[1]);
        	String palabra = args[2];
        	DatagramSocket c = new DatagramSocket();
            /*Se crea peticion*/
            MessageCS peticion = new MessageCS(READ, palabra.length(), 0, palabra);
            byte[] datos = peticion.getByteRepr();
        	DatagramPacket p = new DatagramPacket(datos, datos.length, host, pto);
        	c.send(p);
        	System.out.println("Se envio a: " + host);
            System.out.println("Opcode: " + peticion.getOpcode());
            System.out.println("Count: " + peticion.getCount());
            System.out.println("Offset: " + peticion.getOffset());
        	System.out.println("Name: " + peticion.getName());
            Thread.sleep(1 * 5);

            /*Se recibe respuesta*/
        	DatagramPacket res = new DatagramPacket(new byte[TAM_PAQUETE], TAM_PAQUETE);
        	c.receive(res);
        	MessageSC respuesta = MessageSC.getClassFromBytes(res.getData());
            int count  = respuesta.getCount();
            int result = respuesta.getResult();
            byte[] r   = respuesta.getData();
            int offset = respuesta.getOffset();
            String veces = new String(r);
            System.out.println("\n\n\nSe recibe:");
            System.out.println("Count: "  + count);
            System.out.println("Result: " + result);
            System.out.println("Offset: " + offset);
            System.out.println("Data: "   + veces);
      	}catch(Exception e){
      		e.printStackTrace();
    	}
	}
}