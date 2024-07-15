#include "StudentRegistrationFactory.h"
#include "StudentRegistration.h"

AbstractRegistration* StudentRegistrationFactory::createRegistration(Person &person, QString &details) const {
    return new StudentRegistration(person, details);
}
