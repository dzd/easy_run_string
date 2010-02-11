using namespace std;

// QT includes
#include <QApplication>

#include "Data.hpp"
#include "View.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    
    Data * d = Data::GetInstance();
    EasyView * v = EasyView::GetInstance();

    if (!d->LoadDescXml(QString("/home/dzd/devel/easy_run_string/data/desc.xml")))
        cout << "Error while loading file..." << endl;

    return app.exec();
}