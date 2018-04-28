#include <QCoreApplication>
#include <QDebug>
#include "cxxlib.h"

class Object
{
public:
    Object()
    {
        qDebug() << "Default constructor.";
    }
    ~Object()
    {
        qDebug() << "Destructor.";
    }

    void Method()
    {
        qDebug() << "Method.";
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    {
        auto object = cxx::Make<Object>();
        object->Method();
    }

    return a.exec();
}
