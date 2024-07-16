#include "RegistrationFactory.h"
#include "Registration.h"

RegistrationFactory* RegistrationFactory::instance = NULL;

AbstractRegistration* RegistrationFactory::createRegistration(Person &person, QString &details) const {
    return new Registration(person);
}

RegistrationFactory* RegistrationFactory::getInstance(){
    if(!instance){
        instance = new RegistrationFactory;
    }
    return instance;
}
