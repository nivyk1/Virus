#include "../include/Session.h"
#include "../include/Graph.h"
#include "../include/Agent.h"
//class Agent;
//class Graph;
using namespace std;
using json = nlohmann::json;

//TODO: Check moves Operators
Session::Session(const string &path) : g(Graph()),treeType(Root),agents(vector<Agent *>()),infected_Queue(),currCycle(0){

    fstream i(path);
    json j;
    i >> j;
    g = Graph(j["graph"]);
    if (j["tree"] == "C")
        treeType = Cycle;
    else if (j["tree"] == "M")
        treeType = MaxRank;
    else// if(j["tree"]=="R")
        treeType = Root;
    for (unsigned int k = 0; k < j["agents"].size(); k++) {

        if (j["agents"][k][0] == "V") {
            addAgent(Virus(j["agents"][k][1]))

            enqueueInfected(j["agents"][k][1]);
        } else
        {
            agents.push_back(new ContactTracer());
        }
    }
}



Session::Session() : g(Graph()),treeType(Root),agents(vector<Agent *>()),infected_Queue(),currCycle(0){

}


Session::~Session() {
    delete &g;
    for (auto it = agents.begin(); it != agents.end(); it++) {
        delete *it;
    }

}

Session::Session(const Session &session): g(session.g),treeType(session.treeType),agents(vector<Agent *>()),infected_Queue(session.infected_Queue),currCycle(session.currCycle) {

    for (unsigned int i = 0; i < session.agents.size(); ++i) {
        agents.push_back(session.agents[i]->Clone());
    }

    /*for(auto it = session.agents.begin(); it!=session.agents.end() ; it++)
    {
        agents.push_back(new Agent(*(it)));
    }*/

}

Session &Session::operator=(const Session &session) {

    for (unsigned int i = 0; i < agents.size(); i++) {
        delete agents[i];
    }
    agents.clear();

    // TODO: may be huge problem

    //return ;
    g = session.g;
    treeType = session.treeType;
    for (unsigned int i = 0; i < session.agents.size(); i++) {
        agents.push_back(session.agents[i]->Clone());
    }
    return *this;
}

//move constructor
Session::Session(Session &&session): g(session.g),treeType(session.treeType),agents(session.agents),infected_Queue(session.infected_Queue),currCycle(session.currCycle)
{


    session.agents.clear();



   // session.infected_Queue= nullptr;
   // session.agents= nullptr;

}

//move assignment operator
Session &Session::operator=(Session &&session) {

    for (unsigned int i = 0; i < agents.size(); i++) {
        delete agents[i];
    }
    agents.clear();
    g = session.g;
    treeType = session.treeType;
    agents=session.agents;
    infected_Queue=session.infected_Queue;
    currCycle=session.currCycle;

    return *this;

}

void Session::simulate()
{
    int currentSize;
    while(Terminator()!=true)
    {
        currentSize = agents.size();
        for (int j = 0; j <currentSize ; ++j)
        {
         agents[j]->act();
        }
        currCycle++;
    }
    json k;
    k["graph"]=get_Graph().getEdges();
    k["infected"] = get_Graph().AllInfectedNodes();
    ofstream i("../output.json");
    i<<k<<endl;

}



TreeType Session::get_Treetype() {
    return treeType;
}

vector<Agent *> &Session::get_Agents() {
    return agents;
}

void Session::  addAgent(const Agent &agent) {

    this->agents.push_back(agent.Clone());

}

/*void Session::setGraph(const Graph &graph) {
    if (&g != &graph)
        g = graph;
}*/

void Session::enqueueInfected(int x) {
    infected_Queue.push(x);
}

int Session::dequeueInfected() {

    int x = infected_Queue.front();
    infected_Queue.pop();
    return x;

}

TreeType Session::getTreeType() const {
    return treeType;
}

int Session::get_currCycle() const {
    return currCycle;
}

bool Session::Terminator()
{

    return g.IsTerminated();
}

Graph Session::get_Graph() {
    return this->g;
}











