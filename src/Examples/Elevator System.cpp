/*
    Elevator - Up, Down, Idle
    Floor can be selected from inside and outside buttons
    Servers all requests in current direction before serving opposite direction 
    Has capacity - max no of persons
    Priority - Up has more priority than down => IDLE ~ UP
    
    Entities;
        Elevator Direction
        Request Type
        Request
        Elevator System  
*/

#include <bits/stdc++.h>

using namespace std;

enum Direction {
    UP,
    DOWN,
    IDLE
};

enum Type {
    INTERNAL,
    EXTERNAL
};


class Request {
public:
    int targetFloor;
    int currentFloor;
    Direction direction;   
    Type type;
    
    Request(int currentFloor, int targetFloor, Direction direction, Type type) : targetFloor(targetFloor), currentFloor(currentFloor), direction(direction), type(type) {
        
    }
};

// use directly this elevator class for only 1 elevetor question. Don't usw elevator system class
class Elevator {
    struct UpComp {
        // reverse sort in PQ as default PR is maxheap -> ''ar to minheap
        static bool operator() (Request* a, Request* b) {
            return a->targetFloor > b->targetFloor;
        }
    };
    
    struct DownComp {
        static bool operator() (Request* a, Request* b) {
            return a->targetFloor < b->targetFloor;
        }
    };
public:
    priority_queue<Request*, vector<Request*>, UpComp>upRequests;
    priority_queue<Request*, vector<Request*>, DownComp>downRequests;
    int maxCapacity;
    Direction currDirection;
    int currFloor;
    
    Elevator(int maxCapacity, int currFloor) : currFloor(currFloor), maxCapacity(maxCapacity), currDirection(IDLE) {
        
    }
    
    void addRequest(Request* request) {
        if(request->direction == Direction::UP) {
            if(request->type == Type::EXTERNAL) {
                upRequests.push(new Request(request->currentFloor, request->currentFloor, request->direction, Type::EXTERNAL));
            }

            upRequests.push(request);
        } else {
            if(request->type == Type::EXTERNAL) {
                downRequests.push(new Request(request->currentFloor, request->currentFloor, request->direction, Type::EXTERNAL));
            }

            downRequests.push(request);
        }
    }
    
    void processUpRequests() {
        while(!upRequests.empty()) {
            auto currReq = upRequests.top();
            upRequests.pop();
            this->currFloor = currReq->targetFloor;
            cout<<"current Floor is "<<this->currFloor<<endl;
        }
        
        if(!downRequests.empty()) {
            this->currDirection = Direction::DOWN;
        } else {
            this->currDirection = Direction::IDLE;
        }
    }
    
    void processDownRequests() {
        while(!downRequests.empty()) {
            auto& currReq = downRequests.top();
            downRequests.pop();
            this->currFloor = currReq->targetFloor;
            cout<<"current Floor is "<<this->currFloor<<endl;
        }
        
        if(!upRequests.empty()) {
            this->currDirection = Direction::UP;
        } else {
            this->currDirection = Direction::IDLE;
        }
    }
    
    void processRequests() {
        if(this->currDirection == Direction::UP or this->currDirection == Direction::IDLE) {
            processUpRequests();
            processDownRequests();
        } else {
            processDownRequests();
            processUpRequests();
        }
    }
    
    void run() {
        processRequests();
    }
};

// use this for multiple elevators question
class ElevatorSystem {
public:
    int floors;
    int elevatorsCount;
    int maxCapacity;
    vector<Elevator*>elevators;
    
    ElevatorSystem(int floors, int maxCapacity, int elevatorsCount) : floors(floors), maxCapacity(maxCapacity), elevatorsCount(elevatorsCount) {
        for(int i=0; i<elevatorsCount; i++) {
            auto currElevator = new Elevator(maxCapacity, 0);
            this->elevators.push_back(currElevator);
        }
    }
    
    void addElevator(Elevator* elevator) {
        this->elevators.push_back(elevator);
    }
    
    void removeElevator(Elevator* elevator) {
        auto it = find(this->elevators.begin(), this->elevators.end(), elevator);
        this->elevators.erase(it);
    }
    
    void addRequest(Request* request) {
        auto optimalElevator = findOptimalElevator(request);
        optimalElevator->addRequest(request);
        optimalElevator->run();
    }
    
    Elevator* findOptimalElevator(Request* request) {
        // custom logic - without internal and external requests - works only for uniform requests
        Elevator *optimalElev;
        int distance = INT_MAX;
        for(auto currElev : this->elevators) {
            if(abs(request->targetFloor - currElev->currFloor) < distance and currElev->maxCapacity) {
                optimalElev = currElev;
                distance = abs(request->targetFloor - currElev->currFloor);
            }
        }
        return optimalElev;
    }
    
    void run() {
        for(auto elev : elevators) {
            elev->run();
        }
    }
};

int main() {
    
    ElevatorSystem* elevatorSystem = new ElevatorSystem(10, 12, 3);
    
    Request* req1 = new Request(3, 5, Direction::UP, Type::EXTERNAL);
    Request* req2 = new Request(2, 10, Direction::UP, Type::EXTERNAL);
    Request* req3 = new Request(4, 7, Direction::UP, Type::EXTERNAL);
    
    elevatorSystem->addRequest(req1);
    elevatorSystem->addRequest(req2);
    elevatorSystem->addRequest(req3);
    
    return 0;
}