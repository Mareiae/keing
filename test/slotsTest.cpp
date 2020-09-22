#include <iostream>
#include "../keing/Slots.hpp"


//模拟进度条类
class scrollBar
{
private:
    int value;

public:
    Signal<int> valueChanged; //信号和信号参数类型 

public:
    scrollBar():value(0){} //初始化value的值

    void setValue(int val)
    {
        if(val != value)
        {
            value = val;
            emit valueChanged(value); //如果值改变 触发信号
        }
    }
};


//模拟标签类
class label
{
private:
    int text;

public:
    label(int m_text):text(m_text){}

    void changeText(int m_text)
    {
        text = m_text;
        std::cout<<"now text : " << text << std::endl;
    }

};



int main()
{
    //实例化两个类
    scrollBar* scroll = new scrollBar;
    label*  lab = new label(50);

    //连接信号和槽
    connect(scroll, valuechanged, lab, &label::changeText);

    //调用setValue()
    scroll->setValue(500);
    scroll->setValue(1000);
    scroll->setValue(0);

    delete scroll;
    delete lab;



    return 0;
}