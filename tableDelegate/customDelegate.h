#ifndef CUSTOMDELEGATE_H
#define CUSTOMDELEGATE_H

#include "format.h"
#include "widget/customLineEdit.h"
#include "widget/customSpinBox.h"
#include "widget/customCombo.h"
#include "database/db.h"

#include <QObject>
#include <QStyledItemDelegate>
#include <QWidget>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QLineEdit>


class CustomDelegate: public QStyledItemDelegate
{
public:
    explicit CustomDelegate(QObject *parent = nullptr, QString display=QString());
    QString displayText(const QVariant& value, const QLocale& locale) const override;


private:
    QString display;
};

#endif // CUSTOMDELEGATE_H
