#ifndef CHATBOXTEXTEDIT_H
#define CHATBOXTEXTEDIT_H

#include <QPlainTextEdit>

class ChatBoxTextEdit final : public QPlainTextEdit
{
    Q_OBJECT
signals:
    void enterPressed(const QString& s);
protected:
    void keyPressEvent(QKeyEvent *e) override final;
public:
    ChatBoxTextEdit(QWidget* parent = nullptr);
};

#endif // CHATBOXTEXTEDIT_H
