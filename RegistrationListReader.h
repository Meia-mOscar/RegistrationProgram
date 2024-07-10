#ifndef REGISTRATIONLISTREADER_H
#define REGISTRATIONLISTREADER_H

#include "RegistrationList.h"
#include <QMessageBox>
#include <QXmlInputSource>
#include <QXmlSimpleReader>
#include <QXmlDefaultHandler>

#include <QDomDocument> //Get rid of this

class RegistrationListReader{
public:
    RegistrationListReader();
    void readFromFile(RegistrationList *regList, QString str);
private:
    QMessageBox criticalError;
    QDomDocument doc;
};

#endif // REGISTRATIONLISTREADER_H
