import java.net.*;

public class Registrar_Ip extends Thread{  
    boolean esta;
    int k;
    public void run(){
     	k = 0;
        int pto = 9000;
        DatagramSocket s = new DatagramSocket(pto);
        while(true){
           esta = true;
           try{
                DatagramPacket p = new DatagramPacket(new byte[4], 4);
                s.receive(p);
                String ip = respuesta.obtieneDireccion();
                int resul = p.getBytes().intValue();
                for (int j = 0; j < (k+1); j++){
                    if ((ips[j] == ip) || (resul[0] != 5)){
                        esta = false;
                    }
                }
                if (esta){
                    ips[k] = ip;
                    cout << "Se agrego: " << ips[k] << endl;
                    k++; 
                }
            }catch(Exception e){
                e.printStackTrace();
            }
        }   
    }
}