//
//  main.cpp
//  Very basic SmartPointer Example using std::unique_ptr
//
//  Created by Christopher Gleeson on 1/1/16.
//  Copyright © 2016 Christopher Gleeson. All rights reserved.
//

#include <iostream>
#include <memory>

void cleansUp() {
    std::unique_ptr<int> tempInteger(new int(4096));
    std::cout << "\nAddress of new tempInteger smart pointer is: " << &tempInteger << "\n";
    std::cout << "Address of tempInteger's managed object is: " << tempInteger.get() << "\n";
    std::cout << "Value of tempInteger pointer is: " << *tempInteger << "\n";
    std::cout << "tempInteger is about to be destroyed as this function ends.\n";
    
    //as soon as tempInteger object of type unique_ptr drops out of scope, the
    //object it controls is deallocated automatically.
}

int main(int argc, const char * argv[]) {

    //lets use the std smart pointer and test it
    std::unique_ptr<int> myInteger(new int(1024));
    std::cout << "\nAddress of new myInteger smart pointer is: " << &myInteger << "\n";
    std::cout << "Address of myInteger's managed object is: " << myInteger.get() << "\n";
    std::cout << "Value of myInteger pointer is: " << *myInteger << "\n";
    
    //just an example of how we can still use a basic dereference and assignment
    //like a raw pointer
    *myInteger = 2048;
    std::cout << "\nAddress of myInteger pointer is: " << &myInteger << "\n";
    std::cout << "Address of myInteger's managed object is: " << myInteger.get() << "\n";
    std::cout << "New value of myInteger pointer is: " << *myInteger << "\n";

    //this function will allocate heap memory and that memory is freed when the function
    //returns and scope is lost.
    cleansUp();

    //Another experiment, lets verify that using std::move changes ownership
    std::unique_ptr<int> myTransfer(new int(64));
    std::cout << "\nAddress of new myTransfer pointer is: " << &myTransfer << "\n";
    std::cout << "Address of myTransfer's managed object is: " << myTransfer.get() << "\n";
    std::cout << "Value of myTransfer pointer is: " << *myTransfer << "\n";
    auto tempInteger2 = std::move(myTransfer);
    if(myTransfer) {
        std::cout << "\nmyTransfer still has ownership of its integer! Error!\n";
    }else{
        std::cout << "\nmyTransfer no longer owns its integer.\n";
    }
    if(tempInteger2) {
        std::cout << "\ntempInteger2 now owns the integer\n";
        std::cout << "\nAddress of tempInteger2 pointer is: " << &tempInteger2 << "\n";
        std::cout << "Address of tempInteger2's managed object is: " << tempInteger2.get() << "\n";
        std::cout << "Value of tempInteger2's pointer is: " << *tempInteger2 << "\n";
    }
    
    //Set a breakpoint anywhere below and inspect the memory usage, the only heap allocated memory
    //should be from the object controlled by myInteger which has not dropped out of scope.
    
    //Uncomment the two lines below to introduce a memory leak for testing purposes
    //Create an array of 4096 integers on the heap, never call delete.
    //int *myLeakyInt = new int[4096];
    //std::cout << "Address of myLeakyInt is: " << &myLeakyInt << "\n";
    
    //With a raw pointer, we would have to call delete on its allocated object,
    //but with the smart pointer there is no need, the stack allocated object
    //unique_ptr will delete the heap allocation made by "new int"
    
    //This can be verified by running your favorite memory leak tool such as valgrind
    //or Instruments.  With the intentional leak above (myLeakyInt) commented out, there
    //will be no leak of memory when the program concludes, or from the cleansUp() function
    //above.
    
    return 0;
}
