//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "FingerTable.h"

#include <omnetpp/cexception.h>
#include <omnetpp/clog.h>
#include <omnetpp/cobjectfactory.h>
#include <omnetpp/cownedobject.h>
#include <omnetpp/regmacros.h>
#include <stdint.h>
#include <string>
#include "utils.h"
#include "Node.h"
#define COMPILETIME_LOGLEVEL LOGLEVEL_INFO


// TODO serve a generare le chiavi .start di ogni finger, queste rimarranno le stesse per ogni

Define_Module(FingerTable);

int FingerTable::getSize() {
    return this->fingerTable.size();
}

void FingerTable::initializeFingerTable(Node* owner, bool debug)
{
    fingerTable.clear();
    this->owner = owner;
    if(debug) EV_DEBUG << "Initializing fingerTable for: " << owner->getOverlayKey() <<" \n" ;


}

void FingerTable::printTable(){
    EV << "FINGERTABLE OF: "<<this->owner->getOverlayKey() << endl;
    for ( int i=0; i< this->fingerTable.size(); i++){
        if(!(this->fingerTable[i].first.empty())){
            EV << i << "|| " << this->fingerTable[i].first << " | " << this->fingerTable[i].second->getOverlayKey() << " ||\n";

        }
    }


}

void FingerTable::setFinger(int pos, Node* node)
{
    string start = Utils::getKeyInModule(pos, node->getOverlayKey(), false);
    pair<string, Node*> entry = make_pair(start, node);
    if (pos >= maxSize) {
        throw new cRuntimeError("ChordFingerTable::setFinger(): "
                "Index out of bound");
    }
    int p = maxSize - pos - 1;
    while (fingerTable.size() <= p) {
        fingerTable.push_back(FingerEntry("",Node::UNSPECIFIED_NODE));
    }

    fingerTable[p] = entry;

}



Node* FingerTable::getFinger(int pos)
{
    if (pos >= maxSize) {
        throw new cRuntimeError("ChordFingerTable::getFinger(): "
                "Index out of bound");
    }

    int p = maxSize - pos - 1;
    if (p >= fingerTable.size()) {
        return this->owner->successorlist->getSuccessor();
    }
    while (!fingerTable[p].first.empty() &&
            (p < (fingerTable.size() - 1))) {
        ++p;
    }
    if (isUnspecified(fingerTable[p].second))
        return this->owner->successorlist->getSuccessor();
    return fingerTable[p].second;
}

void FingerTable::removeFinger(uint32_t pos)
{
    if (pos >= maxSize) {
        throw new cRuntimeError("ChordFingerTable::removeFinger(): "
                "Index out of bound");
    }

    uint32_t p = maxSize - pos - 1;

    if (p >= fingerTable.size()) {
        return;
    } else if (p == (fingerTable.size() - 1)) {
        fingerTable.pop_back();
    } else {
        //Successors tempSuccessors;
        //fingerTable[p] = FingerEntry(NodeHandle::UNSPECIFIED_NODE, tempSuccessors);
        fingerTable[p] = FingerEntry("",Node::UNSPECIFIED_NODE);
    }
}

bool FingerTable::isUnspecified(Node* n){
    if(n == Node::UNSPECIFIED_NODE)
        return true;
    else
        return false;
}

bool FingerTable::handleFailedNode(string failed)
{
    bool ret = false;

    for (int p = fingerTable.size() - 1; p >= 0; p--) {
        if (!isUnspecified(fingerTable[p].second) &&
                strcmp(failed.c_str(),fingerTable[p].second->getIp().c_str())==0) {
            fingerTable[p].first = "";
            fingerTable[p].second = Node::UNSPECIFIED_NODE;
            ret = true;
        }
    }

    return ret;
}

bool FingerTable::updateFinger(uint32_t pos, Node* node, simtime_t rtt)
{
    if (rtt < 0)
        return false;

    if (pos >= maxSize) {
        throw new cRuntimeError("ChordFingerTable::updateFinger(): "
                "Index out of bound");
    }

    uint32_t p = maxSize - pos - 1;

    while (fingerTable.size() <= p) {
        fingerTable.push_back(FingerEntry("",Node::UNSPECIFIED_NODE));
    }

    if (fingerTable[p].second->getOverlayKey() == node->getOverlayKey()){
        fingerTable[p] = FingerEntry(node->getOverlayKey(), node); // lui toglie e poi rimette, a noi basta cambiare
        return true;
    } else {
        return false;
    }


}

