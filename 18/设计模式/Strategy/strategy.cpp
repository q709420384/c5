//
// Created by sanyie on 18-6-22.
//

#include "strategy.h"
#include <iostream>
using namespace std;

Strategy::Strategy()
{

}

Strategy::~Strategy()
{
    cout << "~Strategy....." << endl;
}


ConcreteStrategyA::ConcreteStrategyA()
{
    cout << "test ConcreteStrategyA......" << endl;
}

ConcreteStrategyA::~ConcreteStrategyA()
{
    cout << "~test ConcreteStrategyA......" << endl;
}

void ConcreteStrategyA::AlgrithmInterface() {
    cout << "GUA GUA" << endl;
}

ConcreteStrategyB::ConcreteStrategyB()
{
    cout << "test ConcreteStrategyB......" << endl;
}

ConcreteStrategyB::~ConcreteStrategyB()
{
    cout << "~test ConcreteStrategyB......" << endl;
}

void ConcreteStrategyB::AlgrithmInterface()
{
    cout << "test ConcreteStrategyB......" << endl;
}