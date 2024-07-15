#include "mainwindow.h"
#include "GuestRegistration.h"
#include "StudentRegistration.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), registrationListWriter(new RegistrationListWriter), handler(new RegistrationListReader)
{
    //Configure default values

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
    //Table column headings
    //QFont::bold() at (rowCount == 0)

    //Question 2, Save as XML
    saveButton.setText("Save as XML");
    mainLayout.addWidget(&saveButton);

    //Question 3, Upload XML
    uploadButton.setText("Upload file");
    mainLayout.addWidget(&uploadButton);

    //Connect signals and slots
    connect(&addRegistration, &QPushButton::clicked, this, &MainWindow::addClicked);
    connect(&isRegisteredButton, &QPushButton::clicked, this, &MainWindow::isRegisteredClicked);
    connect(&calculateButton, &QPushButton::clicked, this, &MainWindow::calculateClicked);
    connect(&countButton, &QPushButton::clicked, this, &MainWindow::countClicked);
    connect(&saveButton, &QPushButton::clicked, this, &MainWindow::saveClicked);
    connect(&uploadButton, &QPushButton::clicked, this, &MainWindow::uploadClicked);
}

MainWindow::~MainWindow() {
    delete registrationListWriter;
}

void MainWindow::addClicked(){
    bool isRegistered = false;
    for(int i=0; i<registrationList.totalRegistrations(); i++){
        //Unique user identification check, email
        if(registrationList.at(i)->getAttendee().getEmail() == emailLineEdit.text()){
            isRegistered = true;
            registrationStatus.setText("Existing attendee");
        }
    }

    if(!isRegistered){
        Person newPerson(nameLineEdit.text(), affiliationLineEdit.text(), emailLineEdit.text());
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
        }
        else{
            registrationStatus.setText("Registration failed");
            return;
        }
        MainWindow::updateTable();
    }
}

void MainWindow::isRegisteredClicked(){
    if(registrationList.isRegistered(isNameRegisteredLineEdit.text())){
        isNameRegisteredResult.setText("Yes");
    }else{
        isNameRegisteredResult.setText("No");
    }
}

void MainWindow::calculateClicked(){
    int sum=0;
    if(actionGroupRegistrationTypeDropDown.currentText() == "All"){
        for(int i=0; i<registrationList.totalRegistrations(); i++){
            sum += registrationList.at(i)->calculateFee();
        }
    }
    else{
        for(int i=0; i<registrationList.totalRegistrations(); i++){
            if(registrationList.at(i)->getType() == actionGroupRegistrationTypeDropDown.currentText().toLower().remove(" ")){
                sum += registrationList.at(i)->calculateFee();
            }
        }
    }

    calculateResult.setText(QString::number(sum));
}

void MainWindow::countClicked(){
    int count=0;
    for(int i=0; i<registrationList.totalRegistrations(); i++){
        if(registrationList.at(i)->getAttendee().getAffiliation() == affiliationCountLineEdit.text()){
            count++;
        }
    }
    countResult.setText(QString::number(count));
}

void MainWindow::saveClicked(){
    QString fileName;
    fileName.clear();
    fileName = QFileDialog::getOpenFileName(this,tr("Open file"),"",tr("*.xml"));
    registrationListWriter->writeToFile(registrationList, fileName);
}

void MainWindow::uploadClicked(){
    QString fileName;
    fileName.clear();
    fileName = QFileDialog::getOpenFileName(this,tr("Open file"),"",tr("*.xml"));
    if(!fileName.isEmpty()){
        QFile xmlFile(fileName);
        QXmlInputSource source(&xmlFile);
        QXmlSimpleReader reader;
        reader.setContentHandler(handler);
        reader.parse(source);
    }
    //handler->addRegistration(&registrationList);
    qDebug() << "RegistrationListReader::addRegistration(&regList, regFactory)";
    handler->addRegistration(&registrationList, registrationFactory);
    //Program simply closes, no Abort message
    MainWindow::refreshTable();
}

