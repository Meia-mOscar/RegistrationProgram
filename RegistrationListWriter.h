#ifndef REGISTRATIONLISTWRITER_H
#define REGISTRATIONLISTWRITER_H

#include <QtXml/QDomDocument>
#include <QFile>
#include <QTextStream>
#include "RegistrationList.h"

class RegistrationListWriter{
public:
    RegistrationListWriter();
    bool writeToFile(RegistrationList &regList, QString &fileName);
};

#endif // REGISTRATIONLISTWRITER_H
