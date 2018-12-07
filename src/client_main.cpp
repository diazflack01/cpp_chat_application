#include <iostream>

#include <QApplication>
#include <QMainWindow>

#include "ui_mainwindow.h"
#include "ui_form.h"
#include "client.h"

class MaWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow* ui;

private slots:
    void on_pushButton_clicked()
    {
        ui->plainTextEdit->setPlainText(ui->plainTextEdit_2->toPlainText());
        ui->plainTextEdit_2->clear();
    }
public:
    explicit MaWindow(QMainWindow* parent = nullptr)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
    }

    ~MaWindow()
    {
        delete ui;
    }
};

#include "client_main.moc"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    std::cout << "main\n";

    MaWindow m;
    m.show();

//    Client c;
//    c.connectTo(argv[1], atoi(argv[2]));
//    if(!c.isConnected())
//    {
//        std::cout << "Unable to connect to host\n";
//    }
//    c.startCommunication();

    return app.exec();
}
