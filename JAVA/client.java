import java.net.*;
import java.io.*;

public class client
{
	private static Socket socket;
	public static void main(String args[])
	{
	try 
	{
		String host ="192.168.202.134";
		int port = 8080;
		InetAddress address = InetAddress.getByName(host);
		socket = new Socket(address,port);

		//send the message to the server
		OutputStream os = socket.getOutputStream();
		OutputStreamWriter osw = new OutputStreamWriter(os);
		BufferedWriter bw = new BufferedWriter(osw);

		String message ="Hello guys!";
		String sendMessage = message + "\n";
		bw.write(sendMessage);
		bw.flush();
		System.out.println("From client to server: " +sendMessage);

		//get the return message from server 
		InputStream is = socket.getInputStream();
		InputStreamReader isr = new InputStreamReader(is);
		BufferedReader br = new BufferedReader(isr);
		System.out.println("From server to client: " + message);
	}
	catch (Exception exception)
	{
		exception.printStackTrace();
	}
	finally
	{
		//closing the socket
		try
		{
			socket.close();
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
	}
	}
}
