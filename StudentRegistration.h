#ifndef STUDENTREGISTRATION_H
#define STUDENTREGISTRATION_H
#include "Registration.h"

class StudentRegistration : public Registration{
public:
    StudentRegistration(Person person, QString qualification);
    double calculateFee();
    QString toString();
    QString getType();
private:
    QString m_Qualification;
};

#endif //STUDENTREGISTRATION_h
