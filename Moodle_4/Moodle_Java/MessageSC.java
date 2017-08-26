/*
MessageSC.java
Se crea la clase para poder formar estructuras o paquetes que seran enviados del servido al cliente en lenguaje java
*/
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MessageSC {
    
    private int count;   
    private int result;    
    private byte[] data; 
    
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

    public MessageSC(int count, int result, byte[] data){
        this.count = count;
        this.result =  result;
        this.data = data;    
    }

    public static MessageSC getClassFromBytes(byte[] buf) {
        ByteBuffer bb = ByteBuffer.wrap(buf);
        bb.order(ByteOrder.LITTLE_ENDIAN);
        int count = bb.getInt();
        int result = bb.getInt();
        StringBuilder sb = new StringBuilder();
        byte nameByte;
        while ( (nameByte = bb.get()) != '\0' )
            sb.append((char) nameByte);
        
        MessageSC mensaje = new MessageSC(count, result, String.valueOf(sb).getBytes());

        return mensaje;
    }
    
    public byte[] getByteRepr() {
        ByteBuffer bb = ByteBuffer.allocate(4 * 4 + BUF_SIZE);
        bb.order(ByteOrder.LITTLE_ENDIAN);
        bb.putInt(this.count);
        bb.putInt(this.result);                            
        for (int i = 0; i < BUF_SIZE; i++)
          bb.put(this.data[i]);
        return bb.array();
    }
    
    public int getCount() { 
        return count;
    }

    public int getResult() { 
        return result; 
    }

    public byte[] getData() { 
        return data; 
    }

    public void setCount(int caunt) { 
        count = caunt;
    }

    public void setResult(int res) { 
        result = res;
    }

    public void setData(byte[] dat) { 
        data = dat;
    }

}
