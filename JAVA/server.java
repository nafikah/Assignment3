import java.net.*;
import java.io.*;

public class server
{
	private static Socket socket;
	public static void main(String[] args)
	{
		try
		{
		int port = 8080;
		ServerSocket server = new ServerSocket(port);
		System.out.println("Listening for connection on port " + server.getLocalPort());
	
		while(true)
		{
			socket = server.accept();
			InputStream is = socket.getInputStream();
			InputStreamReader isr = new InputStreamReader(is);
			BufferedReader br = new BufferedReader(isr);
			String message = br.readLine();
			System.out.println("Receive from client to server: " + message);

			String returnMessage;
			try {
				char temp;
				char [] arr = message.toCharArray();
				int len = arr.length;
					for(int j=0; j<(message.length())/2; j++, len--)
					{
					temp = arr[j];
					arr[j] = arr[len-1];
					arr[len-1] = temp;
					}
					returnMessage = String.valueOf(arr) + "\n";
					
			}

			catch (Exception ex)
			{
				returnMessage = "Please enter a proper message\n";
			}

			OutputStream os = socket.getOutputStream();
			OutputStreamWriter osw = new OutputStreamWriter(os);
			BufferedWriter bw = new BufferedWriter(osw);
			bw.write(returnMessage);
			System.out.println(" \nSent to client from server: " + returnMessage);
			bw.flush();
			}
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}
		finally
		{
			try{
			socket.close();
			}
			catch (Exception ex){ }
		}
	
	}

}
