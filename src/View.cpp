#include "View.hpp"

// temp
#include <iostream>

#include <typeinfo>


using namespace std;

// View
EasyView * EasyView::p_instance = NULL;


/**
* EasyView is a singleton object
* use GetInstance to use it
**/
EasyView * EasyView::GetInstance()
{
    if(! EasyView::p_instance )
         EasyView::p_instance = new EasyView();
    return EasyView::p_instance;
}

/**
* EasyView constructor.
*/
EasyView::EasyView()
{
    InitWidget();
}

/**
* Refresh the whole list of widget displayed
* with the WidgetData list provided as argument.
*/
void EasyView::Refresh(const list<WidgetData*>& wd)
{
    //cout << "EasyView::Refresh, list size: " << it.size() << endl;
    list<WidgetData*>::const_iterator wd_begin = wd.begin();
    list<WidgetData*>::const_iterator wd_end = wd.end();
    list<WidgetData*>::const_iterator wd_it = wd_begin;

    QWidget * qw;
    for(; wd_it != wd_end; wd_it++)
    {
        cout << "Working on: " << (*wd_it)->GetField("name") << endl;
        // for wd create a view widget

        qw = GetWidget((*wd_it));
        AppendWidget(qw);
    }

}


QWidget * EasyView::GetWidget(WidgetData* w)
{
    BasicOptWidgetData* bowd = dynamic_cast<BasicOptWidgetData*>(w);

    if (bowd)
    {
        return new BasicOptWidget(this, QString("opt"), QString(bowd->GetField("opt").c_str()));
    } else {
        cout << "Unable to cast the WidgetData..., no widget generated" << endl;
        return NULL;
    }
}

void EasyView::AppendWidget(QWidget* qw)
{
    if (qw != NULL)
    {
        bodylayout->addWidget(qw);
    } else {
        cout << "Error inserting widget"<< endl;
    }
}


/**
* Remove the spacer Item from the specified layout (todo)
*/
//TODO: add a layout as parameter
void EasyView::RemoveSpacer()
{
    QLayoutItem *child;
    QWidget * w;
    QSpacerItem * qs = NULL;
    
    int i = 0;
    while ((child = bodylayout->takeAt(i)) != 0)
    {
        i++;
        if (!(w = child->widget()))
        return;

        qs = dynamic_cast<QSpacerItem*>(w);

        if (qs)
        {
            bodylayout->removeItem(child);
            delete w;
            delete child;
        }
    }
}

/**
* Compute runstring with the current value displayed in each widget
*/
void EasyView::ComputeRunstring()
{
// for each widget call a method (from data ?? ) which return the string associated to the opt
    string temp = "trololololol";
    SetRunstring(temp);
}

