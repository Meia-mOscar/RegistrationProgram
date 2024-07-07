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
    actionGroupRegistrationTypeDropDown.addItems((QStringList() << "All" << "Registration" << "Student Registration" << "Guest Registration"));
    calculateLayout.addWidget(&actionGroupRegistrationTypeDropDown);
    calculateButton.setText("Calculate Total Fees");
    calculateLayout.addWidget(&calculateButton);
    calculateLayout.addWidget(&calculateResult);
    //Count number of attendees by institution
    outputLayout.addLayout(&countLayout);
    countLabel.setText("Institution Name");
    countLayout.addWidget(&countLabel);
    countLayout.addWidget(&affiliationCountLineEdit);
    countButton.setText("Calculate Total Registrations");
    countLayout.addWidget(&countButton);
    countLayout.addWidget(&countResult);

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
    //qDebug() << registrationList.totalRegistrations("allRegistrations");
    bool isRegistered = false;
    for(int i=0; i<registrationList.totalRegistrations("allRegistrations"); i++){
        //Unique user identification check, email
        if(registrationList.at(i)->getAttendee().getEmail() == emailLineEdit.text()){
            isRegistered = true;
            registrationStatus.setText("Existing attendee");
        }
    }

    if(!isRegistered){
        QStandardItem *registrationFee = new QStandardItem;
        Person newPerson(nameLineEdit.text(), affiliationLineEdit.text(), emailLineEdit.text()); //nameLineEdit, affiliationCountLineEdit, emailLineEdit
        //qDebug() << newPerson.toString();
        if(registrationTypeDropDown.currentText() == "Registration"){
            Registration *newRegistration = new Registration(newPerson);
            registrationList.addRegistration(newRegistration);
            registrationStatus.setText("Registered");
            registrationFee->setText(QString::number(newRegistration->calculateFee()));
        }else if(registrationTypeDropDown.currentText() == "Student Registration"){
            StudentRegistration *newStudentRegistration = new StudentRegistration(newPerson, qualificationCategoryLineEdit.text());
            registrationList.addRegistration(newStudentRegistration);
            registrationStatus.setText("Student registered");
            registrationFee->setText(QString::number(newStudentRegistration->calculateFee()));
        }else if(registrationTypeDropDown.currentText() == "Guest Registration"){
            GuestRegistration *newGuestRegistration = new GuestRegistration(newPerson, qualificationCategoryLineEdit.text());
            registrationList.addRegistration(newGuestRegistration);
            registrationStatus.setText("Guest registered");
            registrationFee->setText(QString::number(newGuestRegistration->calculateFee()));
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

        table.setItem(rowCount, 5, registrationFee);

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
    //“Registration”,“StudentRegistration”,“GuestRegistration” or “All”
    //actionGroupRegistrationTypeDropDown.addItems((QStringList()
    //<< "All" << "Registration" << "Student Registration" << "Guest Registration"));
    /*for(int i=0; i<registrationList.totalRegistrations("allRegistrations");i++){
        qDebug() << registrationList.at(i)->getType();
    }*/
    int sum=0;
    if(actionGroupRegistrationTypeDropDown.currentText() == "All"){
        for(int i=0; i<registrationList.totalRegistrations("allRegistrations"); i++){
            sum += registrationList.at(i)->calculateFee();
        }
    }
    else{
        for(int i=0; i<registrationList.totalRegistrations("allRegistrations"); i++){
            if(registrationList.at(i)->getType() == actionGroupRegistrationTypeDropDown.currentText()){
                sum += registrationList.at(i)->calculateFee();
            }
        }
    }

    calculateResult.setText(QString::number(sum));
}

void MainWindow::countClicked(){
    //A RegistrationList can also return the number of attendees that
    //are registered for the conference from an institution.
    int count=0;
    for(int i=0; i<registrationList.totalRegistrations("allRegistrations"); i++){
        //compare with affiliation
        //qDebug() << registrationList.at(i)->getAttendee().getAffiliation();
        if(registrationList.at(i)->getAttendee().getAffiliation() == affiliationCountLineEdit.text()){
            count++;
        }
    }
    countResult.setText(QString::number(count));
}
