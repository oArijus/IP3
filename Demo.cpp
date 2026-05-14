#include "Dealership.h"
#include <iostream>

int main() {
    Inventory dealership;
    FuelCar fc("BMW 320i", "Black", 15000);
    ElectricCar ec("Tesla Model 3", "White", 40000);
    ConceptCar cc("Future X", "Silver", 100000);

    dealership.createCar(fc);
    dealership.createCar(ec);
    
    // polymorphism
    std::cout << "1. Polymorphism & dynamic_cast:\n";
    Car* basePtr = dealership.readCar(0); 
    basePtr->checkStatus();

    FuelCar* fcPtr = dynamic_cast<FuelCar*>(basePtr);
    if (fcPtr) {
        fcPtr->refuelGas();
    }

    // iterator
    std::cout << "\n2. Iterator:\n";
    for (auto it = dealership.begin(); it != dealership.end(); ++it) {
        std::cout << "Found car in inventory: " << (*it)->getMake() << "\n";
    }

    // deep copy
    std::cout << "\n3. Deep Copy:\n";
    Inventory backupDealership = dealership;
    backupDealership.createCar(FuelCar("Audi A4", "Red", 18000));
    std::cout << "Original dealership has " << dealership.filterCars([](const Car&){return true;}).size() << " cars.\n";
    std::cout << "Backup dealership has " << backupDealership.filterCars([](const Car&){return true;}).size() << " cars.\n";

    // strategy
    std::cout << "\n4. Strategy Pattern:\n";
    ValueStrategy valStrat;
    TaxStrategy taxStrat;

    dealership.setStrategy(&valStrat);
    std::cout << "Total Dealership Value: $" << dealership.executeStrategy() << "\n";
    dealership.setStrategy(&taxStrat);
    std::cout << "Total Taxes Expected: $" << dealership.executeStrategy() << "\n";

    // callback
    std::cout << "\n5. Callback Pattern:\n";
    auto isBlack = [](const Car& c) {
        return c.getColor() == "Black"; 
    };
    auto expensiveCars = [](const Car& c) {
        return c.getPrice() > 20000; 
    };
    
    auto blackCars = dealership.filterCars(isBlack);
    std::cout << "Black cars found: " << blackCars.size() << "\n";
    std::cout << "Expensive cars found: " << dealership.filterCars(expensiveCars).size() << "\n";

    return 0;
}