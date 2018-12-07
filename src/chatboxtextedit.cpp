#include "chatboxtextedit.h"

ChatBoxTextEdit::ChatBoxTextEdit(QWidget* parent)
    : QPlainTextEdit(parent)
{
}

void ChatBoxTextEdit::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Return) {
        if(!toPlainText().isEmpty())
        {
            emit enterPressed(toPlainText());
            clear();
        }
    } else {
        QPlainTextEdit::keyPressEvent(e);
    }
}
