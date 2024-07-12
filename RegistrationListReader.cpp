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
        //Current Start Element is "registration"
        rType[rCount] = atts.value("type"); //Is registrationListWriter passing the type value?
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
        rName[rCount] = currentTxt;
    }else if(qName == "affiliation"){
        rAffiliation[rCount] = currentTxt;
    }else if(qName == "email"){
        rEmail[rCount] = currentTxt;
    }else if(qName == "bookingdate"){
        rDate[rCount].fromString(currentTxt,"dd/MM/YYYY");
    }else if(qName == "registrationfee"){
        rFee[rCount] = currentTxt.toDouble(&ok);
    }
    currentTag.clear();
    return true;
}

bool RegistrationListReader::characters(const QString &text){
    currentTxt += text;
    return true;
}

bool RegistrationListReader::fatalError(const QXmlParseException &exception){
    qDebug() << "Parse error at line" << exception.lineNumber() <<", column" << exception.columnNumber() << ":" << exception.message();
    return false;
}

void RegistrationListReader::readFromFile(RegistrationList *regList, QString fName){
    QFile xmlFile(fName);
    QXmlInputSource source(&xmlFile);
    //custom handler
}

void RegistrationListReader::addRegistration(RegistrationList *regList){
    int yyyy;
    int mm;
    int dd;
    bool isRegistered = false;
    //Uniqueness check, email
    for(int i=0; i<rCount; i++){
        for(int n=0; n<rCount; n++){
            if(rEmail[i] == regList->at(n)->getAttendee().getEmail()){
                isRegistered = true;
            }
        }
        if(!isRegistered){
            newRegistrationCount++;
            yyyy = rDate[i].year();
            mm = rDate[i].month();
            dd = rDate[i].day();
            Person newPerson(rName[i], rAffiliation[i], rEmail[i]);
            if(rType[i] == "registration"){
                Registration *newRegistration = new Registration(newPerson);
                //int yyyy, int mm, int dd
                newRegistration->setBookingDate(yyyy, mm, dd);
                regList->addRegistration(newRegistration);
            }else if(rType[i] == "studentregistration"){
                StudentRegistration *newStudentRegistration = new StudentRegistration(newPerson, "");
                newStudentRegistration->setBookingDate(yyyy, mm, dd);
                regList->addRegistration(newStudentRegistration);
            }else if(rType[i] == "guestregistration"){
                GuestRegistration *newGuestRegistration = new GuestRegistration(newPerson, "");
                newGuestRegistration->setBookingDate(yyyy, mm, dd);
                regList->addRegistration(newGuestRegistration);
            }
        }
    }

        return;
}

int RegistrationListReader::returnRegistrationCount(){
    return newRegistrationCount;
}
