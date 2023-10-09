#ifndef CUSTOMLINEEDIT_H
#define CUSTOMLINEEDIT_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QLineEdit>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QToolTip>

class CustomLineEdit: public QLineEdit
{
    Q_OBJECT
public:
    CustomLineEdit(QWidget* parent=nullptr, QString regex=QString(), QString errorMsg=QString());
    void setupUI(QString regex=QString(), QString errorMsg=QString());

private slots:
    void showErrors();
    void hideErrors();
    void onTextChanged(const QString &text);  // Ajoutez cette ligne

private:
    QString errorMsg;
};

#endif // CUSTOMLINEEDIT_H
