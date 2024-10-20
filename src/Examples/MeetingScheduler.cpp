/*
// Implement a meeting scheduler application that allows users to schedule and manage meetings. The application should do this:
// * Users can create, update, and delete meetings.
// * Each meeting has a start time, end time, and attendees.
// * The application should prevent users from scheduling overlapping meetings
// * Users can view a calendar of scheduled meetings.
// * The application should be easy to maintain and easy to extend with additional features in the future./


// if one person is not free donot schedule the meeting

    Entities:
        Meeting
        User
        Scheduler
*/

#include <bits/stdc++.h>

using namespace std;

class User;

class Meeting {
public:
    int id;
    int startTime;
    int endTime;
    vector<User*>attendees;
};

class User {
public:
    int id;
    unordered_set<Meeting*>calendar;
    
    User(int id) : id(id) {
        
    }
    
    void addMeeting(Meeting* meet) {
        calendar.insert(meet);
    }
    
    void removeMeeting(Meeting* meet) {
        for(auto mt : calendar) {
            if(mt->id == meet->id) {
                calendar.erase(mt);
                return;
            }
        }
    }
    
    void updateMeeting(Meeting* meet) {
        for(auto mt : calendar) {
            if(mt->id == meet->id) {
                mt = meet;
                return;
            }
        }
    }
    
    bool isOverlapping(Meeting* meet) {
        for(auto mt : calendar) {
            if(meet->startTime <= mt->endTime and meet->endTime >= mt->startTime) {
                return true;
            }
        }
        return false;
    }
};

class MeetingScheduler {
public:
    
    bool create(Meeting* meet) {
        for(auto att : meet->attendees) {
            if(att->isOverlapping(meet)) {
                cout<<"Meeting couldn't schedule"<<endl;
                return false;
            }
        }
        
        for(auto att : meet->attendees) {
            att->addMeeting(meet);
        }
        
        cout<<"Meeting scheduled"<<endl;
        return true; 
    }
    
    void remove(Meeting* meet) {
        for(auto att : meet->attendees) {
            att->removeMeeting(meet);
        }
    }
    
    void update(User* user, Meeting* meet) {
        for(auto att : meet->attendees) {
            att->updateMeeting(meet);
        }
    }
    
    static MeetingScheduler* getInstance() {
        if(instance == nullptr) {
            instance = new MeetingScheduler();
        }
        return instance;
    }

private:
    static MeetingScheduler* instance;
    MeetingScheduler() {
        
    }
    
};

MeetingScheduler* MeetingScheduler::instance = nullptr;

int main() {
    
    User* u1 = new User(1);
    User* u2 = new User(3);
    User* u3 = new User(3);
    
    MeetingScheduler* scheduler = MeetingScheduler::getInstance();
    
    Meeting* m1 = new Meeting(1, 0, 5, {u1, u2});
    Meeting* m2 = new Meeting(2, 1, 7, {u2, u3});
    
    scheduler->create(m1);
    scheduler->create(m2);
    
    return 0;
}