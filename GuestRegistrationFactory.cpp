#include "GuestRegistrationFactory.h"
#include "GuestRegistration.h"

AbstractRegistration* GuestRegistrationFactory::createRegistration(Person &person, QString &details) const {
    return new GuestRegistration(person, details);
}
