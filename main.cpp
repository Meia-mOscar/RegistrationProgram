#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <iostream>
#include <stdexcept>

int main(int argc, char *argv[])
{
    try{
        QApplication a(argc, argv);

        QTranslator translator;
        const QStringList uiLanguages = QLocale::system().uiLanguages();
        for (const QString &locale : uiLanguages) {
            const QString baseName = "RegistrationProgram_" + QLocale(locale).name();
            if (translator.load(":/i18n/" + baseName)) {
                a.installTranslator(&translator);
                break;
            }
        }
        MainWindow w;
        w.show();
        return a.exec();
    } catch (const std::exception &e){
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    return 0;

}
