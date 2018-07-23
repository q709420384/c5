//
// Created by sanyie on 18-6-22.
//

#ifndef STRATEGY_STRATEGY_H
#define STRATEGY_STRATEGY_H

class Strategy
{
public:
    Strategy();
    virtual ~Strategy();
    virtual void AlgrithmInterface() = 0;

protected:
private:
};

class ConcreteStrategyA : public Strategy
{
public:
    ConcreteStrategyA();
    virtual ~ConcreteStrategyA();
    void AlgrithmInterface();

protected:
private:
};

class ConcreteStrategyB : public Strategy
{
public:
    ConcreteStrategyB();
    virtual ~ConcreteStrategyB();
    void AlgrithmInterface();

protected:
private:
};

#endif //STRATEGY_STRATEGY_H
