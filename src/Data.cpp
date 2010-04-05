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

    WidgetData * wd = NULL;
    // Get widget type association
    wd = GetWidgetTypeAssociation(widget_type);

    if (wd == NULL)
    {
        cout << "Unable to get widget data association, skip those data" << endl;
        return;
    }

    list<string> fl = wd->GetFieldList();

    // for each field required by the widget data
    // search in dom for value and fill the widget data
    QString field;
    list<string>::iterator flistbegin = fl.begin();
    list<string>::iterator flistend = fl.end();
    list<string>::iterator flist_it = flistbegin;

    for(; flist_it!=flistend; flist_it++)
    {
        field = e.attribute(QString((*flist_it).c_str()), "");
        if(field != "")
        {
            wd->SetField((*flist_it),field.toStdString());
        }
    }

    // display all the widget data and their content

    // eventually append the new widgetData to the WidgetData list
    widgetdata_list.push_back(*wd);
    p_widgetdata_list.push_back(wd);

/*    // Temp test
    BasicOptWidgetData * test = dynamic_cast<BasicOptWidgetData*>((*p_widgetdata_list.begin()));
    if (test)
        cout << "dynamic_cast worked !" << endl;
    else
        cout << "dynamic_cast failed !" << endl;
    */
}

/**
* Retrieve widgetType association with actual WidgetData Object
* \param widget_type the widget type
* \param w WidgetData pointer to get the empty widgetData created
*/
WidgetData * Data::GetWidgetTypeAssociation(QString & widget_type)
{
    WidgetData * w = NULL; 
    // temporary hard coded
    if ( widget_type == "basic_opt")
    {
        cout << "-- A basic opt widget must be created." << endl;
        w = new BasicOptWidgetData("void");
    }
    return w;
}


/**
* Return a copy of the WidgetData list (for the view)
*/
/*list<WidgetData> Data::GetWidgetDataList()
{
    //cout << "Data::GetWidgetDataList, list size: " << widgetdata_list.size() << endl;
    return widgetdata_list;
}*/

/**
* Return a const iterator on widget data list.
*/
const list<WidgetData*>& Data::GetWidgetDataList()
{
    return p_widgetdata_list;
}

//--------------------------------------------------------------------------------------------
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
//void WidgetData::GetFieldList(list<string> l)
list<string> WidgetData::GetFieldList()
{
    cout << "WidgetData::GetFieldList FieldList, size : " << fieldlist.size() << endl;
    return fieldlist;
}

/**
* Set field associated value
*/
void WidgetData::SetField(string name, string value)
{
    cout << "[" << name << ":" << value <<"]"<< endl;
    field_value_list[name] = value;
}
/**
* Access to field value
*/
string WidgetData::GetField(string name)
{
    return field_value_list[name];
}

//--------------------------------------------------------------------------------------------
/**
* Simple widget data
*/
BasicOptWidgetData::BasicOptWidgetData(string name)
                  : WidgetData(name)
{
    cout << "BasicOptWidgetData created." << endl;
    fieldlist.push_back("name");
    fieldlist.push_back("opt");
    fieldlist.push_back("usage");
    fieldlist.push_back("erf");

    cout << "BasicOptWidgetData:: FieldList, size : " << fieldlist.size() << endl;
}

void BasicOptWidgetData::GetType(string & type)
{

}
//--------------------------------------------------------------------------------------------