#ifndef REGISTRATIONLIST_H
#define REGISTRATIONLIST_H
#include "Registration.h"

class RegistrationList {
public:
    RegistrationList();
    bool addRegistration(Registration *registration);
    ~RegistrationList();
    bool isRegistered(QString name);
    double totalFee(QString type);
    int totalRegistrations(QString affiliation);
    int totalRegistrations();
    Registration* at(int i);
private:
    QList<Registration*> m_AttendeeList;
};

#endif // REGISTRATIONLIST_H
