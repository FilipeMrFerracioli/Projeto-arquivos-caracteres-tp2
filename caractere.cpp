#include "caractere.h"

namespace minhaNamespace {

Caractere::Caractere()
{

}

QString Caractere::inverterCaractere(QString texto)
{
    QString res;

    for(int i = 0; i < texto.length(); i++) {
        int c = texto.at(i).toLatin1();

        if(c >= 65 && c <= 90) {
            c += 32;
            res += QString(QChar::fromLatin1(c));
        } else if(c >= 97 && c <= 122) {
            c -= 32;
            res += QString(QChar::fromLatin1(c));
        } else {
            res += texto.at(i);
        }
    }

    return res;
}

}
