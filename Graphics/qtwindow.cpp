//
// Created by Evan Kirkiles on 6/15/18.
//

#include "qtwindow.hpp"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateEdit>
#include <QFile>
#include <QLineEdit>

AlgoWindow::AlgoWindow(TradingInterface* i_trader, BuyAndHoldStrategy* i_strat, Benchmark* i_bench, GNUPlotter* i_gnuplot,
                       char* *i_startdateaddr, char* *i_enddateaddr, double* i_initialcapitaladdr, QWidget *parent) : QWidget(parent) {

    interface = i_trader;
    strat = i_strat;
    bench = i_bench;
    gnuplot = i_gnuplot;
    startdateaddr = i_startdateaddr;
    enddateaddr = i_enddateaddr;
    initialcapaddr = i_initialcapitaladdr;

    // Vertical layouts
    auto mainLayout = new QVBoxLayout;
    auto topLayout = new QVBoxLayout;
    auto botLayout = new QVBoxLayout;

    // Horizontal layouts
    auto startdatelayout = new QHBoxLayout;
    auto enddatelayout = new QHBoxLayout;
    auto initialcap = new QHBoxLayout;

    // Set size of the window
    setFixedSize(250, 500);

    // Create the widgets to add to vertical layout
    m_button = new QPushButton("Initialize Backtest", this);
    startdate = new QLabel("Start Date: ", this);
    startdateedit = new QDateEdit(this);
    enddate = new QLabel("End Date: ", this);
    enddateedit = new QDateEdit(this);
    initialcapital = new QLabel("Initial Capital: ", this);
    initialcapedit = new QLineEdit(this);
    totalreturn = new QLabel("Total Return: ", this);
    sharpe = new QLabel("Sharpe Ratio: ", this);
    hwm = new QLabel("High-Water Mark: ", this);
    drawdown = new QLabel("Drawdown: ", this);

    // Create horizontal layouts for top layout
    startdatelayout->addWidget(startdate);
    startdatelayout->addWidget(startdateedit);
    enddatelayout->addWidget(enddate);
    enddatelayout->addWidget(enddateedit);
    initialcap->addWidget(initialcapital);
    initialcap->addWidget(initialcapedit);

    // Add widgets to top layout
    topLayout->addWidget(m_button);
    topLayout->addLayout(startdatelayout);
    topLayout->addLayout(enddatelayout);
    topLayout->addLayout(initialcap);

    // Set widget properties
    m_button->setFixedSize(210, 100);
    m_button->setCheckable(true);
    startdate->setFixedSize(75, 10);
    startdateedit->setDisplayFormat("MM/dd/yyyy");
    enddate->setFixedSize(75, 10);
    enddateedit->setDisplayFormat("MM/dd/yyyy");
    initialcapital->setFixedSize(100, 13);
    initialcapedit->setText("10000000");
    initialcapedit->setValidator(new QIntValidator(1, 100000000, this));

    // Add widgets to bot layout
    botLayout->addWidget(totalreturn);
    botLayout->addWidget(sharpe);
    botLayout->addWidget(hwm);
    botLayout->addWidget(drawdown);

    // Add sub-vertical layouts to main vert layout
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(botLayout);

    // Add the slot and signal for the button click
    connect(m_button, SIGNAL (clicked(bool)), this, SLOT (buttonClicked(bool)));

    // Set window options
    setLayout(mainLayout);
    setWindowTitle(tr("Algorithm Control"));
    setObjectName("main_window");

    // Set the style sheet
    QFile File("/Users/samkirkiles/Desktop/algobacktester/Graphics/stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    setStyleSheet(StyleSheet);
}

// Private slot that listens for when button is clicked
void AlgoWindow::buttonClicked(bool checked) {
    if (checked){
        *startdateaddr = (char*)"2008-01-01";
        *enddateaddr = (char*)"2011-01-01";
        *initialcapaddr = 100000;
        gnuplot->initPlot();
        m_button->setText("Run Backtest");
    } else {
        m_button->setText("Built Backtest");
        interface->runbacktest(*strat, *bench, gnuplot);
    }
}