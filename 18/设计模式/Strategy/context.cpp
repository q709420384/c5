//
// Created by sanyie on 18-6-22.
//

#include "context.h"
#include "strategy.h"
#include <iostream>
using namespace std;

Context::Context(Strategy* stg)
{
    _stg = stg;
}

Context::~Context()
{
    if(!_stg)
        delete _stg;
}

void Context::DoAction()
{
    _stg->AlgrithmInterface();
}