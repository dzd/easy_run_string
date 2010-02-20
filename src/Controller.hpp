#ifndef __EASY_CONTROLLER_
#define __EASY_CONTROLLER_

using namespace std;

#include "Data.hpp"
#include "View.hpp"


class EasyController
{
private:
    static EasyController * p_instance;

    EasyView    * view;
    Data        * data;

    EasyController();

    void InitView();
    void InitData();

public:
    static EasyController * GetInstance();

};

#endif // __EASY_CONTROLLER_