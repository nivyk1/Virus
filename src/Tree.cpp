#include "../include/Tree.h"


//class Session;

//constructor
Tree::Tree(int rootLabel) : node(rootLabel),children(vector<Tree *>()) ,depth(0) {
    //vector<Tree*> children;
}

Tree::~Tree() {
    /*for (auto it = begin(children); it!=end(children);++it)
    {
        delete *it;
    }*/
    {
        for (unsigned int i = 0; i < children.size(); ++i) {
            if (children[i] != nullptr)
                delete children[i];
        }
    }
    //children.clear();
}

// copy constructor
Tree::Tree(const Tree &tree) : node(tree.node),children(vector<Tree *>()), depth(tree.depth) {

    for (unsigned int i = 0; i < children.size(); ++i) {
        children.push_back((tree.children[i])->Clone());
    }

}


//copy operator=
Tree &Tree::operator=(const Tree &tree) {
    this->node = tree.node;
    this->depth = tree.depth;
    for (unsigned int i = 0; i < tree.children.size(); ++i) {
        delete children[i];
    }
    // maybe need to clear stack
    for (unsigned int i = 0; i < tree.children.size(); ++i) {
        this->children.push_back(tree.children[i]->Clone());
    }
    return *this;
}

//move constructor
Tree::Tree(Tree &&tree) : node(tree.node),children(vector<Tree *>()), depth(tree.depth) {
    for (unsigned int i = 0; i < children.size(); i++) {
        delete children[i];
    }
    children.clear();
    children=tree.children;
    tree.children.clear();
}

//move assignment operator
Tree &Tree::operator=(const Tree &&tree) {
    if (this != &tree) {
        this->node = tree.node;
        this->depth = tree.depth;
        for (unsigned int i = 0; i < children.size(); ++i) {
            delete children[i];

        }
        children.clear();
       children=tree.children;

    }
    return *this;
}

void Tree::addChild(const Tree &child) {
    children.push_back(child.Clone());
}

/*
Tree* Tree::createTree(const Session &session, int rootLabel)
{
    session.
    Tree* root= new
    return nullptr;
}*/



int Tree::get_node() const {
    return this->node;
}

int Tree::get_depth() const {
    return this->depth;
}

const vector<Tree *> &Tree::get_childrens() const {
    return children;
}

void Tree::set_node(int n1) {
    this->node = n1;
}

void Tree::set_depth(int d) {
    this->depth = d;
}

void Tree::set_childrens(vector<Tree *> subG) {
    this->children = subG;
}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    Tree *x;
    if (session.getTreeType() == Cycle) {
        x = new CycleTree(rootLabel, session.get_currCycle());
    } else if (session.getTreeType() == MaxRank) {
        x = new MaxRankTree(rootLabel);
    } else if (session.getTreeType() == Root) {
        x = new RootTree(rootLabel);
    }
}


//CycleTree
//CycleTree constructor
CycleTree::CycleTree(int rootLabel, int currCycle) :
        currCycle(currCycle), Tree(rootLabel) {

}

Tree *CycleTree::Clone() const {
    return new CycleTree(*this);
}


int CycleTree::traceTree() {
    vector<Tree *> t;
    Tree *tr;

    int c = currCycle;
    if (c == 1) {
        return this->get_node();
    } else
        while (t[0] != nullptr && c > 0) {
            c--;
            t = this->get_childrens();
            tr = t[0];

        }
    return tr->get_node();
}


//MaxRankTree
//MaxRankTree Constructor
MaxRankTree::MaxRankTree(int rootLabel) :
        Tree(rootLabel) {

}


int MaxRankTree::traceTree() {
    return (FindMaxRank(*this, *this).get_node());

}


const Tree &MaxRankTree::CompareRank(Tree &MaxRank, const Tree &Curr) {
    if (MaxRank.get_childrens().size() < Curr.get_childrens().size()) {
        return Curr;
    } else {
        if (MaxRank.get_childrens().size() == Curr.get_childrens().size()) {
            if (MaxRank.get_depth() > Curr.get_depth()) {
                return Curr;
            } else if (MaxRank.get_depth() == Curr.get_depth()) {
                if (MaxRank.get_node() > Curr.get_node()) {
                    return Curr;
                }

            }
        }
    }
    return MaxRank;

}

const Tree &MaxRankTree::FindMaxRank(Tree &MaxRank, Tree &Curr) {

    if (Curr.get_childrens().size() == 0) {
        return Curr;
    }

    for (Tree *x : Curr.get_childrens()) {
        const Tree &i = FindMaxRank(MaxRank, *x);
        MaxRank = CompareRank(MaxRank, i);
    }
    MaxRank = CompareRank(MaxRank, Curr);
    return MaxRank;

}

Tree *MaxRankTree::Clone() const {
    return new MaxRankTree(*this);
}




//RootTree
//RootTree Constructor
RootTree::RootTree(int rootLabel) :
        Tree(rootLabel) {

}

int RootTree::traceTree() {

    return this->get_node();

}

Tree *RootTree::Clone() const {
    return new RootTree(*this);
}













