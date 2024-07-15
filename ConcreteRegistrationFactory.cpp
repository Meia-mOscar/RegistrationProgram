#include "ConcreteRegistrationFactory.h"
#include "GuestRegistration.h"
#include "StudentRegistration.h"

Registration* ConcreteRegistrationFactory::createRegistration(const QString &type, const Person &person, const QString &details) const {
    qDebug() << "Request 'ConcreteRegistrationFactory::createRegistration' create : " << details;
    if(type=="registration"){
        return new Registration(person);
    } else if(type=="studentregistration"){
        return new StudentRegistration(person, details);
    }else if(type=="guestregistration"){
        return new GuestRegistration(person, details);
    }else{
        return nullptr;
    }
}

ConcreteRegistrationFactory* ConcreteRegistrationFactory::instance(){
    static ConcreteRegistrationFactory* singleton;
    return singleton;
}
