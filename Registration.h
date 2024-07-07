#ifndef REGISTRATION_H
#define REGISTRATION_H
#include <QDate>
#include "Person.h"

class Registration{
public:
    Registration(Person person);
    Person getAttendee();
    QDate getBookingDate();
    virtual double calculateFee();
    virtual QString toString();
    virtual QString getType();
private:
    double STANDARD_FEE;
    Person m_Attendee;
    QDate m_BookingDate;
};

#endif // REGISTRATION_H
