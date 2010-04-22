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
#include <QLabel>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>
#include <QSpacerItem>
#include <QCheckBox>

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
    QWidget     * mainwidget,
                * bodywidget;
    QVBoxLayout * mainlayout,
                * bodylayout;



    //QWidget *verticalLayoutWidget;

    QVBoxLayout *verticalLayout;
    QWidget *horizontalLayoutWidget_2;

    // executable header
    QGroupBox   * exec_gbox;
    QHBoxLayout * exec_hbox;
    QLabel      * exec_label;

    // spacer
    QSpacerItem * verticalSpacer;

    // runstring footer
    QGroupBox   * runstring_gbox;
    QHBoxLayout * runstring_hbox;
    QLineEdit   * runstring_lineEdit;
    QToolButton * runstring_button;

    // menu
    QMenuBar    * menubar;
    QMenu       * file;
    QAction     * open,
                * save,
                * saveas,
                * test,
                * addfields,
                * quit,
                * run;

    // Presentation
    void InitWidget();
    void Empty();

    // Metier
    void Populate();
    void SynchroniseToData();

    QWidget * GetWidget(WidgetData* w);
    void AppendWidget(QWidget* qw);

    void RemoveSpacer();
    void MoveSpacerToBottom();

    void ComputeRunstring();

    EasyView();

public:
    static EasyView * GetInstance();

    void Refresh(const list<WidgetData*>& wd);
    void SetRunstring(string s) { runstring_lineEdit->setText(QString(s.c_str()));}
    void SetExecName(string s) { exec_label->setText(QString(s.c_str()));}

    string GetDisplayedExecName() { return exec_label->text().toStdString(); }

    //temp
    void TestWidgetInsertion();

private slots:
/*  bool OnSave();
    bool OnSaveAs();
    void OnClose();*/
    void OnQuit();
    void OnTest();
    void OnRun();

};

class EasyViewWidget : public QWidget
{
    Q_OBJECT
private:
    QSpacerItem * hspacer;

    void InitWidget();

protected:
    QHBoxLayout   * mainlayout;
    QCheckBox     * maincheckbox;

    void MoveSpacerRight();
    void Fold() {}
    void Unfold() {}

public:
    EasyViewWidget(QWidget* q);
    virtual ~EasyViewWidget() {}

    virtual string toStr() = 0;

public slots:
    virtual void OnCheck(int state) {}
};

/*---------------------------------------------------------------------*/
class BasicOptWidget : public EasyViewWidget
{
    Q_OBJECT
private:
    QLabel      * opt_label;
    QLineEdit   * value_text;

    void InitWidget(QString optname, QString description);

protected:
    void Fold();
    void Unfold();

public:
    BasicOptWidget(QWidget* parent, QString opt, QString value);

    virtual string toStr();

public slots:
    virtual void OnCheck(int state);

//     QString getTitle() { return groupbox->title(); }
//     QString getText() { return textedit->toPlainText(); }

};

#endif // __ERS_VIEW_