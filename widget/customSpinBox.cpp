#include "customSpinBox.h"

CustomSpinBox::CustomSpinBox(QWidget* parent, int min, int max)
    :QSpinBox(parent)
{
    this->setMinimum(min);
    this->setMaximum(max);

}

