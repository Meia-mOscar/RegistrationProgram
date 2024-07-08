#include "Registration.h"

Registration::Registration(Person person) : m_Attendee(person.getName(), person.getAffiliation(), person.getEmail()){
    STANDARD_FEE=10;
}

Person Registration::getAttendee(){
    return m_Attendee;
}

QDate Registration::getBookingDate(){
    return m_BookingDate;
}

double Registration::calculateFee(){
    return STANDARD_FEE;
}

QString Registration::toString(){
    return QString("Name: %1\n"
                   "Affiliation: %2\n"
                   "Email: %3\n"
                   "Booking date: %4\n"
                   "Standard fee: %5")
        .arg(m_Attendee.getName(),
             m_Attendee.getAffiliation(),
             m_Attendee.getEmail(),
             QString(m_BookingDate.toString()),
             QString::number(STANDARD_FEE));
}

QString Registration::getType(){
    return QString("Registration");
}
