#ifndef REGISTRATIONLISTREADER_H
#define REGISTRATIONLISTREADER_H

#include "RegistrationList.h"
#include <QMessageBox>
#include <QXmlInputSource>
#include <QXmlSimpleReader>
#include <QXmlDefaultHandler>
#include <QStringList>
#include <QList>
#include <QDate>


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
    bool fatalError(const QXmlParseException &exception);
    void readFromFile(RegistrationList *regList, QString fName);
    void addRegistration(RegistrationList *regList);
    int returnRegistrationCount();
private:
    QString currentTxt;
    QString currentTag;
    QStringList rName;
    QStringList rAffiliation;
    QStringList rEmail;
    QStringList rType;
    QStringList rCategoryOrQualification;
    QList<double> rFee;
    QList<QDate> rDate;
    int rCount;
    int newRegistrationCount;
    bool ok;
};

#endif // REGISTRATIONLISTREADER_H
