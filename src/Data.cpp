#include "Data.hpp"

using namespace std;

// Data
Data * Data::p_instance = NULL;

/**
* Data is a singleton object
* use GetInstance to use it
**/
Data * Data::GetInstance()
{
    if(!Data::p_instance)
        Data::p_instance = new Data();

    return Data::p_instance;
}

/**
* Private constructor for Data class
*/
Data::Data()
{
    cout << "Data constructed" << endl;
}

/**
* Load xml description of the UI
* \param filename : filename to load.
*/
bool Data::LoadDescXml(QString filename)
{
    QDomDocument d;
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return false;
    if (!d.setContent(&file)) {
        file.close();
        return false;
    }
    file.close();

    QDomElement docElem = d.documentElement();
    cout << "Root : " << docElem.tagName().toStdString() << endl;

    // Get the list of widgets
    QDomNodeList nodelist_widget = d.elementsByTagName(QString("widget"));
    QDomNode node;
    //QDomNodeAttributesMap attr_map;
    
    // And read them all
    for (unsigned int i = 0; i< nodelist_widget.length(); i++)
    {
        node = nodelist_widget.item(i);

        if (!node.hasAttributes())
            break;

        // try to convert QDomNode to Element
        QDomElement e = node.toElement();
        if(e.isNull())
            break;

        // OK we have got the element
        AddWidget(e);
    }
    return true;
}


/**
* Add widget to widgetData list
* \param e a QDomElement containing widget description
*/
void Data::AddWidget(QDomElement & e)
{
    //Get the type of widget
    QString widget_type = e.attribute("type");
    cout << "Widget type: "<< widget_type.toStdString() << endl;

    WidgetData * wd;
    // Get widget type association
    GetWidgetTypeAssociation(widget_type, wd);


    QString field;

// buggué donc hardcoded temporairement
//    list<string> fieldlist = wd->GetFieldList();
    list<string> fieldlist;
    fieldlist.push_back("name");
    fieldlist.push_back("opt");
    fieldlist.push_back("usage");
    fieldlist.push_back("erf");

    
    list<string>::iterator flistbegin = fieldlist.begin();
    list<string>::iterator flistend = fieldlist.end();
    list<string>::iterator flist_it = flistbegin;
    for(; flist_it!=flistend; flist_it++)
    {
        cout << "---" << (*flist_it) << endl;
        field = e.attribute(QString((*flist_it).c_str()), "");
        if(field != "")
            wd->FillField((*flist_it),field.toStdString());
    }


    // get list of mandatory fields requested by the widget and fill them


    // get list of optional fields requested by the widget and fill them

    
    // temp test
/*
    cout << e.attribute("name", "NA").toStdString() << endl;
    cout << e.attribute("opt", "NA").toStdString() << endl;
    cout << e.attribute("usage", "NA").toStdString() << endl;
*/
    // Now try to read all the param known for the type of widget
    // param list currently hardcoded
    // name, opt, usage


    // then a specific method is called for this type
}

/**
* Retrieve widgetType association with actual WidgetData Object
* \param widget_type the widget type
* \param w WidgetData pointer to get the empty widgetData created
*/
void Data::GetWidgetTypeAssociation(QString & widget_type, WidgetData * w)
{
    // temporary hard coded
    if ( widget_type == "basic_opt")
    {
        cout << "-- A basic opt widget must be created." << endl;
        w = new BasicOptWidgetData("void");
    }
}

/**
* Base widgetdata
*/
WidgetData::WidgetData(string name)
{
    this->name = name;
    cout << "WidgetData created ["<<name<<"]." << endl;
}

/**
* Return a list of field required by the widgetdata
*/
list<string> & WidgetData::GetFieldList()
{
    return fieldlist;
}

/**
* Return a list of field required by the widgetdata
*/
void WidgetData::FillField(string name, string value)
{
    cout << "[" << name << ":" << value <<"]"<< endl;
}



/**
* Simple widget data 
*/
BasicOptWidgetData::BasicOptWidgetData(string name)
                  : WidgetData(name)
{
    cout << "BasicOptWidgetData created." << endl;
}

void BasicOptWidgetData::GetType(string & type)
{

}
