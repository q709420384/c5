//
// Created by sanyie on 18-6-22.
//

#ifndef STRATEGY_CONTEXT_H
#define STRATEGY_CONTEXT_H

class Strategy;

class Context
{
public:
    Context(Strategy* stg);
    ~Context();
    void DoAction();

protected:
    Strategy* _stg;
};

#endif //STRATEGY_CONTEXT_H
