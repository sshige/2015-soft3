import com.sun.jna.Library;
import com.sun.jna.Native;

public class ExampleMain2 {
    public interface CLibrary extends Library {
        CLibrary INSTANCE = (CLibrary)
            Native.loadLibrary("ffi-c", CLibrary.class);
        void hello(String str);
        double sinc(double x);
    }

    public static void main( String[] args) {
        CLibrary.INSTANCE.hello("world");
        System.out.println("sinc(1.0) = " + CLibrary.INSTANCE.sinc(1.0));
    }
}
