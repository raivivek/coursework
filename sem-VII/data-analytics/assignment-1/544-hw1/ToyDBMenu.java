import java.sql.*;
import java.io.*;
import java.util.*;


public class ToyDBMenu {

    public static void usage() {
	System.out.println("\n *** Please enter one of the following comands *** ");
	System.out.println("> list");
	System.out.println("> list <age>");
	System.out.println("> describe <pid>");
	System.out.println("> inventory <pid>");
	System.out.println("> suppliers <pid>");
	System.out.println("> manufacturer <pid>");
    System.out.println("> quit");
    }

    public static void menu() {

        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        String response = null;

        while ( true ) {

            try {
    
                System.out.print("> ");

	            response = r.readLine(); 
                StringTokenizer st = new StringTokenizer(response);
                String t = st.nextToken();

                // XXX Please remove all the System.out.println below. They are only there
                // to show you what your output should look like.

                if ( t.equals("list") ) {
                    if ( st.hasMoreTokens() ) {
                        int age = Integer.parseInt(st.nextToken());
                        System.out.println("Listing products with min_age below " + age);
                        System.out.println("Sample output format for one product");
                        System.out.println("pid: 0 name: p_0 name min_age: 14");
		            	// XXX Add code to process this request XXX
                    } else {
                        System.out.println("Listing all products");
                        System.out.println("Sample output format for one product");
                        System.out.println("pid: 0 name: p_0 name min_age: 14");
			            // XXX Add code to process this request XXX
                    }
                }

                else if ( t.equals("describe") ) {
                    int pid = Integer.parseInt(st.nextToken());
                    System.out.println("Listing info for product: " + pid);
                    System.out.println("Sample output format for one product");
                    System.out.println("pid: 0 name: p_0 name min_age: 14");
	                // XXX Add code to process this request XXX
                }
                else if ( t.equals("inventory") ) {
                    int pid = Integer.parseInt(st.nextToken());
                    System.out.println("Inventory for product: " + pid);
                    System.out.println("Sample output format for one product");
                    System.out.println("pid: 0 stock: 20");
	                // XXX Add code to process this request XXX
                }

                else if ( t.equals("suppliers") ) {
                    int pid = Integer.parseInt(st.nextToken());
                    System.out.println("Listing suppliers for product: " + pid);
                    System.out.println("Sample output format for one supplier");
                    System.out.println("sid: 0 name: supplier_0");
	                // XXX Add code to process this request XXX
                }

                else if ( t.equals("manufacturer") ) {
                    int pid = Integer.parseInt(st.nextToken());
                    System.out.println("Manufacturer for product: " + pid);
                    System.out.println("Sample output format for one manufacturer");
                    System.out.println("mid: 0 name: manufacturer_0");
	               // XXX Add code to process this request XXX
                }

                else if ( t.equals("quit") ) {
                    System.exit(0);
                }
                else { 
                    usage();
                }
            } catch (Exception e) {
                System.out.println("Error: " + e.getMessage());
                usage();
            }
        }
    }

    public static void main(String[] args) {

	try {
        usage();
        menu();
    }

        } catch (Exception e) {
	    System.out.println("Error: " + e.getMessage());
        }
    }

}

