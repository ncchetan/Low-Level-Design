// multiple channels - sms, email
// custom messages
// multiple messages from different channels to users
// users subscribe and unsubscribe 
/*
Entites:
    Notification Handle Interface
        SMS Handler
        Email handler
    
    Message Interface
        SMS Msg
        Email Msg

    Observers
        Users
    
    Medium/ Channel
 */

#include <bits/stdc++.h>

using namespace std;

enum Channel {
    SMS,
    Email
};

class Message {
public:
    int id = 0;
    string message;
    virtual string getMessage() = 0;
};

class SMSMessage : public Message {
    string phoneNumber;
public:
    SMSMessage(string message, string phoneNumber) : phoneNumber(phoneNumber) {
        this->message = message;
    }

    string getMessage() override {
        return "SMS Message sent to " + this->phoneNumber + " " + this->message;
    }
};

class EmailMessage : public Message {
    string email;
public:
    EmailMessage(string message, string email) : email(email) {
        this->message = message;
    }

    string getMessage() override {
        return "Email Message sent to " + this->email + " " + this->message;
    }
};

class BaseNotificationHandler {
public:
    virtual void sendNotification(Message* message) = 0;

    virtual Channel getChannel() = 0;
};

class SMSHandler : public BaseNotificationHandler {
public:
    void sendNotification(Message* message) override {
        cout<<"SMS "<<message->getMessage()<<" sent"<<endl;
    }

    Channel getChannel() override {
        return Channel::Email;
    }
};

class EmailHandler : public BaseNotificationHandler {
public:
    void sendNotification(Message* message) override {
        cout<<"Email "<<message->getMessage()<<" sent"<<endl;
    }

    Channel getChannel() override {
        return Channel::SMS;
    }
};



class User {
public:
    int id;
    string name;
    string email;
    string phoneNumber;

    User(int id, string name, string email, string phoneNumber) : id(id), name(name), email(email), phoneNumber(phoneNumber) {}
};

class NotificationFactory {
public:
    static BaseNotificationHandler* getNotificationHandler(Channel channel) {
        switch(channel) {
            case SMS:
                return new SMSHandler();
            case Email:
                return new EmailHandler();
        }
    }
};

int main() {
    User* u1 = new User(0, "1", "1@g.com", "1111111111");
    User* u2 = new User(0, "2", "2@g.com", "2222222222");

    Message* sms = new SMSMessage("SMS", u1->phoneNumber);
    Message* mail = new EmailMessage("Email", u2->email);

    BaseNotificationHandler* smsHandler = NotificationFactory::getNotificationHandler(SMS);
    smsHandler->sendNotification(sms);

    BaseNotificationHandler* emailHandler = NotificationFactory::getNotificationHandler(Email);
    emailHandler->sendNotification(mail);

    return 0;
}