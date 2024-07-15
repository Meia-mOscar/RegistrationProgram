#ifndef GUESTREGISTRATIONFACTORY_H
#define GUESTREGISTRATIONFACTORY_H

#include "AbstractRegistrationFactory.h"

class GuestRegistrationFactory : public AbstractRegistrationFactory {
public:
    AbstractRegistration* createRegistration(Person &person, QString &details) const override;
};

#endif // GUESTREGISTRATIONFACTORY_H
