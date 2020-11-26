#include "../include/Agent.h"
#include "../include/Session.h"
#include "../include/Tree.h"
//TODO: Operator= Here need to check!~!




Agent::Agent() {

}

Agent::~Agent() {

}


ContactTracer::ContactTracer() {
}


Agent *ContactTracer::Clone() const {
    return new ContactTracer(*this);
}

void ContactTracer::act(Session &session) {
    int dequedNode =session.dequeueInfected();
    Tree *root = session.get_Graph().BFS(session, dequedNode);
    int IsolateIt = root->traceTree();
    session.get_Graph().IsolateVertice(IsolateIt);
}


Agent *Virus::Clone() const {
    return new Virus(*this);
}


Virus::Virus(int nodeInd) :nodeInd(nodeInd){
}

void Virus::act(Session &session) {
    if (session.get_Graph().GetNodeStatus(nodeInd) == exposed)
        session.get_Graph().SetNodeStatus(nodeInd, infected);
    int othernode = session.get_Graph().GetNodeToInfect(nodeInd);

    if (othernode != -1) {
        session.get_Graph().SetNodeStatus(othernode, exposed);
        session.enqueueInfected(othernode);
        session.get_Agents().push_back(new Virus(othernode));
    }

}
