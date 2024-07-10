#include "RegistrationListReader.h"

void RegistrationListReader::readFromFile(RegistrationList *regList, QString fName){
    QFile xmlFile(fName);
    QXmlInputSource source(&xmlFile);
    //custom handler
}
