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
#include <QComboBox>

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
    bool isFolded;
    QSpacerItem * hspacer;

    void InitWidget(QString opt);

protected:
    QHBoxLayout   * mainlayout;
    QCheckBox     * maincheckbox;
    QLabel        * opt_label;

    void MoveSpacerRight();

    void SetFoldState(bool b) { isFolded = b; }

    virtual void Fold() {}

public:
    EasyViewWidget(QWidget* q, QString opt, bool isFolded = false );
    virtual ~EasyViewWidget() {}

    virtual string toStr() = 0;

    bool GetFoldState() { return isFolded; }
    
public slots:
    virtual void OnCheck(int state) {}
};

/*---------------------------------------------------------------------*/
class BasicOptWidget : public EasyViewWidget
{
    Q_OBJECT
private:
    QLineEdit   * value_text;

    void InitWidget(QString description);

protected:
    virtual void Fold();

public:
    BasicOptWidget(QWidget* parent, QString opt, QString value);

    virtual string toStr();

public slots:
    virtual void OnCheck(int state);
};

/*---------------------------------------------------------------------*/
class ComboboxtWidget : public EasyViewWidget
{
    Q_OBJECT
private:
    QComboBox   * combobox;

    void InitWidget(list<string> list);

protected:
    virtual void Fold();

public:
    ComboboxtWidget(QWidget* parent, QString opt, QString value);

    virtual string toStr();

public slots:
    virtual void OnCheck(int state);
};


#endif // __ERS_VIEW_