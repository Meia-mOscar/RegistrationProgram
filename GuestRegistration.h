#ifndef GUESTREGISTRATION_H
#define GUESTREGISTRATION_H

#include "Registration.h"

class GuestRegistration : public Registration {
public:
    GuestRegistration(Person person, QString category);
    double calculateFee() override;
    QString toString() override;
    QString getType() override;
private:
    QString m_Category;
};

#endif // GUESTREGISTRATION_H
