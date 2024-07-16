#ifndef REGISTRATIONLIST_H
#define REGISTRATIONLIST_H
#include "Registration.h"
#include "AbstractRegistration.h"

class RegistrationList {
public:
    RegistrationList();
    bool addRegistration(AbstractRegistration *abstractRegistration);
    ~RegistrationList();
    bool isRegistered(QString name);
    double totalFee(QString type);
    int totalRegistrations(QString affiliation);
    int totalRegistrations();
    AbstractRegistration* at(int i);
private:
    //QList<Registration*> m_AttendeeList;
    //Implement: Either funtion overload, or consider changing the QList<type> type == AbstractRegistration
    QList<AbstractRegistration*> m_AttendeeList;
};

#endif // REGISTRATIONLIST_H
