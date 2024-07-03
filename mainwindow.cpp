#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
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
    inputLayout.addLayout(&registrationOrCategoryLayout);
    qualificationCategoryLabel.setText("Qualification, if StudentR/Category, if GuestR:");
    registrationOrCategoryLayout.addWidget(&qualificationCategoryLabel);
    registrationOrCategoryLayout.addWidget(&qualificationCategoryLineEdit);
    addRegistration.setText("Add Registration");
    inputLayout.addWidget(&addRegistration);
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

    tableHeading.setFont(headerFont);
    tableHeading.setText("Registration List Display");
    mainLayout.addWidget(&tableHeading);

    mainLayout.addWidget(&tableView);
    tableView.setModel(&table);
}

MainWindow::~MainWindow() {}
