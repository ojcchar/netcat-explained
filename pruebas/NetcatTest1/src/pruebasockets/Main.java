/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package pruebasockets;

import java.io.IOException;
import java.net.BindException;
import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketAddress;
import java.net.UnknownHostException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * 
 * @author ojcchar1
 */
public class Main {

	/**
	 * @param args
	 *            the command line arguments
	 */
	public static void main(String[] args) throws InterruptedException {
		try {
			// pruebaDifServidorMismoPuerto();
			pruebaNetcat();
		} catch (UnknownHostException ex) {
			Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
		} catch (IOException ex) {
			Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
		}

	}

	private static void pruebaDifServidorMismoPuerto()
			throws UnknownHostException, IOException, InterruptedException {
		Socket sock1 = null;
		Socket sock2 = null;
		try {
			InetAddress remAdd = InetAddress.getLocalHost();
			sock1 = new Socket();

			SocketAddress addr = new InetSocketAddress(remAdd, 9898);
			if (!sock1.isBound()) {
				sock1.setReuseAddress(true);
			}
			sock1.bind(new InetSocketAddress(8888));
			sock1.connect(addr);
			System.out.println("Conectado 1...");
			System.out.println("puerto local 1: " + sock1.getLocalPort());

			sock2 = new Socket();
			SocketAddress addr2 = new InetSocketAddress(remAdd, 9899);
			if (!sock2.isBound()) {
				sock2.setReuseAddress(true);
			}

			sock2.bind(new InetSocketAddress(8888));
			sock2.connect(addr2);
			System.out.println("Conectado 2...");
			System.out.println("puerto local 2: " + sock2.getLocalPort());

			sock1.close();
			System.out.println("desconectado 1...");
			sock2.close();
			System.out.println("desconectado 2...");
		} catch (BindException e) {
			e.printStackTrace();
			try {
				if (sock1 != null) {
					if (!sock1.isClosed()) {
						sock1.close();

					}
				}
			} catch (IOException iOException) {
			}
			if (sock2 != null) {
				if (!sock2.isClosed()) {
					sock2.close();

				}
			}
		}
	}

	private static void pruebaNetcat() throws UnknownHostException,
			IOException, InterruptedException {
		Socket sock1 = null;
		try {
			InetAddress remAdd = InetAddress.getLocalHost();
			sock1 = new Socket();

			SocketAddress addr = new InetSocketAddress(remAdd, 9898);
			if (!sock1.isBound()) {
				sock1.setReuseAddress(true);
			}
			sock1.bind(new InetSocketAddress(8888));
			sock1.connect(addr);
			System.out.println("Conectado 1...");
			System.out.println("puerto local 1: " + sock1.getLocalPort());

			Thread.sleep(15000);

			sock1.close();
			System.out.println("desconectado 1...");

		} catch (BindException e) {
			e.printStackTrace();
			try {
				if (sock1 != null) {
					if (!sock1.isClosed()) {
						sock1.close();

					}
				}
			} catch (IOException iOException) {
			}
		}
	}
}
