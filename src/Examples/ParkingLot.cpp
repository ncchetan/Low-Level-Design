/*
    The parking lot should have multiple levels, each level with a certain number of parking spots.
    The parking lot should support different types of vehicles, such as cars, motorcycles, and trucks.
    Each parking spot should be able to accommodate a specific type of vehicle.
    The system should assign a parking spot to a vehicle upon entry and release it when the vehicle exits.
    The system should track the availability of parking spots and provide real-time information to customers.
    Calculate Price at for the parking duration
    
    Entities:
        Slot
        Ticket
        Parking Lot
        Parking Lot System
        Price
        Vehicle
*/

#include<bits/stdc++.h>

using namespace std;

enum Size {
    Small,
    Medium,
    Large
};

enum VehicleType {
    Car,
    Bike,
    Truck
};

class Vehicle {
public:
    string license;
    VehicleType type; 
    
    Vehicle(string license, VehicleType type) : license(license), type(type) {
        
    }
    
};

class Slot {
public:
    int id;
    Vehicle* vehicle;
    bool isAvailable;
    
    Slot(int id, bool isAvailable = true) : id(id), isAvailable(isAvailable) {}
    void removeVehicle() {
        vehicle = nullptr;
        isAvailable = true;
    }
    
};

class PriceStrategy {
public:
    virtual double calculatePrice(long durartion) = 0;
};

class FlatPrice : public PriceStrategy {
public:
    double calculatePrice(long duration) override {
        // custom logic
        return 0.0;
    }
};

class Ticket {
public:
    long entryTime;
    long exitTime;
    Vehicle* vehicle;
    Slot* slot;
    PriceStrategy* priceStrategy;
    
    Ticket(Slot* slot, Vehicle* vehicle, PriceStrategy* priceStrategy) : slot(slot), vehicle(vehicle), priceStrategy(priceStrategy) {
        
    }
    
    double getPrice() {
        long duration = exitTime - entryTime;
        return priceStrategy->calculatePrice(duration);
    }
};

class ParkingLevel {
public:
    int id;
    unordered_map<Size, vector<Slot*>>slots;
    
    ParkingLevel(int id) : id(id) {
        
    }
    
    Size getSlotSize(Vehicle* vehicle) {
        switch(vehicle->type) {
            case Car: 
                return Size::Medium;
            case Bike: 
                return Size::Small;    
            case Truck: 
                return Size::Large;    
            default:
                return Size::Medium;
        }
    }
    
    Slot* assignSlot(Vehicle* vehicle) {
        auto size = getSlotSize(vehicle);
        for(auto parkingSlot : slots[size]) {
            if(parkingSlot->isAvailable) {
                parkingSlot->vehicle = vehicle;
                parkingSlot->isAvailable = false;
                return parkingSlot;
            }
        }
        return nullptr;
    }
    
    void removeSlot(Slot* slot) {
        slot->removeVehicle();
    }
    
    void addSlot(Slot* slot, Size size) {
        slots[size].push_back(slot);
    }
    
};

class ParkingLot {
public:
    vector<ParkingLevel*>levels;
    PriceStrategy* priceStrategy;
    
    Ticket* park(Vehicle* vehicle) {
        for(auto level : levels) {
            auto slot = level->assignSlot(vehicle);
            if(slot) {
                cout<<"Vehicle Parked at "<<level->id<<" and slot "<<slot->id<<endl;
                return new Ticket(slot, vehicle, priceStrategy); 
            }
        }
        cout<<"Vehicle cannot be parked"<<endl;
        return nullptr;
    }
    
    double unpark(Ticket* ticket) {
        double price = ticket->getPrice();
        auto slot = ticket->slot;
        slot->removeVehicle();
        return price;
    }
    
    static ParkingLot* getInstance(vector<ParkingLevel*>levels, PriceStrategy* priceStrategy) {
        if(instance == nullptr) {
            instance = new ParkingLot(levels, priceStrategy);
        }
        return instance;
    };
    
    void addLevel(ParkingLevel* level) {
        levels.push_back(level);
    }
    
private:
    static ParkingLot* instance;
    ParkingLot(vector<ParkingLevel*>levels, PriceStrategy* priceStrategy) : levels(levels), priceStrategy(priceStrategy) {
    }
};

// should initialize static variable outside class
ParkingLot* ParkingLot::instance = nullptr;


int main() {
    PriceStrategy* priceStrategy = new FlatPrice();
    
    ParkingLot* lot = ParkingLot::getInstance({}, priceStrategy);
    
    ParkingLevel* l1 = new ParkingLevel(1);
    ParkingLevel* l2 = new ParkingLevel(2);
    
    lot->addLevel(l1);
    lot->addLevel(l2);
    
    Slot* slot1 = new Slot(1);
    Slot* slot2 = new Slot(2);
    
    l1->addSlot(slot1, Size::Medium);
    l2->addSlot(slot2, Size::Large);
    
    Vehicle* v1 = new Vehicle("123", VehicleType::Car);
    Vehicle* v2 = new Vehicle("456", VehicleType::Bike);
    
    Ticket* ticket1 = lot->park(v1);
    Ticket* ticket2 = lot->park(v2);
    
    return 0;
}