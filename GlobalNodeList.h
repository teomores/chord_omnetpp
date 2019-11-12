/*
 * GlobalNodeList.h
 *
 *  Created on: 6 set 2019
 *      Author: Albo
 */

#include <omnetpp.h>
#include <iostream>
#include <map>
#include <set>
#include <vector>

class Node;

using namespace std;
using namespace omnetpp;

#ifndef GLOBALNODELIST_H_INCLUDED__
#define GLOBALNODELIST_H_INCLUDED__

class GlobalNodeList : public cSimpleModule
{
public:
    string getBootstrapNode();

    const std::map<std::string, std::string>& getNodeMap() const {
        return nodeMap;
    }

    void setNodeMap(const std::map<std::string, std::string>& nodeMap) {
        this->nodeMap = nodeMap;
    }

    const std::set<std::string>& getSetNode() const {
        return setNode;
    }

    void setSetNode(const std::set<std::string>& setNode) {
        this->setNode = setNode;
    }

    int getNumberOfNodes() const {
        return numberOfNodes;
    }

    void setNumberOfNodes(int numberOfNodes) {
        this->numberOfNodes = numberOfNodes;
    }
    void addBooststrapNode(Node* boot);
    void printList();
    bool willFail(string key);

private:
    std::map<std::string,std::string> nodeMap; // per ora non usata
    std::set<std::string> setNode; // lista di tutti i nodi nella rete
    std::vector<std::string> boostrapList; // lista aggiornata dei nodi che fanno parte di chord
    int numberOfNodes;
    std::vector<std::string> failedNodes;

protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void pickFailed();





};

#endif
