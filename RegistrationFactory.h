#ifndef REGISTRATIONFACTORY_H
#define REGISTRATIONFACTORY_H

#include "AbstractRegistrationFactory.h"

class RegistrationFactory : public AbstractRegistrationFactory {
public:
    static RegistrationFactory* instance();
    AbstractRegistration* createRegistration(Person &person, QString &details) const override;
};

#endif // REGISTRATIONFACTORY_H
