#include "RegistrationListReader.h"
#include "StudentRegistration.h"
#include "GuestRegistration.h"

#include <iostream>
#include <stdexcept>

RegistrationListReader::RegistrationListReader(){
    currentTxt.clear();
    currentTag.clear();
    rName.clear();
    rAffiliation.clear();
    rEmail.clear();
    rType.clear();
    rCategoryOrQualification.clear();
    rFee.clear();
    rCount=0;
    newRegistrationCount=0;
    ok = true;
}

bool RegistrationListReader::startDocument(){
    return true;
}

bool RegistrationListReader::startElement(const QString &namespaceURI,
                  const QString &localName,
                  const QString &qName,
                  const QXmlAttributes &atts){
    currentTxt.clear();
    if(qName == "registration"){
        rType.append(atts.value("type"));
    }else if(qName == "name" || qName == "affiliation" || qName == "email" || qName == "bookingdate" || qName == "registrationfee"){
        currentTag = qName;
    }
    return true;
}

bool RegistrationListReader::endElement(const QString &namespaceURI, const QString &localName, const QString &qName){
    if(qName == "registration"){
        //Current End Element is "registration" then increment Lists to next item
        rCount++;
    }else if(qName == "name"){
        rName.append(currentTxt);
    }else if(qName == "affiliation"){
        rAffiliation.append(currentTxt);
    }else if(qName == "email"){
        rEmail.append(currentTxt);
    }else if(qName == "bookingdate"){
        rDate << QDate::fromString(currentTxt,"dd/MM/yyyy");
    }else if(qName == "registrationfee"){
        rFee << currentTxt.toDouble(&ok);
    }
    currentTag.clear();
    return true;
}

bool RegistrationListReader::characters(const QString &text){
    currentTxt += text;
    return true;
}

bool RegistrationListReader::fatalError(const QXmlParseException &exception){
    return false;
}

void RegistrationListReader::readFromFile(RegistrationList *regList, QString fName){

}

void RegistrationListReader::addRegistration(RegistrationList *regList){
    int yyyy;
    int mm;
    int dd;
    //Uniqueness check, email
    int regListSize = regList->totalRegistrations();
    for(int i=0; i<rCount; i++){
        bool isRegistered = false;
        for(int n=0; n<regListSize; n++){
            if(rEmail.at(i) == regList->at(n)->getAttendee().getEmail()){
                isRegistered = true;
            }
        }
        if(!isRegistered){
            newRegistrationCount++;
            yyyy = rDate.at(i).year();
            mm = rDate.at(i).month();
            dd = rDate.at(i).day();
            Person newPerson(rName.at(i), rAffiliation.at(i), rEmail.at(i));
            if(rType.at(i) == "registration"){
                Registration *newRegistration = new Registration(newPerson);
                //int yyyy, int mm, int dd
                newRegistration->setBookingDate(yyyy, mm, dd);
                regList->addRegistration(newRegistration);
            }else if(rType.at(i) == "studentregistration"){
                StudentRegistration *newStudentRegistration = new StudentRegistration(newPerson, "");
                newStudentRegistration->setBookingDate(yyyy, mm, dd);
                regList->addRegistration(newStudentRegistration);
            }else if(rType.at(i) == "guestregistration"){
                GuestRegistration *newGuestRegistration = new GuestRegistration(newPerson, "");
                newGuestRegistration->setBookingDate(yyyy, mm, dd);
                regList->addRegistration(newGuestRegistration);
            }
        }
    }

    return;
}

void RegistrationListReader::addRegistration(RegistrationList *regList, ConcreteRegistrationFactory *regFactory){
    qDebug() << "Enter : RegistrationListReader::addRegistration(regList, regfactory)";
    int yyyy;
    int mm;
    int dd;
    //Uniqueness check, email
    int regListSize = regList->totalRegistrations();
    for(int i=0; i<rCount; i++){
        bool isRegistered = false;
        for(int n=0; n<regListSize; n++){
            if(rEmail.at(i) == regList->at(n)->getAttendee().getEmail()){
                isRegistered = true;
            }
        }

        /* Refactor
         * Pass rType.at(i) & trust the correct object will be created.
         *
         *
         *
         */

        if(!isRegistered){
            qDebug() << "Uniqueness verified: Add registration.";
            newRegistrationCount++;
            yyyy = rDate.at(i).year();
            mm = rDate.at(i).month();
            dd = rDate.at(i).day();
            Person newPerson(rName.at(i), rAffiliation.at(i), rEmail.at(i));
            qDebug() << "Registration type: " << rType.at(i);
            if(rType.at(i) == "registration"){
                qDebug() << "Create Registration obj.";
                Registration *newRegistration = regFactory->createRegistration(rType.at(i), newPerson, "");
                qDebug() << "Registration obj. created";
                //int yyyy, int mm, int dd
                newRegistration->setBookingDate(yyyy, mm, dd);
                regList->addRegistration(newRegistration);
            }else if(rType.at(i) == "studentregistration"){
                qDebug() << "Create StudentRegistration obj.";
                /*StudentRegistration *newStudentRegistration = dynamic_cast<StudentRegistration*>(newRegistration);
                newStudentRegistration->setBookingDate(yyyy, mm, dd);
                regList->addRegistration(newStudentRegistration);*/
                try{
                    regList->addRegistration(regFactory->createRegistration(rType.at(i), newPerson,""));
                    qDebug() << "StudentRegistration obj. created";
                }catch (const std::exception &e) {
                    std::cerr << "Exception caught: " << e.what() << std::endl;
                    qDebug() << e.what();
                }catch (){
                    qDebug() << "Unknown exception caught";
                }
            }else if(rType.at(i) == "guestregistration"){
                qDebug() << "Create GuestRegistration obj.";
                /*GuestRegistration *newGuestRegistration = regFactory->createRegistration(rType.at(i), newPerson, "");
                newGuestRegistration->setBookingDate(yyyy, mm, dd);
                regList->addRegistration(newGuestRegistration);*/
                regList->addRegistration(regFactory->createRegistration(rType.at(i), newPerson, ""));
                qDebug() << "GuestRegistration obj. created";
            }
        }
    }

    return;
}

int RegistrationListReader::returnRegistrationCount(){
    return newRegistrationCount;
}
