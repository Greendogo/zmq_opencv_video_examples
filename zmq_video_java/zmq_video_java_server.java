import java.util.Base64;
import java.io.UnsupportedEncodingException;
// import org.zeromq.ZContext;
import org.zeromq.ZMQ.Socket;
import org.zeromq.ZMQ;
import org.zeromq.ZMQ.Context;

import java.util.concurrent.TimeUnit;

class Server {
    public static void main(String[] args) {
      // try {
      //   String temp = "hello";
      //   String encoded = Base64.getEncoder().encodeToString(temp.getBytes("utf-8"));
      //   System.out.println(encoded);
      // } catch(UnsupportedEncodingException e) {
      //   System.out.println("Error :" + e.getMessage());
      // }

      Context context = ZMQ.context(1);
      Socket socket = context.socket(ZMQ.PUB);
      socket.bind("tcp://*:5555");
      try
      {
          Thread.sleep(500);
      }
      catch(InterruptedException e)
      {
           // this part is executed when an exception (in this example InterruptedException) occurs
      }
      int i = 0;
      while(i < 100)
      {
        i = i + 1;
        socket.send("-" + i);
      }
    }
}
