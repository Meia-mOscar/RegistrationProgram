#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Configure default values
    rowCount = 0;

    //Configure mainwindow
    headerFont.setBold(true);
    headerFont.setPointSize(12);
    setWindowTitle("Registration");
    centralWidget.setLayout(&mainLayout);
    setCentralWidget(&centralWidget);

    //Registration detail group
    registrationHeading.setText("Registration Details Group");
    registrationHeading.setFont(headerFont);
    mainLayout.addWidget(&registrationHeading);

    //Input layout
    mainLayout.addLayout(&inputLayout);
    inputLayout.addLayout(&nameInputLayout);
    nameLabel.setText("Attendee Name:");
    nameInputLayout.addWidget(&nameLabel);
    nameInputLayout.addWidget(&nameLineEdit);
    inputLayout.addLayout(&emailInputLayout);
    emailLabel.setText("Attendee Email:");
    emailInputLayout.addWidget(&emailLabel);
    emailInputLayout.addWidget(&emailLineEdit);
    inputLayout.addLayout(&affiliationInputLayout);
    affiliationLabel.setText("Affiliation:");
    affiliationInputLayout.addWidget(&affiliationLabel);
    affiliationInputLayout.addWidget(&affiliationLineEdit);
    inputLayout.addLayout(&typeOfRegistrationLayout);
    registrationTypeLabel.setText("Registration Type:");
    typeOfRegistrationLayout.addWidget(&registrationTypeLabel);
    registrationTypeDropDown.addItems(QStringList() << "Registration" << "Student Registration" << "Guest Registration");
    typeOfRegistrationLayout.addWidget(&registrationTypeDropDown);
    inputLayout.addLayout(&qualificationOrCategoryLayout);
    qualificationCategoryLabel.setText("Qualification, if StudentR/Category, if GuestR:");
    qualificationOrCategoryLayout.addWidget(&qualificationCategoryLabel);
    qualificationOrCategoryLayout.addWidget(&qualificationCategoryLineEdit);
    inputLayout.addLayout(&registrationStatusLayout);
    addRegistration.setText("Add Registration");
    registrationStatusLayout.addWidget(&addRegistration);
    registrationStatus.setText("Pending");
    registrationStatusLayout.addWidget(&registrationStatus);

    //Actoin groups
    outputHeading.setFont(headerFont);
    outputHeading.setText("Action Groups");
    mainLayout.addWidget(&outputHeading);
    //Search attendees by name
    mainLayout.addLayout(&outputLayout);
    outputLayout.addLayout(&queryLayout);
    isNameRegisteredLabel.setText("Name:");
    queryLayout.addWidget(&isNameRegisteredLabel);
    queryLayout.addWidget(&isNameRegisteredLineEdit);
    isRegisteredButton.setText("Lookup Attendee");
    queryLayout.addWidget(&isRegisteredButton);
    queryLayout.addWidget(&isNameRegisteredResult);
    //Calculate fees based on Type: Registration, StudentRegistration, GuestRegistration, All.
    outputLayout.addLayout(&calculateLayout);
    regestrationTypeQueryLabel.setText("Registration Type:");
    calculateLayout.addWidget(&regestrationTypeQueryLabel);
    actionGroupRegistrationTypeDropDown.addItems((QStringList() << "All" << "Registration" << " StudentRegistration" << "GuestRegistration"));
    calculateLayout.addWidget(&actionGroupRegistrationTypeDropDown);
    calculateButton.setText("Calculate Total Fees");
    calculateLayout.addWidget(&calculateButton);
    //Count number of attendees by institution
    outputLayout.addLayout(&countLayout);
    countLabel.setText("Institution Name");
    countLayout.addWidget(&countLabel);
    countLayout.addWidget(&affiliationCountLineEdit);
    countButton.setText("Calculate Total Registrations");
    countLayout.addWidget(&countButton);

    //Table layout
    tableHeading.setFont(headerFont);
    tableHeading.setText("Registration List Display");
    mainLayout.addWidget(&tableHeading);
    mainLayout.addWidget(&tableView);
    tableView.setModel(&table);

    //Connect signals and slots
    connect(&addRegistration, &QPushButton::clicked, this, &MainWindow::addClicked);
    connect(&isRegisteredButton, &QPushButton::clicked, this, &MainWindow::isRegisteredClicked);
    connect(&calculateButton, &QPushButton::clicked, this, &MainWindow::calculateClicked);
    connect(&countButton, &QPushButton::clicked, this, &MainWindow::countClicked);
}

MainWindow::~MainWindow() {}

void MainWindow::addClicked(){
    //Create appropriate user and add to registrationList
    qDebug() << registrationList.totalRegistrations("allRegistrations");
    //Oscar, is the add method adding to the Attendee list? Initially yes, but subsequent submissions?
    bool isRegistered = false;
    for(int i=0; i<registrationList.totalRegistrations("allRegistrations"); i++){
        //Unique user identification check, email
        if(registrationList.at(i)->getAttendee().getEmail() == emailLineEdit.text()){
            isRegistered = true;
            registrationStatus.setText("Existing attendee");
        }
    }
    if(!isRegistered){
        Person newPerson(nameLineEdit.text(), affiliationCountLineEdit.text(), emailLineEdit.text()); //nameLineEdit, affiliationCountLineEdit, emailLineEdit
        if(registrationTypeDropDown.currentText() == "Registration"){
            Registration *newRegistration = new Registration(newPerson);
            registrationList.addRegistration(newRegistration);
            registrationStatus.setText("Registered");
        }else if(registrationTypeDropDown.currentText() == "Student Registration"){
            StudentRegistration *newStudentRegistration = new StudentRegistration(newPerson, qualificationCategoryLineEdit.text());
            registrationList.addRegistration(newStudentRegistration);
            registrationStatus.setText("Student registered");
        }else if(registrationTypeDropDown.currentText() == "Guest Registration"){
            GuestRegistration *newGuestRegistration = new GuestRegistration(newPerson, qualificationCategoryLineEdit.text());
            registrationList.addRegistration(newGuestRegistration);
            registrationStatus.setText("Guest registered");
        }else{
            registrationStatus.setText("Registration failed");
        }

        //Add each attribute to the attendee table
        QStandardItem *nameAttribute = new QStandardItem;
        nameAttribute->setText(nameLineEdit.text());
        table.setItem(rowCount,0,nameAttribute);

        QStandardItem *affiliationAttribute = new QStandardItem;
        affiliationAttribute->setText(affiliationLineEdit.text());
        table.setItem(rowCount,1,affiliationAttribute);

        QStandardItem *emailAttribute = new QStandardItem;
        emailAttribute->setText(emailLineEdit.text());
        table.setItem(rowCount,2,emailAttribute);

        QStandardItem *registrationTypeAttribute = new QStandardItem;
        registrationTypeAttribute->setText(registrationTypeDropDown.currentText());
        table.setItem(rowCount,3,registrationTypeAttribute);

        QStandardItem *qualificationOrCategoryAttribute = new QStandardItem;
        qualificationOrCategoryAttribute->setText(qualificationCategoryLineEdit.text());
        table.setItem(rowCount,4,qualificationOrCategoryAttribute);

        rowCount++;
    }

}

void MainWindow::isRegisteredClicked(){
    // Implementation of the slot function
    if(registrationList.isRegistered(isNameRegisteredLineEdit.text())){
        isNameRegisteredResult.setText("Yes");
    }else{
        isNameRegisteredResult.setText("No");
    }
}

void MainWindow::calculateClicked(){
    // Implementation of the slot function
}

void MainWindow::countClicked(){
    // Implementation of the slot function
}
