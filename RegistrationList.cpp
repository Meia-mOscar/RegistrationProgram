#include "RegistrationList.h"

bool RegistrationList::addRegistration(AbstractRegistration *abstractRegistration){
    bool newAttendee = true;
    //Email validation
    for(int i=0; i<m_AttendeeList.size(); i++){
        if(m_AttendeeList.at(i)->getAttendee().getEmail() == abstractRegistration->getAttendee().getEmail()){
            newAttendee = false;
        }
    }

    if(newAttendee){
        m_AttendeeList.append(abstractRegistration);
    }

    return newAttendee;
}

RegistrationList::RegistrationList(){

}

RegistrationList::~RegistrationList(){
    for(int i=0; i<m_AttendeeList.size(); i++){
        delete m_AttendeeList.at(i);
    }
}

bool RegistrationList::isRegistered(QString name){
    bool isRegistered = false;
    for(int i=0; i<m_AttendeeList.size(); i++){
        if(m_AttendeeList.at(i)->getAttendee().getName() == name){
            isRegistered = true;
        }
    }

    return isRegistered;
}

//Accepted types are "Registration", "StudentRegistration", "GuestRegistration"
double RegistrationList::totalFee(QString type){
    double fee = 0;
    for(int i=0; i<m_AttendeeList.size(); i++){
        if(m_AttendeeList.at(i)->toString().contains(type)){
            fee += m_AttendeeList.at(i)->calculateFee();
        }
    }

    return fee;
}

int RegistrationList::totalRegistrations(QString affiliation){
    int count = 0;
    for(int i=0; i<m_AttendeeList.size(); i++){
            if(m_AttendeeList.at(i)->getAttendee().getAffiliation() == affiliation){
                count++;
            }
        }

    return count;
}

int RegistrationList::totalRegistrations(){
    return m_AttendeeList.size();
}

AbstractRegistration* RegistrationList::at(int i){
    return m_AttendeeList.at(i);
}
