#include <QCoreApplication>
#include <iostream>
#include "smartstring.h"
using namespace std;

int main()
{
    SmartString a("Hello");
    cout << "a "<< a.toString() << " " << &a.shared->data << endl;
    SmartString b("World");
    cout << "b "<< b.toString() << " " << &b.shared->data << endl;
    cout << "a "<< a.shared->RefNumber() << endl;
    cout << "b "<< b.shared->RefNumber() << endl;
    b = a;
    cout << "a "<< a.toString() << " " << &a.shared->data << endl;
    cout << "b "<< b.toString() << " " << &b.shared->data << endl;
    cout << "a "<< a.shared->RefNumber() << endl;
    cout << "b "<< b.shared->RefNumber() << endl;
    cout << endl;

    SmartString c = "ccc";
    cout << "c " << c.toString() << " " << &c.shared->data << endl;
    cout << endl;

    string str = "test";
    SmartString d = str;
    cout << "d "<< d.toString() << " " << &d.shared->data << endl;
    cout << endl;

    SmartString e = SmartString(c);
    cout << "e "<< e.toString() << " " << &e.shared->data << endl;
    return 0;
}
