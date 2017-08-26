import java.net.*;
//import java.;

public class Serie_Fourier{
  public static void main(String[] args) {
      try{
        InetAddress host = InetAddress.getByName("192.168.0.113");
        int pto = 9001;
        DatagramSocket c = new DatagramSocket();
        double amplitud = Math.PI / 4;
        double y = 0, n = 1;
        int x =0;
        while(true){
          for (double angulo = -Math.PI; angulo <= Math.PI; angulo += 0.007853982) {
            for (double j = 1; j <= n; j += 2 ) {
              y += ((1/j) * Math.sin(j * angulo)) * amplitud * 300;
            }
            String coordenada = "" + x + "," + (int)y;
            System.out.println(coordenada);
            byte[] datos = coordenada.getBytes();
            DatagramPacket p = new DatagramPacket(datos, datos.length, host, pto);
            c.send(p);
            Thread.sleep(1 * 5);
            y = 0;
            x++;
          }
          x = 0;
          n += 2;
        }
      }catch(Exception e){
      e.printStackTrace();
    }
  }
}
