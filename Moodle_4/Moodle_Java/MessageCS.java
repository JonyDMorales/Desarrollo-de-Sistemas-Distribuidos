/*
MessageCS.java
Se crea la clase para poder formar estructuras o paquetes que seran enviados del cliente al servidor en lenguaje java
*/
import java.nio.ByteBuffer;
import java.nio.ByteOrder;


public class MessageCS {

    private  int opcode;    
    private  int count;
    private  int offset;
    private  String name;

    /* Definiciones necesarias para los clientes y el servidor de archivos */
    private final int BUF_SIZE = 1000;  ////Cantidad de bytes que se transfieren por paquete
    private final int MAX_PATH  = 255;  //Longitud máxima en el nombre de un archivo

    /* Definición de las operaciones permitidas */
    private final int CREATE = 1; //Crea un nuevo archivo
    private final int READ  = 2; //Lee una parte del archivo
    private final int WRITE  = 3; //Escribe una parte del archivo
    private final int DELETE = 4; //Elimina un archivo existente

    /*Códigos de error */
    private final int OK =  0;                //Operación correcta
    private final int E_BAD_OPCODE = -1;     //Operación desconocida
    private final int E_BAD_PARAM = -2;      //Error en un parámetro
    private final int E_IO = -3;             //Error en disco u otro error de E/S
    
    public MessageCS(int opcoud, int caunt, int ofset, String neim){
        opcode = opcoud;
        count = caunt;
        offset = ofset;
        name = neim;
    }
    
    public static MessageCS getClassFromBytes(byte[] buf) {
        ByteBuffer bb = ByteBuffer.wrap(buf);
        bb.order(ByteOrder.LITTLE_ENDIAN);
        int opcoud = bb.getInt();
        int caunt = bb.getInt();
        int ofset = bb.getInt();
        StringBuilder sb = new StringBuilder();
        byte nameByte;
        while ( (nameByte = bb.get()) != '\0' )
            sb.append((char) nameByte);
        
        MessageCS mensaje = new MessageCS(opcoud, caunt, ofset, sb.toString());

        return mensaje;
    }
    
    public byte[] getByteRepr() {
        ByteBuffer bb = ByteBuffer.allocate(3 * 4 + 255);
        bb.order(ByteOrder.LITTLE_ENDIAN);
        bb.putInt(opcode);
        bb.putInt(count);
        bb.putInt(offset);
        for (int i = 0; i < count; i++)
          bb.put((byte) name.charAt(i));
        return bb.array();
    }
    
    public int getOpcode() { 
        return opcode; 
    }

    public int getCount() { 
        return count; 
    }
    
    public int getOffset() { 
        return offset; 
    }

    public String getName() { 
        return name; 
    }
    
    public void setOpcode(int opcoud) { 
        opcode = opcoud;
    }

    public void setCount(int caunt) { 
        count = caunt; 
    }    

    public void setOffset(int ofset) {
        offset = ofset; 
    }

    public void setName(String neim) { 
        name = neim;
    }

}
