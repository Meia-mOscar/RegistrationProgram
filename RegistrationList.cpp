#include "RegistrationList.h"

bool RegistrationList::addRegistration(Registration *registration){
    bool added = true;
    for(int i=0; i<m_AttendeeList.size(); i++){
        if(m_AttendeeList.at(i)->getAttendee().getName() == registration->getAttendee().getName()){
            added = false;
        }
    }

    if(added){
        m_AttendeeList.append(registration);
    }

    return added;
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
    if(affiliation != "allRegistrations"){
        for(int i=0; i<m_AttendeeList.size(); i++){
            if(m_AttendeeList.at(i)->getAttendee().getAffiliation() == affiliation){
                count++;
            }
        }
    }else{
        count = m_AttendeeList.size();
    }

    return count;
}

Registration* RegistrationList::at(int i){
    return m_AttendeeList.at(i);
}
