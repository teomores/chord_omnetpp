/*
 * FingerTable.h
 *
 *  Created on: 30 ago 2019
 *      Author: Albo
 */
#include <deque>
#include <iostream>
#include <utility>
#include <omnetpp.h>
class Node;


using namespace omnetpp;
using namespace std;
     // forward delle classi evitare gli include

//typedef pair<std::string, Node*> Successor;
//typedef pair<Node*, Successor> FingerEntry;
typedef pair<string, Node*> FingerEntry;



#ifndef FINGERTABLE_H_INCLUDED__
#define FINGERTABLE_H_INCLUDED__

class FingerTable: public cSimpleModule {

protected:
    const int maxSize = 160; /**< maximum size of the finger table */
    Node* owner;

    deque<FingerEntry> fingerTable; /**< the finger table vector */ //TODO FIX

public:
    int getSize();
    Node* getFinger(int pos);
    void setFinger(int pos, Node* node);
    void handleFailedNode();
    void initializeFingerTable(Node* owner, bool debug);
    void printTable();
    void removeFinger(uint32_t pos);
    bool isUnspecified(Node* n);
    bool handleFailedNode(string failed);
    bool updateFinger(uint32_t pos, Node* node, simtime_t rtt);
};

#endif
