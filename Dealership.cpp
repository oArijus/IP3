#include "Dealership.h"
#include <iostream>

double ValueStrategy::execute(const std::vector<Car*>& cars) const {
    double total = 0;
    for(auto c : cars) total += c->getPrice();
    return total;
}

double TaxStrategy::execute(const std::vector<Car*>& cars) const {
    double tax = 0;
    for(auto c : cars) tax += c->getPrice() * 0.21; // 21% tax rate
    return tax;
}

class Inventory::Impl {
public:
    std::vector<Car*> cars;
    Strategy* strategy = nullptr;

    ~Impl() {
        for (auto c : cars) delete c;
    }
    
    Impl* clone() const {
        Impl* copy = new Impl();
        copy->strategy = strategy;

        for (auto c : cars) {
            copy->cars.push_back(c->clone());
        }
        return copy;
    }
};

Inventory::Inventory() : pimpl(new Impl()) {
}

Inventory::~Inventory() {
    delete pimpl;
}

Inventory::Inventory(const Inventory& other) {
    pimpl = other.pimpl->clone();
}

Inventory& Inventory::operator=(const Inventory& other) {
    if (this != &other) {
        delete pimpl;
        pimpl = other.pimpl->clone();
    }
    return *this;
}

void Inventory::createCar(const Car& car) {
    pimpl->cars.push_back(car.clone());
}

Car* Inventory::readCar(size_t index) const {
    if (index < pimpl->cars.size()) return pimpl->cars[index];
    return nullptr;
}

void Inventory::updateCar(size_t index, const Car& car) {
    if (index < pimpl->cars.size()) {
        delete pimpl->cars[index];
        pimpl->cars[index] = car.clone();
    }
}

void Inventory::deleteCar(size_t index) {
    if (index < pimpl->cars.size()) {
        delete pimpl->cars[index];
        pimpl->cars.erase(pimpl->cars.begin() + index);
    }
}

void Inventory::setStrategy(Strategy* strategy) {
    pimpl->strategy = strategy;
}

double Inventory::executeStrategy() const {
    if (!pimpl->strategy) throw StrategyNotSet();
    return pimpl->strategy->execute(pimpl->cars);
}

void Inventory::checkAllCars() const {
    for (auto c : pimpl->cars) {
        c->checkStatus();
    }
}

std::vector<Car*> Inventory::filterCars(std::function<bool(const Car&)> callback) const {
    std::vector<Car*> result;
    for(auto c : pimpl->cars) {
        if(callback(*c)) {
            result.push_back(c);
        }
    }
    return result;
}

Inventory::Iterator Inventory::begin() {
    return Iterator(pimpl->cars.begin());
}
    
Inventory::Iterator Inventory::end() {
    return Iterator(pimpl->cars.end());
}