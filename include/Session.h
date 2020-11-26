#ifndef SESSION_H_
#define SESSION_H_

#include "../include/Graph.h"
#include "../include/Agent.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "json.hpp"
#include <string>
#include <queue>


class Agent;

using namespace std;
//class Graph;
//class Agent;


enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class Session{
public:
    Session(const std::string& path);
    Session();
    //destructor
    virtual ~Session();
    // copy constructor
    Session(const Session &session);
    //copy operator=
    Session& operator=(const Session &session);
    //move constructor
    Session(Session && session);
    //move assignment operator
    Session& operator=(Session &&session);
    //Session* const Clone() ;
    void simulate();
    void addAgent(const Agent& agent);
    //void setGraph(const Graph& graph);
    void enqueueInfected(int x);
    int dequeueInfected();
    bool Terminator();
    TreeType getTreeType() const;


    //Getters
    Graph get_Graph();
    TreeType get_Treetype();
    vector<Agent*> &get_Agents();
    int get_currCycle() const;




private:
    Graph g;
    TreeType treeType;
    vector<Agent*> agents;
    queue<int> infected_Queue;
    int currCycle;
};

#endif
