/*
// * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package pruebasockets;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * 
 * @author ojcchar1
 */
public class Server1 {

	public static void main(String[] args) throws IOException,
			InterruptedException {
		ServerSocket sSocket = new ServerSocket();
		sSocket.setReuseAddress(true);
		sSocket.bind(new InetSocketAddress(9898));
		do {
			sSocket.accept();
		} while (true);

	}
}
