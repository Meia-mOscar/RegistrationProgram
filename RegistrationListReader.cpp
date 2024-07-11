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
    rCount = 0;
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

    //Oscar, perform email validation!

    for(int i=0; i<rCount; i++){
        yyyy = rDate[rCount].year();
        mm = rDate[rCount].month();
        dd = rDate[rCount].day();
        Person newPerson(rName[rCount], rAffiliation[rCount], rEmail[rCount]);
        if(rType[rCount] == "registration"){
            Registration *newRegistration = new Registration(newPerson);
            //int yyyy, int mm, int dd
            newRegistration->setBookingDate(yyyy, mm, dd);
            regList->addRegistration(newRegistration);
        }else if(rType[rCount] == "studentregistration"){
            StudentRegistration *newStudentRegistration = new StudentRegistration(newPerson, "");
            newStudentRegistration->setBookingDate(yyyy, mm, dd);
            regList->addRegistration(newStudentRegistration);
        }else if(rType[rCount] == "guestregistration"){
            GuestRegistration *newGuestRegistration = new GuestRegistration(newPerson, "");
            newGuestRegistration->setBookingDate(yyyy, mm, dd);
            regList->addRegistration(newGuestRegistration);
        }
    }
}
