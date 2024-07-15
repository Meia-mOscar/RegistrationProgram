#ifndef REGISTRATION_H
#define REGISTRATION_H
#include "AbstractRegistration.h"
#include "Person.h"
#include <QDate>

class Registration : public AbstractRegistration {
public:
    ~Registration() override = default;
    Registration(Person person);
    Person getAttendee();
    QDate getBookingDate();
    void setBookingDate(int yyyy, int mm, int dd) override;
    double calculateFee() override;
    QString toString() override;
    QString getType() override;
private:
    double STANDARD_FEE;
    Person m_Attendee;
    QDate m_BookingDate;
};

#endif // REGISTRATION_H