/**
* Initilization of all the QT widgets.
*/
void EasyView::InitWidget()
{
    setMinimumSize(400,600);


    //--- menu ---
    menubar = new QMenuBar(this);

    open = new QAction(tr("Open..."), this);
    save = new QAction(tr("Save"), this);
    saveas = new QAction(tr("Save as..."), this);
    addfields = new QAction(tr("Add fields..."), this);
    test = new QAction(tr("test"), this);
    quit = new QAction(tr("Quit"), this);

    file = new QMenu(tr("File"));
    file->addAction(open);
    file->addAction(save);
    file->addAction(saveas);
    file->addAction(addfields);
    file->addSeparator();
    file->addAction(test);
    file->addSeparator();
    file->addAction(quit);

    menubar->addMenu(file);

    setMenuBar(menubar);

    // --- central widget ---
    scrollarea = new QScrollArea(this);
    mainwidget = new QWidget(this);

    bodywidget = new QWidget(this);
    scrollarea->setWidget(bodywidget);
    scrollarea->setWidgetResizable(true);

    setCentralWidget(mainwidget);

    // layout for the main widget
    mainlayout = new QVBoxLayout(this);
    mainlayout->setMargin(0);
    mainlayout->setSpacing(0);
    mainwidget->setLayout(mainlayout);

    // layout for the body widget
    bodylayout = new QVBoxLayout(this);
    bodylayout->setMargin(0);
    bodylayout->setSpacing(0);
    bodywidget->setLayout(bodylayout);
    

    // header widget 
    exec_gbox = new QGroupBox(scrollarea);
    exec_gbox->setMinimumSize(QSize(0, 60));
    // TODO: setup a variable for this string.
    exec_gbox->setTitle("Executable name: ");
    exec_hbox = new QHBoxLayout(exec_gbox);
    exec_label = new QLabel(exec_gbox);
    // TODO: setup a variable for this string.
    exec_label->setText("No executable name specified...");
    exec_hbox->addWidget(exec_label);
    mainlayout->addWidget(exec_gbox);

    // initiate empty list : only one spacer
    /*verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainlayout->addItem(verticalSpacer);*/
    mainlayout->addWidget(scrollarea);
    

    // footer widget
    runstring_gbox = new QGroupBox(scrollarea);
    runstring_gbox->setMinimumSize(QSize(0, 60));
    // TODO: setup a variable for this string.
    runstring_gbox->setTitle("Runstring preview:");
    runstring_hbox = new QHBoxLayout(runstring_gbox);
    runstring_lineEdit = new QLineEdit(runstring_gbox);
    runstring_button = new QToolButton(runstring_gbox);
    // TODO: pour l'internationalisation:
    //runstring_button->setText(QApplication::translate("Dialog", "run !", 0, QApplication::UnicodeUTF8));
    runstring_button->setText("run!");
    runstring_hbox->addWidget(runstring_lineEdit);
    runstring_hbox->addWidget(runstring_button);
    mainlayout->addWidget(runstring_gbox);
    
    scrollarea->show();
    bodywidget->show();
    mainwidget->show();
    this->show();

    //connection time
    connect(quit, SIGNAL(triggered()), this, SLOT(OnQuit()));
    connect(test, SIGNAL(triggered()), this, SLOT(OnTest()));
    
/*
    connect(open, SIGNAL(triggered()), this, SLOT(OnOpen()));
    connect(save, SIGNAL(triggered()), this, SLOT(OnSave()));
    connect(saveas, SIGNAL(triggered()), this, SLOT(OnSaveAs()));
    connect(addfields, SIGNAL(triggered()), this, SLOT(OnAddFields()));


    connect(treeview,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(OnTreeDoubleClicked(QModelIndex)));
    connect(descdata,SIGNAL(WriteFileError(QString)),this,SLOT(OnWriteFileError(QString)));
*/
}


/**
* SLOT triggered by 'test' menu
* used for testing purpose
*/
void EasyView::TestWidgetInsertion()
{
    /*
    QWidget * q = new BasicOptWidget(this, QString("-plop"), QString("vide..."));
    mainlayout->addWidget(q);
    */
    //RemoveSpacer();
    ComputeRunstring();
    SetExecName("plop");
}


/**
* SLOT triggered by 'quit' menu
*/
void EasyView::OnQuit()
{
    cout << "Exiting !"<< endl;
    qApp->quit();
}

//--------------------------------------------------------------------------------------------------------------------
BasicOptWidget::BasicOptWidget(QWidget* parent, QString opt, QString value)
              : QWidget(parent)
{
    InitWidget(opt, value);
}


void BasicOptWidget::InitWidget(QString opt, QString value)
{
//     groupbox = new QGroupBox(this);
//     groupbox->setTitle(title);

    opt_text = new QLineEdit(this);
    opt_text->setReadOnly(true);
    opt_text->insert(opt);

    value_text = new QLineEdit(this);
    value_text->insert(value);

    mainlayout = new QHBoxLayout(this);

    mainlayout->addWidget(opt_text);
    mainlayout->addWidget(value_text);

    this->setLayout(mainlayout);
}