// http://sdc.sun.co.jp/java/docs/j2se/1.4/ja/docs/ja/guide/idl/tutorial/GSserver.html
import EchoApp.*;
import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;
import org.omg.PortableServer.*;
import org.omg.PortableServer.POA;
import java.util.Properties;

class EchoImpl extends EchoApp.EchoPOA{
    private ORB orb;
    public void setORB(ORB orb_val){
	orb = orb_val;
    }
    // implement echoString() method
    public void echoString(String input){
	System.err.println(">> " + input);
    }
    // implement shutdown() method
    public void shutdown(){
	orb.shutdown(false);
    }
}

public class EchoServer{
    public static void main(String args[]) {
	try {
	    // create and initialize the ORB
	    ORB orb = ORB.init(args, null);
	    // get reference to rootpoa & activate the POAManager
	    POA rootpoa = POAHelper.narrow(orb.resolve_initial_references("RootPOA"));
	    rootpoa.the_POAManager().activate();
	    // create servant and register it with the ORB
	    EchoImpl echoImpl = new EchoImpl();
	    echoImpl.setORB(orb);
	    // get object reference from the servant
	    org.omg.CORBA.Object ref = rootpoa.servant_to_reference(echoImpl);
	    Echo href = EchoHelper.narrow(ref);
	    // get the root naming context
	    org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
	    // Use NamingContextExt which is part of the Interoperable
	    // Naming Service (INS) specification.
	    NamingContextExt ncRef = NamingContextExtHelper.narrow(objRef);
	    // bind the Object Reference in Naming
	    String name = "EchoApp/Echo";
	    NameComponent path[] = ncRef.to_name( name );
	    ncRef.rebind(path, href);
	    System.out.println("EchoServer ready and waiting ...");
	    // wait for invocations from clients
	    orb.run();
	}
	catch (Exception e) {
	    System.err.println("ERROR: " + e);
	    e.printStackTrace(System.out);
	}
	System.out.println("EchoServer Exiting ...");
    }
}
