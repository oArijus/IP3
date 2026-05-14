#pragma once
#include "Vehicles.h"
#include <vector>
#include <functional>
#include <memory>

// Exception thrown if a calculation is attempted without setting a strategy
class StrategyNotSet : public std::logic_error {
public:
    StrategyNotSet() : std::logic_error("Strategy not set") {
    }
};

// Strategy pattern interface for calculations
class Strategy {
public:
    virtual ~Strategy() = default;
    virtual double execute(const std::vector<Car*>& cars) const = 0;
};
class ValueStrategy : public Strategy {
public:
    double execute(const std::vector<Car*>& cars) const override;
};
class TaxStrategy : public Strategy {
public:
    double execute(const std::vector<Car*>& cars) const override;
};

// Class managing a collection of Vehicles
class Inventory {
private:
    class Impl;
    Impl* pimpl;

public:
    Inventory();
    ~Inventory();
    Inventory(const Inventory& other);
    Inventory& operator=(const Inventory& other);

    // CRUD operations
    void createCar(const Car& car);
    Car* readCar(size_t index) const;
    void updateCar(size_t index, const Car& car);
    void deleteCar(size_t index);

    void setStrategy(Strategy* strategy);
    double executeStrategy() const;

    void checkAllCars() const; 

    // Callback filtering
    std::vector<Car*> filterCars(std::function<bool(const Car&)> callback) const;

    // Forward Iterator
    class Iterator {
    private:
        std::vector<Car*>::iterator it;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Car*;
        using difference_type = std::ptrdiff_t;
        using pointer = Car**;
        using reference = Car*&;

        Iterator(std::vector<Car*>::iterator iter) : it(iter) {
        }
        Iterator& operator++() {
            ++it;
            return *this;
        }
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        bool operator==(const Iterator& other) const {
            return it == other.it;
        }
        bool operator!=(const Iterator& other) const {
            return it != other.it;
        }
        Car* operator*() {
            return *it;
        }
    };

    Iterator begin();
    Iterator end();
};