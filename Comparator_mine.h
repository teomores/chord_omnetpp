/*
 * Comparator.h
 *
 *  Created on: 4 set 2019
 *      Author: Albo
 */

#include <omnetpp.h>
#include "string"
#include <string.h>

#include "sha1.h"


using namespace omnetpp;
using namespace std;

/*
 * Questo header si preoccupa di fare tutta la logica per le somme e i confronti di chiavi di chord
 * lista di cose da fare:
 * - funzione somma di stringhe con logica modulo
 * - avrà un riferimento a sha1
 * -
 * */

static string getsum(string str1, string str2){
    if ( str1.size() < str2.size()){
        while(str1.size() < str2.size() ){
            str1 = "0" + str1;
        }
    }else if ( str2.size() < str1.size()){

        while(str2.size() < str1.size() ){
            str2 = "0" + str2;
        }
    }
    return str1;
}

static void getHex(int integer, int pow){

}

static string isGreater(string str1, string str2){
    std::string thisKey = str1;
    std::string key = str2;

    std::string thisHex[5];
    thisHex[0] = thisKey.substr(0,7);
    thisHex[1] = thisKey.substr(8,15);
    thisHex[2] = thisKey.substr(16,23);
    thisHex[3] = thisKey.substr(24,31);
    thisHex[4] = thisKey.substr(32,39);

    std::string hex[5];
    hex[0] = key.substr(0,7);
    hex[1] = key.substr(8,15);
    hex[2] = key.substr(16,23);
    hex[3] = key.substr(24,31);
    hex[4] = key.substr(32,39);

    assert (thisKey.size() == key.size());
    assert (thisKey != key);
    for(int i=0; i<5;i++){
        if (stoll(thisHex[i], 0, 16) > stoll(hex[i], 0, 16)) {
            EV << "this key: " << thisHex << "is bigger than: " << hex << " \n";
            return str1;
        }else if (stoll(thisHex[i], 0, 16) < stoll(hex[i], 0, 16)){
            EV << "key: " << thisHex << "is lower than: " << hex << " \n";
            return str1;
        }

    }return str1;
}


