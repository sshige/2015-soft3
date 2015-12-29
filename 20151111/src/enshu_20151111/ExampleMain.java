public class ExampleMain {
    public static void main(String[] args) {
        System.loadLibrary("ffi-class_wrap");
        Example e = new Example();
        e.Hello("world");
        e.Sinc(1.0);
    }
}
