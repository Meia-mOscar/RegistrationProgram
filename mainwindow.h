#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    //void addClicked();
    //void queryClicked();
    //void calculateClicked();
    //void countClicked();
private:
    //Layout elements
    QWidget centralWidget;
    QVBoxLayout mainLayout;
    QVBoxLayout inputLayout;
    QHBoxLayout nameInputLayout;
    QHBoxLayout emailInputLayout;
    QHBoxLayout affiliationInputLayout;
    QHBoxLayout typeOfRegistrationLayout;
    QHBoxLayout registrationOrCategoryLayout;
    //add button
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
    //Action groups
    QLabel isNameRegisteredLabel;
    QLineEdit isNameRegisteredLineEdit; //Query by name, QString
    QPushButton isRegisteredButton;
    QLabel regestrationTypeQueryLabel;
    QComboBox actionGroupRegistrationTypeDropDown;   //"Registration/NotApplicable" "StudentRegistration/Qualification" "GuestRegistration/Category"
    QPushButton calculateButton;
    QLabel countLabel;
    QLineEdit affiliationCountLineEdit;; //Input the affiliation, QString
    QPushButton countButton;
    //Table fields
    QStandardItemModel table;

};
#endif // MAINWINDOW_H
