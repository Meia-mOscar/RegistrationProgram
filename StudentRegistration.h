#include "Registration.h"

class StudentRegistration : public Registration{
public:
    StudentRegistration(Person person, QString qualification);
    double calculdateFee();
    QString toString();
private:
    QString m_Qualification;
};
