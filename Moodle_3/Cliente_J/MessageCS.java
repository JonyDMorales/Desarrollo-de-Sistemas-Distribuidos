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
