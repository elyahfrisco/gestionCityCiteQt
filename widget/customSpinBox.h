#ifndef CUSTOMSPINBOX_H
#define CUSTOMSPINBOX_H

#include <QObject>
#include <QWidget>
#include <QSpinBox>

class CustomSpinBox: public QSpinBox
{
public:
    CustomSpinBox(QWidget* parent, int min, int max);
};

#endif // CUSTOMSPINBOX_H
