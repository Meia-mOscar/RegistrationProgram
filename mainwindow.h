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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void addClicked();
    void queryClicked();
    void calculateClicked();
    void countClicked();
private:
    //Layout elements
    QWidget centralWidget;
    QVBoxLayout mainLayout;
    QHBoxLayout inputLayout;
    QHBoxLayout outputLayout;
    QTableView tableView;
    //Interactive fields
    QPushButton add;
       QLabel nameLabel;
       QLineEdit name;
       QLabel emailLabel;
       QLineEdit email;
       QLabel affiliationLabel;
       QLineEdit affiliation;
       QLabel registrationTypeLabel;
       QComboBox registrationType; //"Registration/NotApplicable" "StudentRegistration/Qualification" "GuestRegistration/Category"
       QLineEdit qualificationOrCategory; //If(Registration/NotApplicable){/*HIDE*/}
    QPushButton query;
       QLineEdit queryInput; //Query by name, QString
    QPushButton calculateFee;
       QComboBox calculateFeeInput;    //"Registration/NotApplicable" "StudentRegistration/Qualification" "GuestRegistration/Category"
    QPushButton count;
       QLineEdit countInput; //Input the affiliation, QString


};
#endif // MAINWINDOW_H
