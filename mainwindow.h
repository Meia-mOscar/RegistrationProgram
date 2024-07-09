#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "RegistrationList.h"
#include "GuestRegistration.h"
#include "StudentRegistration.h"
#include "RegistrationListWriter.h"

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QFont>
#include <QFileDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void addClicked();
    void isRegisteredClicked();
    void calculateClicked();
    void countClicked();
    void saveClicked();
    void uploadClicked();
private:
    //GUI management
    void clearInputWidgets();
    RegistrationList registrationList;
    int rowCount;
    //Layout elements
    QWidget centralWidget;
    QVBoxLayout mainLayout;
    QVBoxLayout inputLayout;
    QHBoxLayout nameInputLayout;
    QHBoxLayout emailInputLayout;
    QHBoxLayout affiliationInputLayout;
    QHBoxLayout typeOfRegistrationLayout;
    QHBoxLayout qualificationOrCategoryLayout;
    QHBoxLayout registrationStatusLayout;
    QVBoxLayout outputLayout;
    QHBoxLayout queryLayout;
    QHBoxLayout calculateLayout;
    QHBoxLayout countLayout;
    QTableView tableView;
    QLabel registrationHeading;
    QFont headerFont;
    QLabel outputHeading;
    QLabel tableHeading;
    //Registration fields
    QLabel nameLabel;
    QLineEdit nameLineEdit;
    QLabel emailLabel;
    QLineEdit emailLineEdit;
    QLabel affiliationLabel;
    QLineEdit affiliationLineEdit;
    QLabel registrationTypeLabel;
    QComboBox registrationTypeDropDown; //"Registration/NotApplicable" "StudentRegistration/Qualification" "GuestRegistration/Category"
    QLabel qualificationCategoryLabel; //Registration type / Category?
    QLineEdit qualificationCategoryLineEdit; //Registration or category
    QPushButton addRegistration;
    QLabel registrationStatus;
    //Action groups
    QLabel isNameRegisteredLabel;
    QLineEdit isNameRegisteredLineEdit; //Query by name, QString
    QPushButton isRegisteredButton;
    QLabel isNameRegisteredResult;
    QLabel regestrationTypeQueryLabel;
    QComboBox actionGroupRegistrationTypeDropDown;   //"Registration/NotApplicable" "StudentRegistration/Qualification" "GuestRegistration/Category"
    QPushButton calculateButton;
    QLabel calculateResult;
    QLabel countLabel;
    QLineEdit affiliationCountLineEdit;; //Input the affiliation, QString
    QPushButton countButton;
    QLabel countResult;
    //Table fields
    QStandardItemModel table;
    //Question 2, Save as XML
    QPushButton saveButton;
    RegistrationListWriter *registrationListWriter;
    QFileDialog fileDialogWrite;
    //Question3, Upload XML
    QPushButton uploadButton;
    QFileDialog fileDialogUpload;
};
#endif // MAINWINDOW_H
