#include "Dealership.h"
#include <iostream>

int main() {
    std::cout << "Testing non implemented class:\n";
    try {
        HybridCar hc("Toyota Prius", "Silver", 25000);
        
        hc.checkStatus(); 
        hc.chargeAndRefuel();
        
    } catch (const NotImplementedException& e) {
        std::cout << "Caught expected exception: " << e.what() << "\n";
    }

    return 0;
}