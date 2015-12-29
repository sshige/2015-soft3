// http://sdc.sun.co.jp/java/docs/j2se/1.4/ja/docs/ja/guide/idl/tutorial/GSapp.html
import EchoApp.*;
import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;

public class EchoClient
{
    static Echo echoImpl;
    public static void main(String args[])
    {
	try {
	    // create and initialize the ORB
	    ORB orb = ORB.init(args, null);
	    // get the root naming context
	    org.omg.CORBA.Object objRef =
		orb.resolve_initial_references("NameService");
	    // Use NamingContextExt instead of NamingContext. This is
	    // part of the Interoperable naming Service.
	    NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);
	    // resolve the Object Reference in Naming
	    String name = "EchoApp/Echo";
	    echoImpl = EchoHelper.narrow(ncRef.resolve_str(name));
	    System.out.println("Obtained a handle on server object: " + echoImpl);
	    echoImpl.echoString("hello world this is test");
	} catch (Exception e) {
	    System.out.println("ERROR : " + e);
	    e.printStackTrace(System.out);
	}
    }
}
