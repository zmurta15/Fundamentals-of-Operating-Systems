q/*	Application		A program which continually requests more memory until it is refused
	File			Memory_Hog.Java 
	Purpose			A Memory-intensive program which is used to demonstrate attributes of memory management behaviour
	Author			Richard John Anthony
	Date			January 2015
	
	Function		1. Runs in a loop, incrementally requesting memory, finds allocation limit by doubling request size until a request is refused
                                2. Displays the amount of memory held

        To run the project from the command line, go to the dist folder and type: java -jar "Memory_Hog.jar"
*/

package Memory_Hog;

import java.util.*;

public class Memory_Hog
{
    private static int Million = 1000000;
    public static void main(String[] args)
    {
        int iAllocationIncrement = 1;   // Number of millions of bytes per request
        int iTotalAllocation = 0;       // Total number of millions of bytes allocated and held
        LinkedList<byte[]> MemoryBlockList = new LinkedList<byte[]>(); // Declare a linked list of byte array objects
        Boolean bLimitReached = false;
        
        // Increment allocation size phase
        System.out.printf("Increment memory block allocation size phase:-\n");
        while(false == bLimitReached)
        {
            try
            {   // Allocate memory to a local variable
                byte[] bIncrementalBlockOfMemory = new byte[iAllocationIncrement * Million];
                // Add the local variable into the linked list to retain a reference to it and thus prevent it being garbage-collected
                MemoryBlockList.add(bIncrementalBlockOfMemory);
                iTotalAllocation += iAllocationIncrement;
                iAllocationIncrement *= 2;
            }
            catch (OutOfMemoryError Ex)
            {
                bLimitReached = true;
                System.out.printf("   Memory allocation refused with \"%s\"\n", Ex.toString());
                System.out.printf("   Memory allocation limit reached: %d Million bytes allocated\n", iTotalAllocation);
                System.out.printf("   Largest successful memory allocation unit was: %d Million bytes\n\n", iAllocationIncrement / 2);
                break; // Leave the increment size phase
            }
        }
 
        // Decrement allocation size phase
        // Start with the last size that succeeded, i.e. half the size that was refused
        // Stop when limit is hit a second time, or when the allocation size reaches 1 (Million)
        System.out.printf("Decrement memory block allocation size phase:-\n");
        bLimitReached = false;
        iAllocationIncrement /= 2;
        while(false == bLimitReached && 1 < iAllocationIncrement)
        {
            try
            {   // Allocate memory to a local variable
                byte[] bIncrementalBlockOfMemory = new byte[iAllocationIncrement * Million];
                // Add the local variable into the linked list to retain a reference to it and thus prevent it being garbage-collected
                MemoryBlockList.add(bIncrementalBlockOfMemory);
                iTotalAllocation += iAllocationIncrement;
                iAllocationIncrement /= 2;
            }
            catch (OutOfMemoryError Ex)
            {
                bLimitReached = true;
                System.out.printf("   Memory allocation refused with \"%s\"\n\n", Ex.toString());
                break; // Leave the decrement size phase
            }
        }
        
        System.out.printf("Memory allocation limit reached: %d Million bytes allocated\n", iTotalAllocation);
        // Hold phase, hold the allocated memory until the process is externally killed
        while(true)
        {
        }
    }
}       
        
        
