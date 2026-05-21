#include "Vehicles.h"
#include <iostream>

NotImplementedException::NotImplementedException() : std::logic_error("Not implemented yet") {
}

Car::Car(std::string m, std::string c, double p) : make(m), color(c), price(p) {
}
Car::Car(const Car& other) : make(other.make), color(other.color), price(other.price) {
}
Car::~Car() = default;

std::string Car::getColor() const { 
    return color; 
}

double Car::getPrice() const { 
    return price; 
}

std::string Car::getMake() const { 
    return make; 
}

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
