#ifndef STUDENTREGISTRATIONFACTORY_H
#define STUDENTREGISTRATIONFACTORY_H

#include "AbstractRegistrationFactory.h"

class StudentRegistrationFactory : public AbstractRegistrationFactory {
public:
    AbstractRegistration* createRegistration(Person &person, QString &details) const override;
};

#endif // STUDENTREGISTRATIONFACTORY_H
