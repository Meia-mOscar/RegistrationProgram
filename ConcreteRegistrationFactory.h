#ifndef CONCRETEREGISTRATIONFACTORY_H
#define CONCRETEREGISTRATIONFACTORY_H

#include "RegistrationFactory.h"

class ConcreteRegistrationFactory : public QObject, public RegistrationFactory {
    Q_OBJECT
public:
    static ConcreteRegistrationFactory* instance();
    Registration *createRegistration(const QString &type, const Person &person, const QString &details) const override;
protected:
    ConcreteRegistrationFactory();
};

#endif // CONCRETEREGISTRATIONFACTORY_H
