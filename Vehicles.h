#pragma once
#include <string>
#include <stdexcept>

// Exception thrown when a method is called that has not been implemented yet
class NotImplementedException : public std::logic_error {
public:
    NotImplementedException() : std::logic_error("Not implemented yet") {
    }
};

// Abstract base class for all vehicles
class Car {
protected:
    std::string make;
    std::string color;
    double price;
public:
    Car(std::string m, std::string c, double p) : make(m), color(c), price(p) {
    }
    virtual ~Car() = default;
    
    // Prototype pattern
    virtual Car* clone() const = 0;
    
    // Polymorphic method
    virtual void checkStatus() const = 0;
    
    std::string getColor() const {
        return color;
    }
    double getPrice() const { 
        return price;
    }
    std::string getMake() const { 
        return make;
    }
};

class FuelCar : public Car {
public:
    FuelCar(std::string m, std::string c, double p);
    Car* clone() const override;
    void checkStatus() const override;
    
    // Child specific method
    void refuelGas() const; 
};

class ElectricCar : public Car {
public:
    ElectricCar(std::string m, std::string c, double p);
    Car* clone() const override;
    void checkStatus() const override;
};

class ConceptCar : public Car {
public:
    ConceptCar(std::string m, std::string c, double p);
    Car* clone() const override;
    void checkStatus() const override; 
};

class HybridCar : public Car {
public:
    HybridCar(std::string m, std::string c, double p);
    Car* clone() const override;
    void checkStatus() const override;
    void chargeAndRefuel() const;
};