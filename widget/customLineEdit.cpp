#include "customLineEdit.h"

CustomLineEdit::CustomLineEdit(QWidget* parent, QString regex, QString errorMsg)
    :QLineEdit(parent)
{
    QRegularExpressionValidator* validator = new QRegularExpressionValidator(QRegularExpression(regex), this);
    this->setValidator(validator);
    this->errorMsg = errorMsg;

    connect(this, &QLineEdit::textChanged, this, &CustomLineEdit::onTextChanged);
}

void CustomLineEdit::onTextChanged(const QString &text)
{
    int pos = 0;
    QString modifiableText = text;  // Créez une copie modifiable de la chaîne de texte
    QValidator::State state = validator()->validate(modifiableText, pos);  // Utilisez la copie modifiable
    if (state == QValidator::Invalid) {
        showErrors();
    } else {
        hideErrors();
    }
}

void CustomLineEdit::showErrors(){
    QPoint pos = this->mapToGlobal(QPoint(0, 15));
    QToolTip::showText(pos, errorMsg);
}

void CustomLineEdit::hideErrors(){
    QToolTip::hideText();
}

void CustomLineEdit::setupUI(QString regex, QString errorMsg){
    QRegularExpressionValidator* validator = new QRegularExpressionValidator(QRegularExpression(regex), this);
    this->setValidator(validator);
    this->errorMsg = errorMsg;

    connect(this, &QLineEdit::textChanged, this, &CustomLineEdit::onTextChanged);
}
