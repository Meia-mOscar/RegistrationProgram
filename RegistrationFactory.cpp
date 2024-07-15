#include "RegistrationFactory.h"
#include "Registration.h"

AbstractRegistration* RegistrationFactory::createRegistration(Person &person, QString &details) const {
    //qDebug() << "Request 'ConcreteRegistrationFactory::createRegistration' create : " << details;
    return new Registration(person);
}

RegistrationFactory* RegistrationFactory::instance(){
    static RegistrationFactory* singleton;
    return singleton;
}
