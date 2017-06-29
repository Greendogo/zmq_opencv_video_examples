// import java.util.Base64;
// import java.io.UnsupportedEncodingException;
// import org.zeromq.ZContext;
import org.zeromq.ZMQ.Socket;
import org.zeromq.ZMQ;
import org.zeromq.ZMQ.Context;

class Client {
    public static void main(String[] args) {
      // try {
      //   String temp = "hello";
      //   String encoded = Base64.getEncoder().encodeToString(temp.getBytes("utf-8"));
      //   System.out.println(encoded);
      // } catch(UnsupportedEncodingException e) {
      //   System.out.println("Error :" + e.getMessage());
      // }
      ZMQ.Context context = ZMQ.context(1);
      Socket socket = context.socket(ZMQ.SUB);
      socket.connect("tcp://192.168.128.224:20"); //vita's IPv4 address
      socket.subscribe("".getBytes());
      while(true)
      {
        String msg = socket.recvStr();
        System.out.print(msg);
      }
    }
}
