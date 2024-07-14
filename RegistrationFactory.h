#ifndef REGISTRATIONFACTORY_H
#define REGISTRATIONFACTORY_H

#include "Registration.h"

class RegistrationFactory{
public:
    virtual ~RegistrationFactory(){};
    virtual Registration* createRegistration(const QString &type, const Person &person, const QString &details) const = 0;
};

#endif // REGISTRATIONFACTORY_H
