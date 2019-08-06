#include "notepad.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //对话框类应用中文
    QTranslator user;
    bool ok = user.load("qt_zh_CN.qm", ".");
    a.installTranslator(&user);

    NotePad np;
    if (argc >= 2)
    {
        QString s = QString::fromLocal8Bit(argv[1]);
        np.loadFromFile(s);
    }
    np.show();

    return a.exec();
}
