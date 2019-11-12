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
#include <omnetpp.h>
#include <string.h>
#include <string>
#include "string"
#include <utility>
#include <cctype>
#include <cstddef>
#include <cstring>
#include<iostream>
#include<iterator> // for iterators
#include<vector> // for vectors

#include "SuccessorList.h"

#include "ChordMessages_m.h"
#include "Node.h"
#include "utils.h"
//#define COMPILETIME_LOGLEVEL LOGLEVEL_OFF

using namespace omnetpp;
using namespace std;

// The module class needs to be registered with OMNeT++
Define_Module(SuccessorList);

void SuccessorList::initializeList(int size, Node* owner, bool debug)
{
    successorMap.clear();

    successorListSize = size;
    this->thisNode = owner;
    if (debug)
        EV_DEBUG << "Initializing SuccessorList for: " << thisNode->getOverlayKey() <<endl ;

    addSuccessor(thisNode, true, debug);
}

int SuccessorList::getSize()
{
    return successorMap.size();
}


void SuccessorList::addSuccessor(Node* successor, bool resize, bool debug)
{
    /*
    int posInsert = -1; // posizione a cui inserire il successor
    EV << "Adding to successor list " <<  successor->getOverlayKey() << endl;
    EV << "Successor list before add: " << endl;
    for (unsigned int i=0; i<successorMap.size(); i++)
        EV << successorMap[i].first.first << " , " << successorMap[i].second << endl;

    // controlla per ogni coppia di chiavi successive se quella da inserire sta nel mezzo
    if(successorMap.size() != 0){
        if(this->isEmpty()){
            successorMap.pop_back();
            EV << "Since the list contains only our key, we pop it And we insert new key:"<< successor->getOverlayKey() << endl;

            successorMap.insert(successorMap.begin(),make_pair(make_pair(successor->getOverlayKey(),true), successor)); // mette newEntry a true
        }else{
            if((successor->getOverlayKey()!=this->thisNode->getOverlayKey())){
                bool flag = false;
                for(int i = 0; i < this->getSize(); i++){
                    if (strcmp(successorMap[i].first.first.c_str(),successor->getOverlayKey().c_str())==0){
                        flag = true;
                    }
                }
                if(!flag){
                    if(successorMap.size()==1){
                        if(Utils::isBetween(successor->getOverlayKey(), thisNode->getOverlayKey(),successorMap[0].first.first)){
                            EV << "Successor: " << successor->getOverlayKey() << " è compreso tra " << thisNode->getOverlayKey() << " e " << successorMap[0].first.first << endl;
                            successorMap.insert(successorMap.begin(),make_pair(make_pair(successor->getOverlayKey(),true), successor));
                        } else {
                            EV<< "Successor: " << successor->getOverlayKey() << " non è compreso tra " << thisNode->getOverlayKey() << " e " << successorMap[0].first.first << endl;
                            successorMap.insert(successorMap.begin()+1,make_pair(make_pair(successor->getOverlayKey(),true), successor));
                        }
                    } else {
                        if (Utils::isBetween(successor->getOverlayKey(), this->thisNode->getOverlayKey(),successorMap[0].first.first)){
                            posInsert = 0;
                        } else {
                            for(unsigned int i=0; i<successorMap.size()-1; i++){
                                if(Utils::isBetween(successor->getOverlayKey(), successorMap[i].first.first, successorMap[i+1].first.first))
                                    EV << successor->getOverlayKey() << " is btw " << successorMap[i].first.first << " and " << successorMap[i+1].first.first<< endl;
                                posInsert = i+1;
                            }}
                        // controlla se arriva alla fine del loop senza cambiare posInsert
                        if(posInsert==-1)
                            posInsert=successorMap.size(); // nel caso, va pushato alla fine

                        EV << "Pos Insert:" << posInsert << endl;
                        successorMap.insert(successorMap.begin()+posInsert,make_pair(make_pair(successor->getOverlayKey(),true), successor));
                        print();
                    }

                }
            }

        }
    }
    else {
        if (debug) EV_DEBUG << "No key in the successorList yet. Inserting it in position:" << posInsert+1 << endl;
        successorMap.insert(successorMap.begin(),make_pair(make_pair(successor->getOverlayKey(),true), successor));
    }

    if (debug) EV_DEBUG << "New successorList: " << endl;
    for (unsigned int i=0; i<successorMap.size(); i++)
        if (debug) EV_DEBUG << successorMap[i].first.first <<endl; // " , " << successorMap[i].second << "\t";

    // faccio resize togliendo l'ultimo elemento se eccede la lunghezza massima consentita
    if ((resize == true) && (successorMap.size() > successorListSize)) {
        successorMap.pop_back();
    }
     */
    EV_DEBUG << "Adding to successor list " <<  successor->getOverlayKey() << endl;
    EV_DEBUG << "Successor list before add: " << endl;
    //print();
    bool flag = false;
    // controllo se il nodo da inserire è già nella successor list
    for(int i = 0; i < this->getSize(); i++){
        if (strcmp(successorMap[i].first.first.c_str(),successor->getOverlayKey().c_str())==0){
            EV_DEBUG << successorMap[i].first.first.c_str() << " == " << successor->getOverlayKey().c_str() << endl;
            flag = true;
        } else {
            EV_DEBUG << successorMap[i].first.first.c_str() << " != " << successor->getOverlayKey().c_str() << endl;
        }
    }
    // se non è nella successor list inizia la procedura di inserimento
    if(!flag){
        // non ci sono duplicati
        if(successorMap.size() == 0){
            // se la lista è vuota, semplicemente lo pusho
            EV_DEBUG << "Lista vuota, metto in testa" << endl;
            successorMap.insert(successorMap.begin(),make_pair(make_pair(successor->getOverlayKey(),true), successor));
        } else {
            // caso EMPTY: lista con solo il nodo stesso
            if(strcmp(thisNode->getOverlayKey().c_str(),successor->getOverlayKey().c_str())!=0){
                if(this->isEmpty()){
                    // in questo caso rimuovo il nodo e inserisco quello nuovo
                    successorMap.pop_back();
                    EV_DEBUG << "Since the list contains only our key, we pop it And we insert new key:"<< successor->getOverlayKey() << endl;
                    successorMap.insert(successorMap.begin(),make_pair(make_pair(successor->getOverlayKey(),true), successor));
                } else {
                    // nel caso in cui non sia empty, INSERIMENTO NORMALE
                    if(Utils::isBetween(successor->getOverlayKey(), thisNode->getOverlayKey(),successorMap[0].first.first)){
                        // CASO 1: inserimento in TESTA
                        EV_DEBUG << "Successor: " << successor->getOverlayKey() << " è compreso tra " << thisNode->getOverlayKey() << " e " << successorMap[0].first.first << endl;
                        successorMap.insert(successorMap.begin(),make_pair(make_pair(successor->getOverlayKey(),true), successor));
                    } else {
                        // CASO 2: inserimento NORMALE
                        bool posInsertFound = false;
                        for(unsigned int i=0; i<successorMap.size()-1; i++){
                            if(Utils::isBetween(successor->getOverlayKey(), successorMap[i].first.first, successorMap[i+1].first.first)){
                                EV_DEBUG << successor->getOverlayKey() << " is btw " << successorMap[i].first.first << " and " << successorMap[i+1].first.first<< endl;
                                EV_DEBUG << "Inserisco "  << successor->getOverlayKey() << " in posizione " << i+1 << endl;
                                posInsertFound = true;
                                successorMap.insert(successorMap.begin()+i+1,make_pair(make_pair(successor->getOverlayKey(),true), successor));
                            }
                        }
                        if(!posInsertFound){
                            // CASO 3: inserisco in fondo
                            EV_DEBUG << "Non ho trovato intervalli, inserisco "  << successor->getOverlayKey() << " in posizione " << successorMap.size()-1 << endl;
                            successorMap.insert(successorMap.begin()+successorMap.size(),make_pair(make_pair(successor->getOverlayKey(),true), successor));
                        }
                    }
                }
            }
        }
    }
    while (successorMap.size() > successorListSize) {
        successorMap.pop_back();
    }
    EV_DEBUG << "AFTER ADD" << endl;
    //print();
}

