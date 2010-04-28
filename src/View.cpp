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
    mainlayout = new QVBoxLayout();
    mainlayout->setMargin(0);
    mainlayout->setSpacing(0);
    mainwidget->setLayout(mainlayout);

    // layout for the body widget
    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    bodylayout = new QVBoxLayout();
    bodylayout->setMargin(0);
    bodylayout->setSpacing(0);
    bodywidget->setLayout(bodylayout);
    bodylayout->addItem(verticalSpacer);

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
    mainlayout->addWidget(scrollarea);


    // footer widget
    runstring_gbox = new QGroupBox(scrollarea);
    runstring_gbox->setMinimumSize(QSize(0, 60));
    // TODO: setup a variable for this string.
    runstring_gbox->setTitle("Runstring preview:");
    runstring_hbox = new QHBoxLayout(runstring_gbox);
    runstring_lineEdit = new QLineEdit(runstring_gbox);
    runstring_button = new QToolButton(runstring_gbox);
    //run = new QAction(tr("run"), this);
    //runstring_button->addAction(run);
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
    connect(runstring_button, SIGNAL(clicked()), this, SLOT(OnRun()));

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
    // for each widget data in the list
    for(; wd_it != wd_end; wd_it++)
    {
        // for each field required by the EasyWidget
        cout << "Working on: " << (*wd_it)->GetField("name") << endl;

        // for wd create a view widget
        qw = GetWidget((*wd_it));
        AppendWidget(qw);
    }
    MoveSpacerToBottom();

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
    QSpacerItem * qs = NULL;
    
    for(int i = 0; (child = bodylayout->itemAt(i)) != 0; i++)
    {

        qs = dynamic_cast<QSpacerItem*>(child);

        if (qs)
        {
            bodylayout->removeItem(child);
            delete child;
        }
    }
}

/**
* Move the spacer to the bottom of the list
*/
void EasyView::MoveSpacerToBottom()
{
    QLayoutItem *child;
    QSpacerItem * qs = NULL;

    for(int i = 0; (child = bodylayout->itemAt(i)) != 0; i++)
    {
        qs = dynamic_cast<QSpacerItem*>(child);

        if (qs)
        {
            //cout << "Spacer found at: " << i << endl;
            child = bodylayout->takeAt(i);
            bodylayout->addItem(child);
            return;
        }
    }
}


/**
* Compute runstring with the current value displayed in each widget
*/
void EasyView::ComputeRunstring()
{
    QLayoutItem *child;
    QWidget * w;
    EasyViewWidget * evw;
    string runstring = GetDisplayedExecName()+" ";

    for(int i = 0; (child = bodylayout->itemAt(i)) != 0; i++)
    {
        if ((w = child->widget()))
        {
            evw = dynamic_cast<EasyViewWidget*>(w);

            if (evw)
            {
                if ( evw->GetFoldState())
                {
                    runstring += evw->toStr();
                    runstring += " ";
                }
            }
        }
    }
    SetRunstring(runstring);
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
    RemoveSpacer();
    //MoveSpacerToBottom();
}


/**
* SLOT triggered by 'quit' menu
*/
void EasyView::OnQuit()
{
    cout << "Exiting !"<< endl;
    qApp->quit();
}

/**
* SLOT triggered by 'test' menu
*/
void EasyView::OnTest()
{
    SetExecName("plop");
    //RemoveSpacer();
}

/**
* SLOT triggered by the 'run' button
*/
void EasyView::OnRun()
{
    ComputeRunstring();
}


//--------------------------------------------------------------------------------------------------------------------
EasyViewWidget::EasyViewWidget(QWidget * parent, QString opt,  bool b )
              : QWidget(parent)
{
    SetFoldState( b );
    InitWidget(opt);
}

void EasyViewWidget::InitWidget(QString opt)
{
    mainlayout = new QHBoxLayout(this);
    this->setLayout(mainlayout);

    maincheckbox = new QCheckBox(this);
    maincheckbox->setChecked(this->isFolded);
    mainlayout->addWidget(maincheckbox);

    opt_label = new QLabel(this);
    opt_label->setText(opt);
    mainlayout->addWidget(opt_label);

    hspacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    mainlayout->addItem(hspacer);
}


void EasyViewWidget::MoveSpacerRight()
{
    QLayoutItem * child;
    QSpacerItem * qs = NULL;

    for(int i = 0; (child = mainlayout->itemAt(i)) != 0; i++)
    {
        qs = dynamic_cast<QSpacerItem*>(child);

        if (qs)
        {
            //cout << "Spacer found at: " << i << endl;
            child = mainlayout->takeAt(i);
            mainlayout->addItem(child);
            return;
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------
BasicOptWidget::BasicOptWidget(QWidget* parent, QString opt, QString value)
              : EasyViewWidget(parent, opt)
{
    InitWidget(value);
    Fold();
}


/**
* Init BasicOptWidget
*/
void BasicOptWidget::InitWidget(QString value)
{
    value_text = new QLineEdit(this);
    value_text->insert(value);

    mainlayout->addWidget(value_text);


    connect(maincheckbox, SIGNAL(stateChanged(int)), this, SLOT(OnCheck(int)));

}

/**
* Output into a str the command line equivalent to the widget
*/
string BasicOptWidget::toStr()
{
    return "-"+opt_label->text().toStdString()+" "+value_text->text().toStdString();
}

/**
* Public slot triggered when checkbox is checked
*/
void BasicOptWidget::OnCheck(int state)
{
    if ( state == 0 )
        this->EasyViewWidget::SetFoldState(false);
    else
        this->EasyViewWidget::SetFoldState(true);

    Fold();
}


/**
* Inherited method used to switch the widget to his folded/unfolded version
*/
void BasicOptWidget::Fold()
{
    if ( GetFoldState() )
    {
        value_text->show();
    }
    else
    {
        value_text->hide();
    }
}

//--------------------------------------------------------------------------------------------------------------------

QLabel      * opt_label;
QComboBox   * combobox;

ComboboxtWidget::ComboboxtWidget(QWidget* parent, QString opt, QString value)
               : EasyViewWidget(parent, opt)
{
    list<string> l;
    l.push_back("truc 1");
    l.push_back("truc 2");
    l.push_back("truc 3");
    l.push_back("truc 4");
    
    InitWidget(l);
}

void ComboboxtWidget::InitWidget(list<string> l)
{
    combobox = new QComboBox(this);

    list<string>::iterator it = l.begin();

    for(; it != l.end(); it++)
    {
        combobox->addItem(QString((*it).c_str()));
    }

    mainlayout->addWidget(combobox);
}

void ComboboxtWidget::Fold()
{
    if ( GetFoldState() )
    {
        combobox->show();
    }
    else
    {
        combobox->hide();
    }
}

string ComboboxtWidget::toStr()
{

}


void ComboboxtWidget::OnCheck(int state)
{

}


