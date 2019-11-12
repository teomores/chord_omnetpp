/*
 * SuccessorList.h
 *
 *  Created on: 30 ago 2019
 *      Author: Albo
 */

#include <omnetpp.h>
#include <string.h>
#include <string>
#include "ChordMessages_m.h"
class Node;

class NotifyResponse;

using namespace std;
using namespace omnetpp;

#ifndef SUCCESSORLIST_H_INCLUDED__
#define SUCCESSORLIST_H_INCLUDED__


class SuccessorList: public cSimpleModule {

protected:
    std::vector<pair<pair<string, bool>,Node*>> successorMap; // il bool dice se è una new entry
    int successorListSize;
    Node* thisNode;

public:
    void initializeList(int size, Node* owner, bool debug = true);
    int getSize();
    bool isEmpty();
    Node* getSuccessor(int pos = 0);
    void addSuccessor(Node* successor, bool resize = true, bool debug = true);
    void updateList(NotifyResponse* notifyResponse);
    void removeOldSuccessors();
    void print();
    bool handleFailedNode(string failed);
    void sortList();

};

#endif