bool SuccessorList::isEmpty()
{
    if (successorMap.size() == 1 && getSuccessor()->getOverlayKey() == thisNode->getOverlayKey())
        return true;
    else
        return false;
}

Node* SuccessorList::getSuccessor(int pos)
{

    if (pos > successorMap.size()) {
        error("Index out of bound (ChordSuccessorList, getSuccessor())");
    }
    return successorMap[pos].second;

    // TODO: non so se va fatto, c'era in oversim, nodo vuoto se non ha la SuccessorList in pratica ?
}

void SuccessorList::updateList(NotifyResponse* notifyResponse)

{
    EV_DEBUG << "UPDATING SUCCESSORS for node " << thisNode->getOverlayKey() << " WITH THESE SUCCESSORS:" << endl;
    int sucNum = notifyResponse->getSuccessorNum();
    for (int k = 0; ((k < sucNum) && (k < (successorListSize))); k++) {
        EV_DEBUG << notifyResponse->getSuccessorNode(k)<< endl;
    }
    EV_DEBUG << "BEFORE:"<< endl;
    //print();

    Node* sender =  check_and_cast<Node*>(notifyResponse->getSenderModule());
    addSuccessor(sender, false, true);

    for (int k = 0; ((k < sucNum)
            && (k < (successorListSize))); k++) {
        string successor = notifyResponse->getSuccessorNode(k);
        EV_DEBUG << "Successor " << k << ": " << successor << endl;
        Node* our = check_and_cast<Node*>(this->getParentModule()->getSubmodule("node"));

        if (Utils::isBetweenLR(successor, our->getOverlayKey(), sender->getOverlayKey()))
            continue;
        Node* succNode = check_and_cast<Node*>(Utils::getModule(successor, true, false));
        addSuccessor(succNode, true, true);


    }


    EV_DEBUG << "FINAL LIST AFTER UPDATE:" << endl;
    //print();
    //sortList();
    //removeOldSuccessors();
    assert(!isEmpty());
    //this->print();
}

