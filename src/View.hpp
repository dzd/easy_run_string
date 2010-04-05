#ifndef __ERS_VIEW_
#define __ERS_VIEW_

using namespace std;

// STL includes
#include <string>
#include <list>


// QT includes
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include "qapplication.h"
#include <QLineEdit>

// easy_run_string includes
#include "Data.hpp"


class BasicOptWidget;
class WidgetFactory;
class BasicOptWidgetFactory;

class EasyView : public QMainWindow
{
    Q_OBJECT

private:
    static EasyView * p_instance;

    QScrollArea * scrollarea;
    QWidget     * mainwidget;
    QVBoxLayout * mainLayout;

    QMenuBar    * menubar;
    QMenu       * file;
    QAction     * open,
                * save,
                * saveas,
                * test,
                * addfields,
                * quit;


    // Presentation
    void InitWidget();
    void Empty();

    // Metier
    void Populate();
    void SynchroniseToData();

    void GetWidget(WidgetData* w, QWidget* qw);
    void AppendWidget(QWidget* qw);

    EasyView();

public:
    static EasyView * GetInstance();

    void Refresh(list<WidgetData> & l);

    //temp
    void TestWidgetInsertion();

private slots:
/*  bool OnSave();
    bool OnSaveAs();
    void OnClose();*/
    void OnQuit();
    void OnTest() {TestWidgetInsertion();}

};

/*---------------------------------------------------------------------*/
/**
* Base factory class to produce widget
*/
class WidgetFactory
{
protected:
    EasyView * parent;
public:
    WidgetFactory(EasyView * p) { parent = p; }
    virtual void GetWidget(WidgetData* w, QWidget* qw) {}
};

/**
* Factory class to produce BasicOptWidget
*/
class BasicOptWidgetFactory : public WidgetFactory
{
public:
    BasicOptWidgetFactory(EasyView * p);
    virtual void GetWidget(WidgetData* w, QWidget* qw);
};



/*---------------------------------------------------------------------*/
class BasicOptWidget : public QWidget
{
    Q_OBJECT
private:
    QLineEdit   * opt_text,
                * value_text;
    QHBoxLayout * mainlayout;

    void InitWidget(QString optname, QString description);

public:
    BasicOptWidget(QWidget* parent, QString opt, QString value);

//     QString getTitle() { return groupbox->title(); }
//     QString getText() { return textedit->toPlainText(); }

};

#endif // __ERS_VIEW_