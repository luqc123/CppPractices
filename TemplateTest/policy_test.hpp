#ifndef POLICY_TEST_H
#define POLICY_TEST_H

#include "policy.hpp"
#include <iostream>

class Widget {};
class Widget2 {};

using namespace std;

namespace policy_test {

void testcase() {
	typedef WidgetManager1<OpNewCreator<Widget>> MyManager1;
	typedef WidgetManager2<OpNewCreator> MyManager2;
	typedef WidgetManager3<> MyManager3;
	cout << "hello,world" << endl;
	typedef WidgetManager2<PrototypeCreator> MyManager4;
	//works
	MyManager4 mymanager4;
	Widget* pWidget = new Widget();
	Widget* pNewWidget = new Widget();
    mymanager4.SetPrototype(pWidget);
	mymanager4.SwitchPrototype(pNewWidget);
	typedef WidgetManager2<OpNewCreator> Mymanager5;
	//error GetPrototype is not member of OpNewCreator
	//Mymanager5 mymanager5;
	//mymanager5.SwitchPrototype(new Widget);
	//woks not call SwitchPrototype
	Mymanager5 mymanager5;
}
}

#endif