#ifndef REGISTRATIONLISTREADER_H
#define REGISTRATIONLISTREADER_H

#include "RegistrationList.h"
#include <QMessageBox>
#include <QXmlInputSource>
#include <QXmlSimpleReader>
#include <QXmlDefaultHandler>


class RegistrationListReader : public QXmlDefaultHandler{
public:
    RegistrationListReader();
    bool startDocument();
    bool startElement(const QString &namespaceURI,
                      const QString &localName,
                      const QString &qName,
                      const QXmlAttributes &atts);
    bool characters(const QString &text);
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);
    void readFromFile(RegistrationList *regList, QString fName);
private:
    QString tbc;
};

#endif // REGISTRATIONLISTREADER_H
