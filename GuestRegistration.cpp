#include "GuestRegistration.h"

GuestRegistration::GuestRegistration(Person person, QString category)
    : Registration(person), m_Category(category){

};

double GuestRegistration::calculateFee(){
    return this->Registration::calculateFee()*0.9;
};

QString GuestRegistration::toString(){
    return QString("Name: %1\n"
                   "Email: %2\n"
                   "Affiliation: %3\n"
                   "Standard fee: %4\n"
                   "Date: %5\n"
                   "Category: %6")
        .arg(this->getAttendee().getName(),
             this->getAttendee().getEmail(),
             this->getAttendee().getAffiliation(),
             QString::number(this->calculateFee()),
             QString(this->getBookingDate().toString()),
             m_Category);
};
