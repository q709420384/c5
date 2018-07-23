#include "context.h"
#include "strategy.h"
#include <iostream>
using namespace std;

int main()
{
    Strategy* ps = new ConcreteStrategyA();

    Context* pc = new Context(ps);

    pc->DoAction();

    if(pc != NULL)
    {
        delete pc;
    }
    return 0;

}