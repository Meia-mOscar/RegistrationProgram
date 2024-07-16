#include "Person.h"

Person::Person(QString name, QString affiliation, QString email) : m_Name(name), m_Affiliation(affiliation), m_Email(email){

}

QString Person::getName(){
    return m_Name;
}

QString Person::getAffiliation(){
    return m_Affiliation;
}

QString Person::getEmail(){
    return m_Email;
}

void Person::setName(QString name){
    m_Name = name;
}
void Person::setAffiliation(QString affiliation){
    m_Affiliation = affiliation;
}

void Person::setEmail(QString email){
    m_Email = email;
}

QString Person::toString(){
    return QString("Name: %1\n"
                   "Affiliation: %2\n"
                   "Email: %3")
        .arg(m_Name, m_Affiliation, m_Email);
}
