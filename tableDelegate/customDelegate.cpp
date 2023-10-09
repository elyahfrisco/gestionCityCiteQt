#include "customDelegate.h"

CustomDelegate::CustomDelegate(QObject *parent, QString display)
    :QStyledItemDelegate(parent)
{
    this->display = display;
}

QString CustomDelegate::displayText(const QVariant& value, const QLocale& locale) const{
    Q_UNUSED(locale);
    if(display == "phoneNumber"){
        return Format::phoneNumber(value.toString());
    }
    return value.toString();
}
