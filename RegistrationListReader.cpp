#include "RegistrationListReader.h"

RegistrationListReader::RegistrationListReader(){
    criticalError.setText("Error: Could not open file");
}

void RegistrationListReader::readFromFile(RegistrationList *regList, QString fileName){
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)){
        criticalError.show();
        return;
    }
    if(!doc.setContent(&file)){
        file.close();
        criticalError.show();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    if(root.tagName() != "registrationList"){
        criticalError.show();
        return;
    }

    QDomNodeList regNodeList = root.elementsByTagName("registration");
    for(int i=0; i<regNodeList.size();i++){
        QDomNode regNode = regNodeList.at(i);
        if(regNode.isElement()){
            QDomElement registrationElement = regNode.toElement();
            QString type = registrationElement.attribute("type");

            QDomElement attendeeElement = registrationElement.firstChildElement("attendee");
            QString name = attendeeElement.firstChildElement("name").text();
            QString affiliation = attendeeElement.firstChildElement("affiliation").text();
            QString email = attendeeElement.firstChildElement("email").text();

            QString bookingDate = registrationElement.firstChildElement("bookingDate").text();
            QString registrationFee = registrationElement.firstChildElement("registrationFee").text();

            qDebug() << "Type: " << type;
            qDebug() << "Name: " << name;
            qDebug() << "Affiliation: " << affiliation;
            qDebug() << "Email: " << email;
            qDebug() << "Booking Date: " << bookingDate;
            qDebug() << "Registration Fee: " << registrationFee;
        }
    }

}
