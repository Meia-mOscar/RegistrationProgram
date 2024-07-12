#include "RegistrationListReader.h"
#include "StudentRegistration.h"
#include "GuestRegistration.h"

//Debugging toolset
/*int startDocCount = 0;
int startCount = 0;
int charCount = 0;
int endCount = 0;*/

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
    //startDocCount++;
    //qDebug() << "startDoc: " << startDocCount;
    return true;
}

bool RegistrationListReader::startElement(const QString &namespaceURI,
                  const QString &localName,
                  const QString &qName,
                  const QXmlAttributes &atts){
    //startCount++;
    //qDebug() << "startElement: " << startCount;
    currentTxt.clear();
    if(qName == "registration"){
        //Current Start Element is "registration"
        qDebug() << "Enter: if(qName == 'registration'): " << qName;
        rType.append(atts.value("type")); //Is registrationListWriter passing the type value?
        //qDebug() << "Appended type";
    }else if(qName == "name" || qName == "affiliation" || qName == "email" || qName == "bookingdate" || qName == "registrationfee"){
        currentTag = qName;
        qDebug() << "Enter: else if(qName ==): " << qName;
    }
    return true;
}

bool RegistrationListReader::endElement(const QString &namespaceURI, const QString &localName, const QString &qName){
    //endCount++;
    qDebug() << "endElement: " << qName;
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
        rDate << QDate::fromString(currentTxt,"dd/MM/YYYY");
    }else if(qName == "registrationfee"){
        rFee << currentTxt.toDouble(&ok);
    }
    currentTag.clear();
    return true;
}

bool RegistrationListReader::characters(const QString &text){
    //charCount++;
    qDebug() << "Current char: " << text;
    currentTxt += text;
    return true;
}

bool RegistrationListReader::fatalError(const QXmlParseException &exception){
    qDebug() << "Parse error at line" << exception.lineNumber() <<", column" << exception.columnNumber() << ":" << exception.message();
    return false;
}

void RegistrationListReader::readFromFile(RegistrationList *regList, QString fName){

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
