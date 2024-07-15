#ifndef ABSTRACTREGISTRATION_H
#define ABSTRACTREGISTRATION_H
#include <QString>

class AbstractRegistration{
public:
    virtual ~AbstractRegistration(){};
    virtual void setBookingDate(int yyyy, int mm, int dd) = 0;
    virtual double calculateFee() = 0;
    virtual QString toString() = 0;
    virtual QString getType() = 0;
};

#endif // ABSTRACTREGISTRATION_H

/*
 * virtual void someFunction() = 0; // Pure virtual function
    virtual ~Registration() = default;*/
