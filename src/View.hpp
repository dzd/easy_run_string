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

    QWidget * GetWidget(WidgetData* w);
    void AppendWidget(QWidget* qw);

    EasyView();

public:
    static EasyView * GetInstance();

    void Refresh(const list<WidgetData*>& wd);

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