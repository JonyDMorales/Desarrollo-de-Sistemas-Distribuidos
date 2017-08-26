import java.net.*;

public class Serie_Fourier{

  public static void main(String[] args) {
      try{

        InetAddress host = InetAddress.getByName("127.0.0.1");
        int pto = 9001;
        DatagramSocket c = new DatagramSocket();
        double amplitud = Math.PI / 4;
        double y[] = new double [800];
        int cont = 1;
        int k = 0;

        for (k = 0; k < 800; k++)
            y[k] = 0;
        
        for(int i = 3; true; i+=2, cont +=2){
            for (int j = 1; j < i; j +=2 ) {
                //System.out.println("1/" + j + " * " + "sen(" + j + " * angulo )  + ");
                 k = 0;  
                for (double angulo = -Math.PI; angulo <= Math.PI; angulo += 0.007853982) {
                    y[k] += (1/j) * Math.sin(j * angulo);
                    if (j == cont) {
                        String coordenada = "" + angulo + "," + y[k];
                        byte[] datos = coordenada.getBytes();
                        //DatagramPacket p = new DatagramPacket(datos, datos.length, host, pto);
                        //c.send(p);
                        System.out.println("Coordenada: " + coordenada);
                        y[k] = 0;
                    }
                    k++;    
                }
            }
        }
      }catch(Exception e){
      e.printStackTrace();
    }
  }
}