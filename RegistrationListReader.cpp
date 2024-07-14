#include "RegistrationListReader.h"
#include "StudentRegistration.h"
#include "GuestRegistration.h"

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
            newRegistrationCount++;
            yyyy = rDate.at(i).year();
            mm = rDate.at(i).month();
            dd = rDate.at(i).day();
            Person newPerson(rName.at(i), rAffiliation.at(i), rEmail.at(i));
            if(rType.at(i) == "registration"){
                Registration *newRegistration = regFactory->createRegistration(rType.at(i), newPerson, "");
                //int yyyy, int mm, int dd
                newRegistration->setBookingDate(yyyy, mm, dd);
                regList->addRegistration(newRegistration);
            }else if(rType.at(i) == "studentregistration"){
                /*StudentRegistration *newStudentRegistration = dynamic_cast<StudentRegistration*>(newRegistration);
                newStudentRegistration->setBookingDate(yyyy, mm, dd);
                regList->addRegistration(newStudentRegistration);*/
                regList->addRegistration(regFactory->createRegistration(rType.at(i), newPerson,""));
            }else if(rType.at(i) == "guestregistration"){
                /*GuestRegistration *newGuestRegistration = regFactory->createRegistration(rType.at(i), newPerson, "");
                newGuestRegistration->setBookingDate(yyyy, mm, dd);
                regList->addRegistration(newGuestRegistration);*/
                regList->addRegistration(regFactory->createRegistration(rType.at(i), newPerson, ""));
            }
        }
    }

    return;
}

int RegistrationListReader::returnRegistrationCount(){
    return newRegistrationCount;
}
