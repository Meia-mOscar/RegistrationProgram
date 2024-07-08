#include "RegistrationListWriter.h"

RegistrationListWriter::RegistrationListWriter(){

}

bool RegistrationListWriter::writeToFile(RegistrationList &regList, QString &fileName){
    QDomDocument doc;
    QDomElement root = doc.createElement("RegistrationList");
    doc.appendChild(root);

    for(int i=0; i<regList.totalRegistrations("allRegistrations"); i++){
        QDomElement regElement = doc.createElement("Registration");
        regElement.setAttribute("Name", regList.at(i)->getAttendee().getName());
        regElement.setAttribute("Affiliation", regList.at(i)->getAttendee().getAffiliation());
        regElement.setAttribute("Email", regList.at(i)->getAttendee().getEmail());
        regElement.setAttribute("Type", regList.at(i)->getType());
        regElement.setAttribute("Fee", QString::number(regList.at(i)->calculateFee()));
    }

    return true;
}
