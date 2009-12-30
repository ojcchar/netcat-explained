/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package pruebasockets;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.ServerSocket;

/**
 * 
 * @author ojcchar1
 */
public class Server2 {

	public static void main(String[] args) throws IOException,
			InterruptedException {
		ServerSocket sSocket = new ServerSocket();
		sSocket.setReuseAddress(true);
		sSocket.bind(new InetSocketAddress(9899));
		do {
			sSocket.accept();
		} while (true);

	}
}