void SuccessorList::print(){
    EV << "SUCCESSORLIST FOR : "<< thisNode->getOverlayKey() << endl;
    for (unsigned int i=0; i<successorMap.size(); i++)
        EV << successorMap[i].first.first << " , " << successorMap[i].second << endl;

}

void SuccessorList::removeOldSuccessors(){
    for(unsigned int i=0; i<successorMap.size(); i++){
        if (successorMap[i].first.second == false) {
            successorMap.erase(successorMap.begin() + i);
        } else {
            successorMap[i].first.second = false;
        }
    }

    int i = successorMap.size();
    i--;
    while (successorMap.size() > successorListSize) {
        successorMap.erase(successorMap.begin() + i--);
    }

    if (getSize() == 0)
        addSuccessor(thisNode, false);
}

bool SuccessorList::handleFailedNode(string failed)
{

    assert(failed != thisNode->getIp());

    for(unsigned int i=0; i<successorMap.size(); i++){
        if (strcmp(successorMap[i].second->getIp().c_str(),failed.c_str())==0){
            successorMap.erase(successorMap.begin() + i);
            //throw cRuntimeError("ping");
            if (getSize() == 0)
                addSuccessor(thisNode);
            return true;
        }
    }
    return false;
}

void SuccessorList::sortList() {
    /*Node * real_successor = successorMap.begin();
    sort(successorMap.begin(), successorMap.end(),Utils::isSmallerComparator);
    int cur_size = successorMap.size();
    std::vector<std::pair<std::pair<string, bool>,Node*>> secondMap;
    for(unsigned int i=0; i<cur_size; i++){
        if (Utils::isSmaller(successorMap[0].first.first, this->getSuccessor())) {
           secondMap.push_back(make_pair(make_pair(successorMap[0].first.first, successorMap[0].first.second), successorMap[0].second));
           successorMap.erase(successorMap.begin());
        }

    }
    for(unsigned int i=0; i<secondMap.size()-1; i++){
        successorMap.push_back(secondMap[i]);
    }
    this->print();*/
}


