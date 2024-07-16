#ifndef REGISTRATIONFACTORY_H
#define REGISTRATIONFACTORY_H

#include "AbstractRegistrationFactory.h"

class RegistrationFactory : public AbstractRegistrationFactory {
public:
    AbstractRegistration* createRegistration(Person &person, QString &details) const override;
    RegistrationFactory(const RegistrationFactory&) = delete;
    RegistrationFactory operator=(const RegistrationFactory&) = delete;
    static RegistrationFactory* getInstance();
private:
    static RegistrationFactory* instance;
    RegistrationFactory(){};
};

#endif // REGISTRATIONFACTORY_H
