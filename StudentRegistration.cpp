#include "StudentRegistration.h"

StudentRegistration::StudentRegistration(Person person,QString qualification)
    : Registration(person), m_Qualification(qualification){

};

double StudentRegistration::calculateFee(){
    return this->Registration::calculateFee()*0.5;
};

QString StudentRegistration::toString(){
    return QString("Name: %1\n"
                   "Affiliation: %2\n"
                   "Email: %3\n"
                   "Standard fee: %4\n"
                   "Date: %5\n"
                   "Qualification: %6")
        .arg(this->getAttendee().getName(),
             this->getAttendee().getAffiliation(),
             this->getAttendee().getEmail(),
             QString::number(this->calculateFee()),
             QString(this->getBookingDate().toString()),
             m_Qualification);
};

QString StudentRegistration::getType(){
    return QString("studentregistration");
}
