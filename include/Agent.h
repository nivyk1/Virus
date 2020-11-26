#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
//#include <iostream>
#include "../include/Session.h"
//class session;

class Agent {
public:

    Agent();
    virtual ~Agent();
    virtual Agent *Clone() const = 0;// const;
    virtual void act(Session &session) = 0;

};

class ContactTracer: public Agent {
public:
    ContactTracer();
    virtual Agent *Clone() const;
    virtual void act(Session &session);
};


class Virus: public Agent {
public:
    Virus(int nodeInd);
    virtual Agent *Clone() const;
    virtual void act(Session &session);

private:
    const int nodeInd;
};

#endif
