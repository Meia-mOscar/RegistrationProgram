#ifndef REGISTRATIONLISTREADER_H
#define REGISTRATIONLISTREADER_H

#include "RegistrationList.h"
#include <QMessageBox>
#include <QDomDocument>
#include <QXmlInputSource>

class RegistrationListReader{
public:
    RegistrationListReader();
    void readFromFile(RegistrationList *regList, QString str);
private:
    QMessageBox criticalError;
    QDomDocument doc;
};

#endif // REGISTRATIONLISTREADER_H
