#ifndef ABSTRACTREGISTRATIONFACTORY_H
#define ABSTRACTREGISTRATIONFACTORY_H

#include "Person.h"
#include "AbstractRegistration.h"

class AbstractRegistrationFactory{
public:
    virtual ~AbstractRegistrationFactory(){};
    virtual AbstractRegistration* createRegistration(Person &person, QString &details) const = 0;
};

#endif // ABSTRACTREGISTRATIONFACTORY_H
