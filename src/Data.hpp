#ifndef _ERS_DATA_
#define _ERS_DATA_

using namespace std;

// standard includes
#include <iostream>

// STL includes
#include <list>
#include <string>
#include <map>

// QT includes
#include <QString>
#include <QDomDocument>
#include <QFile>
#include <QDomNode>
#include <QDomNodeList>
#include <QDomNamedNodeMap>

class WidgetData;

/**
* This is the main data class
*/
class Data
{
private:
//FIXME:  deprecated: to be replaced by p_widgetdata_list
    list<WidgetData> widgetdata_list;
//
    list<WidgetData*>::const_iterator it_p_widgetdata_list;

    list<WidgetData*> p_widgetdata_list;

    static Data * p_instance;
    Data();

    void AddWidget(QDomElement & e);
    WidgetData * GetWidgetTypeAssociation(QString & widget_type);

public:
    static Data * GetInstance();

    bool LoadDescXml(QString filename);

//FIXME: deprecated: to be replaced by list<WidgetData>::const_iterator GetWidgetDataList();
    //list<WidgetData> GetWidgetDataList();
    const list<WidgetData*>& GetWidgetDataList();
};

/**
* Base class for describing widget properties and way to acess them
*/
class WidgetData
{
protected:
    string name;
    list<string> fieldlist;

    map<string, string> field_value_list;

public:
    WidgetData(string name);

//  void GetFieldList(list<string> l);
    list<string> GetFieldList();

    void SetField(string name, string value);
    string GetField(string name);

    virtual void GetType(string & type) {};
};

/**
* Basic widget one option following by inputs
*/
class BasicOptWidgetData : public WidgetData
{
protected:
    string  opt,
            defaultvalue,
            usage;

public:
    BasicOptWidgetData(string name);

    virtual void GetType(string & type);

    void SetOpt(string o) {opt = o;}
    void SetFieldDefault(string d) {defaultvalue = d;}
};



#endif //_ERS_DATA_