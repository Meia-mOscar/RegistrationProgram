#ifndef PERSON_H
#define PERSON_H

#include <QString>

class Person{
public:
    Person(QString name, QString affiliation, QString email);
    QString getName();
    QString getAffiliation();
    QString getEmail();
    void setName(QString name);
    void setAffiliation(QString affiliation);
    void setEmail(QString email);
    QString toString();
private:
    QString m_Name;
    QString m_Affiliation;
    QString m_Email;
};

#endif // PERSON_H
