#include "RegistrationListWriter.h"

RegistrationListWriter::RegistrationListWriter(){

}

bool RegistrationListWriter::writeToFile(RegistrationList &regList, QString &fileName){
    QDomDocument doc;
    QDomElement root = doc.createElement("RegistrationList");
    doc.appendChild(root);

    for(int i=0; i<regList.totalRegistrations(); i++){
        QDomElement regElement = doc.createElement("registration");
        regElement.setAttribute("type", regList.at(i)->getType());

        QDomElement attendeeElement = doc.createElement("attendee");

        QDomElement nameElement = doc.createElement("name");
        QDomText nameText = doc.createTextNode(regList.at(i)->getAttendee().getName());
        nameElement.appendChild(nameText);
        attendeeElement.appendChild(nameElement);

        QDomElement affiliationElement = doc.createElement("affiliation");
        QDomText affiliationText = doc.createTextNode(regList.at(i)->getAttendee().getAffiliation());
        affiliationElement.appendChild(affiliationText);
        attendeeElement.appendChild(affiliationElement);

        QDomElement emailElement = doc.createElement("email");
        QDomText emailText = doc.createTextNode(regList.at(i)->getAttendee().getEmail());
        emailElement.appendChild(emailText);
        attendeeElement.appendChild(emailElement);

        regElement.appendChild(attendeeElement);

        QDomElement bookingDateElement = doc.createElement("bookingdate");
        QDomText bookingDateText = doc.createTextNode(regList.at(i)->getBookingDate().toString());
        bookingDateElement.appendChild(bookingDateText);
        regElement.appendChild(bookingDateElement);

        QDomElement registrationFeeElement = doc.createElement("registrationfee");
        QDomText registrationFeeText = doc.createTextNode(QString::number(regList.at(i)->calculateFee()));
        registrationFeeElement.appendChild(registrationFeeText);
        regElement.appendChild(registrationFeeElement);

        root.appendChild(regElement);
    }

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)){
        return false;
    }else{
        QTextStream stream(&file);
        stream << doc.toString();
        file.close();
        return true;
    }

}
