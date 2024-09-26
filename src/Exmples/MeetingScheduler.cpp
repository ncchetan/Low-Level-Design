#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class User {
public:
    string name;

    User(string name) : name(name) {}

    void notify(string message) {
        cout << name << ": " << message << endl;
    }
}; 

class Meeting {
public:
    int start, end;
    vector<User*> attendees;

    Meeting(int start, int end) : start(start), end(end) {}

    void notifyAttendees(string message) {
        for (auto& attendee : attendees) {
            attendee->notify(message);
        }
    }

    void addAttendees(vector<User*> newAttendees) {
        attendees.insert(attendees.end(), newAttendees.begin(), newAttendees.end());
        notifyAttendees("You have been added to the meeting.");
    }

    void update(int newStart, int newEnd) {
        notifyAttendees("The meeting has been updated.");
        start = newStart;
        end = newEnd;
    }
};

class MeetingScheduler {
private:
    static MeetingScheduler* instance;
    map<int, Meeting*> meetings;
    int meetingID = 0;

    MeetingScheduler() {}

public:
    static MeetingScheduler* getInstance() {
        if (instance == nullptr) {
            instance = new MeetingScheduler();
        }
        return instance;
    }

    bool isNonOverlapping(int start, int end) {
        for (auto& entry : meetings) {
            Meeting* meeting = entry.second;
            if (max(meeting->start, start) < min(meeting->end, end)) {
                return false;
            }
        }
        return true;
    }

    int createMeeting(int start, int end, vector<User*> attendees) {
        if (isNonOverlapping(start, end)) {
            meetingID++;
            Meeting* newMeeting = new Meeting(start, end);
            newMeeting->addAttendees(attendees);
            meetings[meetingID] = newMeeting;
            cout << "Meeting " << meetingID << " scheduled from " << start << " to " << end << endl;
            return meetingID;
        }
        cout << "Failed to schedule meeting." << endl;
        return -1;
    }

    bool addAttendees(int meetingID, vector<User*> newAttendees) {
        if (meetings.find(meetingID) != meetings.end()) {
            meetings[meetingID]->addAttendees(newAttendees);
            return true;
        }
        cout << "Meeting not found." << endl;
        return false;
    }

    bool updateMeeting(int meetingID, int newStart, int newEnd) {
        if (meetings.find(meetingID) != meetings.end()) {
            if (isNonOverlapping(newStart, newEnd)) {
                meetings[meetingID]->update(newStart, newEnd);
                cout << "Meeting " << meetingID << " updated to " << newStart << "-" << newEnd << endl;
                return true;
            } else {
                cout << "Update failed." << endl;
                return false;
            }
        }
        cout << "Meeting not found." << endl;
        return false;
    }

    bool cancelMeeting(int meetingID) {
        if (meetings.find(meetingID) != meetings.end()) {
            meetings[meetingID]->notifyAttendees("Meeting has been canceled.");
            delete meetings[meetingID];
            meetings.erase(meetingID);
            cout << "Meeting " << meetingID << " canceled." << endl;
            return true;
        }
        cout << "Meeting not found." << endl;
        return false;
    }
};

MeetingScheduler* MeetingScheduler::instance = nullptr;

int main() {
    MeetingScheduler* scheduler = MeetingScheduler::getInstance();

    User* personA = new User("PersonA");
    User* personB = new User("PersonB");

    int meeting1 = scheduler->createMeeting(9, 10, {personA});
    int meeting2 = scheduler->createMeeting(11, 12, {personB});

    scheduler->updateMeeting(meeting1, 9, 11);

    scheduler->addAttendees(meeting1, {personB});

    scheduler->cancelMeeting(meeting2);

    return 0;
}
