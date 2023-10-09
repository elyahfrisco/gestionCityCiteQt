#include "format.h"

Format::Format()
{

}

QString Format::phoneNumber(QString value){
    value.remove(" ");
    QStringList pieces = value.split("");

    return QString("%1 %2 %3 %4")
        .arg(pieces.at(1) + pieces.at(2) + pieces.at(3),
             pieces.at(4) + pieces.at(5),
             pieces.at(6) + pieces.at(7) + pieces.at(8),
             pieces.at(9) + pieces.at(10));

}