void MainWindow::refreshTable(){
    table.clear();
    rowCount = 0;
    for (int var = 0; var < registrationList.totalRegistrations(); ++var) {
        QStandardItem *nameAttribute = new QStandardItem;
        nameAttribute->setText(registrationList.at(var)->getAttendee().getName());
        table.setItem(rowCount,0,nameAttribute);

        QStandardItem *affiliationAttribute = new QStandardItem;
        affiliationAttribute->setText(registrationList.at(var)->getAttendee().getAffiliation());
        table.setItem(rowCount,1,affiliationAttribute);

        QStandardItem *emailAttribute = new QStandardItem;
        emailAttribute->setText(registrationList.at(var)->getAttendee().getEmail());
        table.setItem(rowCount,2,emailAttribute);

        QStandardItem *registrationTypeAttribute = new QStandardItem;
        registrationTypeAttribute->setText(registrationList.at(var)->getType());
        table.setItem(rowCount,3,registrationTypeAttribute);

        int start=0;
        int end=0;
        QString qVar = "qualification: ";
        QString cVar = "category: ";
        QString substr;
        QStandardItem *qualificationOrCategoryAttribute = new QStandardItem;
        if(registrationList.at(rowCount)->toString().contains("category", Qt::CaseInsensitive)){
            start = registrationList.at(rowCount)->toString().indexOf(cVar,0,Qt::CaseInsensitive);
            start += cVar.length()-1;
            substr = registrationList.at(rowCount)->toString().mid(start);
            qualificationOrCategoryAttribute->setText(substr);

        }else if(registrationList.at(rowCount)->toString().contains("qualification", Qt::CaseInsensitive)){
            start = registrationList.at(rowCount)->toString().indexOf(qVar,0,Qt::CaseInsensitive);
            start += qVar.length()-1;
            substr = registrationList.at(rowCount)->toString().mid(start);
            qualificationOrCategoryAttribute->setText(substr);
        }else{
            qualificationOrCategoryAttribute->setText("");
        }
        table.setItem(rowCount,4,qualificationOrCategoryAttribute);

        QStandardItem *bookingDate = new QStandardItem;
        bookingDate->setText(registrationList.at(var)->getBookingDate().toString());
        table.setItem(rowCount,5,bookingDate);

        QStandardItem *registrationFee = new QStandardItem;
        registrationFee->setText(QString::number(registrationList.at(var)->calculateFee()));
        table.setItem(rowCount, 6, registrationFee);

        rowCount++;
    }

    return;
}

void MainWindow::updateTable(){
    int index;
    index = (registrationList.totalRegistrations()-1);
    //Add each attribute to the attendee table
    QStandardItem *nameAttribute = new QStandardItem;
    nameAttribute->setText(registrationList.at(index)->getAttendee().getName());
    table.setItem(index,0,nameAttribute);

    QStandardItem *affiliationAttribute = new QStandardItem;
    affiliationAttribute->setText(registrationList.at(index)->getAttendee().getAffiliation());
    table.setItem(index,1,affiliationAttribute);

    QStandardItem *emailAttribute = new QStandardItem;
    emailAttribute->setText(registrationList.at(index)->getAttendee().getEmail());
    table.setItem(index,2,emailAttribute);

    QStandardItem *registrationTypeAttribute = new QStandardItem;
    registrationTypeAttribute->setText(registrationList.at(index)->getType());
    table.setItem(index,3,registrationTypeAttribute);

    QStandardItem *qualificationOrCategoryAttribute = new QStandardItem;
    qualificationOrCategoryAttribute->setText(qualificationCategoryLineEdit.text());
    table.setItem(index,4,qualificationOrCategoryAttribute);

    /*int start=0;
    int end=0;
    QString qVar = "qualification: ";
    QString cVar = "category: ";
    QString substr;
    QStandardItem *qualificationOrCategoryAttribute = new QStandardItem;
    if(registrationList.at(index)->toString().contains("category", Qt::CaseInsensitive)){
        start = registrationList.at(index)->toString().indexOf(cVar,0,Qt::CaseInsensitive);
        start += cVar.length()-1;
        substr = registrationList.at(index)->toString().mid(start);
        qualificationOrCategoryAttribute->setText(substr);

    }else if(registrationList.at(index)->toString().contains("qualification", Qt::CaseInsensitive)){
        start = registrationList.at(index)->toString().indexOf(qVar,0,Qt::CaseInsensitive);
        start += qVar.length()-1;
        substr = registrationList.at(index)->toString().mid(start);
        qualificationOrCategoryAttribute->setText(substr);
    }else{
        qualificationOrCategoryAttribute->setText("");
    }
    table.setItem(index,4,qualificationOrCategoryAttribute);*/

    QStandardItem *bookingDate = new QStandardItem;
    bookingDate->setText(registrationList.at(index)->getBookingDate().toString("dd/M/yyyy"));
    table.setItem(index,5,bookingDate);

    //registrationType
    QStandardItem *registrationFee = new QStandardItem;
    registrationFee->setText(QString::number(registrationList.at(index)->calculateFee()));
    table.setItem(index, 6, registrationFee);
}
