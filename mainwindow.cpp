#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    headerFont.setBold(true);
    headerFont.setPointSize(12);
    setWindowTitle("Registration");
    centralWidget.setLayout(&mainLayout);
    setCentralWidget(&centralWidget);

    registrationHeading.setText("Registration Details Group");
    registrationHeading.setFont(headerFont);
    mainLayout.addWidget(&registrationHeading);

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
    registrationTypeLabel.setText("Registration Type:"); //Oscar, this text is not displayed?
    typeOfRegistrationLayout.addWidget(&registrationTypeLabel);
    typeOfRegistrationLayout.addWidget(&registrationTypeLineEdit);
    inputLayout.addLayout(&registrationOrCategoryLayout);
    qualificationCategoryLabel.setText("Registration / Category:");
    registrationOrCategoryLayout.addWidget(&qualificationCategoryLabel);
    registrationOrCategoryLayout.addWidget(&qualificationCategoryLineEdit);
    addRegistration.setText("Add Registration");
    inputLayout.addWidget(&addRegistration);

    outputHeading.setFont(headerFont);
    outputHeading.setText("Action Groups");
    mainLayout.addWidget(&outputHeading);

    mainLayout.addLayout(&outputLayout);
    outputLayout.addLayout(&queryLayout);
    isNameRegisteredLabel.setText("Name:");
    queryLayout.addWidget(&isNameRegisteredLabel);
    queryLayout.addWidget(&isNameRegisteredLineEdit);
    isRegisteredButton.setText("Lookup Attendee");
    queryLayout.addWidget(&isRegisteredButton);
    outputLayout.addLayout(&calculateLayout);
    regestrationTypeQueryLabel.setText("Registration Type:");
    calculateLayout.addWidget(&regestrationTypeQueryLabel);
    calculateLayout.addWidget(&registrationTypeQueryLineEdit);
    calculateButton.setText("Calculate Total Fees");
    calculateLayout.addWidget(&calculateButton);
    outputLayout.addLayout(&countLayout);
    countLabel.setText("Count of which affiliation?");
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
