using namespace std;

// QT includes
#include <QApplication>

//#include "Data.hpp"
//#include "View.hpp"
#include "Controller.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
/*
    Data * d = Data::GetInstance();
    EasyView * v = EasyView::GetInstance();

    if (!d->LoadDescXml(QString("data/desc.xml")))
        cout << "Error while loading file..." << endl;
*/

    EasyController * c = EasyController::GetInstance();
    return app.exec();
}
