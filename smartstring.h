#ifndef SMARTSTRING_H
#define SMARTSTRING_H
#include <string>
#include <iostream>
// review notes: Почему это плохо делать в заголовочном файле?
using namespace std;

// review notes: Где бы логичнее проивести данное объявление?
class SmartStringData{
private:
    short refcount;
public:
    string data;
    SmartStringData(){refcount=1;}
    // review notes: Почему плохо использовать имена, начинающиеся с подчеркивания?
    SmartStringData(string _data){data=_data;refcount=1;}
    void incRef(){refcount++;}
    void decRef(){--refcount; if(refcount==0) delete this;}
    short RefNumber(){return refcount;}
};


class SmartString{
public:
    // revie notes: Как вы оцениваете данное объвление с точки зрения инкапсуляции?
    SmartStringData* shared;
    SmartString(){shared = new SmartStringData();}
    // revie notes: А почему i передается по значению?
    SmartString(string i){shared = new SmartStringData(i);}
    SmartString(const SmartString& data){shared = data.shared; shared->incRef();}
    // revie notes: Зачем ch преводится к своему же типу? Как грамотнее переписать данный конструктор?
    SmartString(const char *ch){string s = (const char*) ch; shared = new SmartStringData(s);}  //SmartString a = "123";

    // revie notes: Представте, что вы заказчик продукта. Были ли бы вы довольны, получив программу, которая не компилируется?
    const SmartString& operator=(const SmartString& data){
        if(shared!=data.shared){              //SmartString a=b
            shared->decRef();
            shared = data.shared;
            shared->incRef();
        }
    }

    // revie notes: Когда быдет вызываться данный оператор? Верен ли пример в комментарии?
    // revie notes: Все ли в порядке в данноем методе?
    const SmartString& operator=(const string& data){if(shared->data!=data){                   //string a="123"; SmartString b = a;
            shared->decRef();
            shared = new SmartStringData(data);
            shared->incRef();}
                                                    }

    ~SmartString(){shared->decRef();}
    string toString(){return shared->data;}
};

#endif // SMARTSTRING_H
