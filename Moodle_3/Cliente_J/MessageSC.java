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
    private  int offset;   
    private final int BUF_SIZE = 1000;

    public MessageSC(int count, int result, int offset, byte[] data){
        this.count = count;
        this.result =  result;
        this.data = data;   
        this.offset = offset;     
    }

    public static MessageSC getClassFromBytes(byte[] buf) {
        ByteBuffer bb = ByteBuffer.wrap(buf);
        bb.order(ByteOrder.LITTLE_ENDIAN);
        int count = bb.getInt();
        int result = bb.getInt();
        int offset = bb.getInt();
        StringBuilder sb = new StringBuilder();
        byte nameByte;
        while ( (nameByte = bb.get()) != '\0' )
            sb.append((char) nameByte);
        
        MessageSC mensaje = new MessageSC(count, result, offset, String.valueOf(sb).getBytes());

        return mensaje;
    }
    
    public byte[] getByteRepr() {
        ByteBuffer bb = ByteBuffer.allocate(4 * 4 + BUF_SIZE);
        bb.order(ByteOrder.LITTLE_ENDIAN);
        bb.putInt(this.count);
        bb.putInt(this.result); 
        bb.putInt(this.offset);                               
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

    public int getOffset() { 
        return offset; 
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

    public void setOffset(int ofset) { 
        offset = ofset;
    }

}
