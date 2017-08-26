public class Servidor{
	public static void main(String[] args) {
		Thread hiloA = new Registrar_Ip();
		//Thread hiloB = new Responder_Peticion();
		//Thread hiloC = new Enviar_Peticion();
		//Thread hiloD = new Envia_Archivos();
		//Thread hiloE = new Solicito_Archivo();
		//Thread hiloF = new Responde_Archivo();
		//Thread hiloG = new Envia_Borrar();

		hiloA.start();
		//hiloB.start();
		//hiloC.start();
		//hiloD.start();
		//hiloE.start();
		//hiloF.start();
		//hiloG.start();
	}
}