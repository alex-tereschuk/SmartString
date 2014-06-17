#include <QCoreApplication>
#include <string>
#include <iostream>
using namespace std;

class SmartStringData{
private:
    short refcount;
public:
    string data;
    SmartStringData(){refcount=1;}
    SmartStringData(string _data){data=_data;refcount=1;}
    void incRef(){refcount++;}
    void decRef(){--refcount; if(refcount==0) delete this;}
    short RefNumber(){return refcount;}
};

class SmartString{
public:
    SmartStringData* shared;
    SmartString(){shared = new SmartStringData();}
    SmartString(string i){shared = new SmartStringData(i);}
    SmartString(const SmartString& data){shared = data.shared; shared->incRef();}
    SmartString(const char *ch){string s = (const char*) ch; shared = new SmartStringData(s);}  //SmartString a = "123";

    const SmartString& operator=(const SmartString& data){if(shared!=data.shared){              //SmartString a=b
            shared->decRef();
            shared = data.shared;
            shared->incRef();}
                                                         }
    const SmartString& operator=(const string& data){if(shared->data!=data){                   //string a="123"; SmartString b = a;
            shared->decRef();
            shared = new SmartStringData(data);
            shared->incRef();}
                                                    }

    ~SmartString(){shared->decRef();}
    string toString(){return shared->data;}
};

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

    SmartString c = "ccc";
    cout << "c " << c.toString() << " " << &c.shared->data << endl;

    string str = "test";
    SmartString d = str;
    cout << "d "<< d.toString() << " " << &d.shared->data << endl;

    SmartString e = SmartString(c);
    cout << "e "<< e.toString() << " " << &e.shared->data << endl;
    return 0;
}
