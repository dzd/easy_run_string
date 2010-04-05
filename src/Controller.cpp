using namespace std;

#include <iostream>

#include <list>

#include <QString>

#include "Controller.hpp"

// Controller
EasyController * EasyController::p_instance = NULL;

EasyController::EasyController()
{
    InitView();
    InitData();

    if (data->LoadDescXml(QString("data/desc.xml")))
    {
        list<WidgetData> l = data->GetWidgetDataList();
        // for each item in WidgetData list ask the view to append a new widget
        view->Refresh(l);
    } else {
        cout << "Error while loading file..." << endl;
    }

}

/**
* EasyController is a singleton object
* use GetInstance to use it
**/
EasyController * EasyController::GetInstance()
{
    if(! EasyController::p_instance )
         EasyController::p_instance = new EasyController();
    return EasyController::p_instance;
}

void EasyController::InitView()
{
    view = EasyView::GetInstance();
    // setup connections
    //todo: connect(quit, SIGNAL(triggered()), this, SLOT(OnQuit()));
}

void EasyController::InitData()
{
    data = Data::GetInstance();
}