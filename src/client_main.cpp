#include <iostream>

#include <QApplication>
#include <QMainWindow>

#include <QScrollBar>
#include <QTimer>

#include "ui_mainwindow.h"
#include "client.h"

class MaWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow* ui;

    void moveScrollBarToBottom()
    {
        ui->scrollArea->verticalScrollBar()->setSliderPosition(ui->scrollArea->verticalScrollBar()->maximum());
        ui->plainTextEdit->moveCursor(QTextCursor::End);
    }
private slots:
    void on_pushButton_clicked()
    {
        if (!ui->plainTextEdit_2->toPlainText().isEmpty()) {
            ui->plainTextEdit->insertPlainText(ui->plainTextEdit_2->toPlainText() + "\n");
            ui->plainTextEdit->moveCursor(QTextCursor::End);
            moveScrollBarToBottom();
        }
    }
public:
    explicit MaWindow(QMainWindow* parent = nullptr)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
        QObject::connect(ui->plainTextEdit_2, &ChatBoxTextEdit::enterPressed,
                         [&](const QString& msg){
            ui->plainTextEdit->insertPlainText(msg+"\n");
            ui->plainTextEdit->moveCursor(QTextCursor::End);
            moveScrollBarToBottom();
        });
        QTimer::singleShot(100, [&](){ this->moveScrollBarToBottom(); });
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
