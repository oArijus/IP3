#include "Vehicles.h"
#include <iostream>

FuelCar::FuelCar(std::string m, std::string c, double p) : Car(m, c, p) {
}
Car* FuelCar::clone() const {
    return new FuelCar(*this);
}
void FuelCar::checkStatus() const { 
    std::cout << make << " (Fuel): Checking gas level and engine oil.\n"; 
}
void FuelCar::refuelGas() const { 
    std::cout << make << " is refueling at the gas station.\n"; 
}

ElectricCar::ElectricCar(std::string m, std::string c, double p) : Car(m, c, p) {
}
Car* ElectricCar::clone() const { 
    return new ElectricCar(*this);
}
void ElectricCar::checkStatus() const { 
    std::cout << make << " (Electric): Checking battery degradation and voltage.\n"; 
}

ConceptCar::ConceptCar(std::string m, std::string c, double p) : Car(m, c, p) {
}
Car* ConceptCar::clone() const { 
    return new ConceptCar(*this);
}
void ConceptCar::checkStatus() const { 
    throw NotImplementedException(); 
}