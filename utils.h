/*
 * utils.h
 *
 *  Created on: 5 set 2019
 *      Author: Albo
 */


#include <_ctype.h>
#include <omnetpp/cexception.h>
#include <omnetpp/clog.h>
#include <omnetpp/cpar.h>
#include <omnetpp/csimulation.h>
#include <omnetpp/platdep/platdefs.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include "BaseConverter.h"

#include "/usr/local/Cellar/gmp/6.1.2_2/include/gmp.h"
//#define COMPILETIME_LOGLEVEL LOGLEVEL_OFF
class Node;

using namespace std;

using namespace omnetpp;

#ifndef UTILS_H_INCLUDED__
#define UTILS_H_INCLUDED__

class Utils {

protected:
    static const int maxexp = 160;

public:

    static string plus_hex(string hex1, string hex2)
    {
        std::transform(hex1.begin(), hex1.end(),hex1.begin(), ::toupper);
        std::transform(hex2.begin(), hex2.end(),hex2.begin(), ::toupper);
        if (hex1.length() < hex2.length())
            hex1.swap(hex2);

        //for convenience, make sure that hex1 is longer.

        /*Strat algorithm*/

        int length1, length2;
        length1 = hex1.length();
        length2 = hex2.length();
        int flag = 0; // carry
        int get1, get2;
        int sum;

        while (length1>0)
        {
            //get first number
            if (hex1[length1 - 1] >= 'A')
                get1 = hex1[length1 - 1] - 55;
            else
                get1 = hex1[length1 - 1] - '0';

            //get second number

            if (length2 > 0)
            {
                if (hex2[length2 - 1] >= 'A')
                    get2 = hex2[length2 - 1] - 55;
                else
                    get2 = hex2[length2 - 1] - '0';
            }
            else
                get2 = 0;

            //get the sum
            sum = get1 + get2 + flag;

            if (sum >= 16)
            {
                int left = sum % 16;
                if (left >= 10)
                    hex1[length1 - 1] = 'A' + left % 10;
                else
                    hex1[length1 - 1] = '0' + left;
                flag = 1;
            }
            else
            {
                if (sum >= 10)
                    hex1[length1 - 1] = 'A' + sum % 10;
                else
                    hex1[length1 - 1] = '0' + sum;
                flag = 0;
            }

            length1--;
            length2--;
        }

        if (flag == 1)
            return "1" + hex1;
        else
            return hex1;

        /*End of algorithm*/
    }

    static bool isSmaller(string str1, string str2)
    {
        // Calculate lengths of both string
        int n1 = str1.length(), n2 = str2.length();

        if (n1 < n2)
            return true;
        if (n2 < n1)
            return false;

        for (int i=0; i<n1; i++)
            if (str1[i] < str2[i])
                return true;
            else if (str1[i] > str2[i])
                return false;

        return false;
    }

    static string diff_hex(string hex1, string hex2, bool debug)
    {
        bool swapped = false;
        const BaseConverter& hex2dec = BaseConverter::HexToDecimalConverter();
        std::transform(hex1.begin(), hex1.end(),hex1.begin(), ::toupper);
        string str1 =  hex2dec.Convert(hex1);
        if (debug) EV_DEBUG << "Stringa1 to dec: "<< str1 << "\n";

        std::transform(hex2.begin(), hex2.end(),hex2.begin(), ::toupper);
        string str2 =  hex2dec.Convert(hex2);
        if (debug) EV_DEBUG << "Stringa1 to dec: "<< str2 << "\n";

        // Before proceeding further, make sure str1
        // is not smaller
        if (isSmaller(str1, str2)){
            swap(str1, str2);
            swapped = true;
        }



        // Take an empty string for storing result
        string str = "";

        // Calculate lengths of both string
        int n1 = str1.length(), n2 = str2.length();
        int diff = n1 - n2;

        // Initially take carry zero
        int carry = 0;

        // Traverse from end of both strings
        for (int i=n2-1; i>=0; i--)
        {
            // Do school mathematics, compute difference of
            // current digits and carry
            int sub = ((str1[i+diff]-'0') -
                    (str2[i]-'0') -
                    carry);
            if (sub < 0)
            {
                sub = sub+10;
                carry = 1;
            }
            else
                carry = 0;

            str.push_back(sub + '0');
        }

        // subtract remaining digits of str1[]
        for (int i=n1-n2-1; i>=0; i--)
        {
            if (str1[i]=='0' && carry)
            {
                str.push_back('9');
                continue;
            }
            int sub = ((str1[i]-'0') - carry);
            if (i>0 || sub>0) // remove preceding 0's
                str.push_back(sub+'0');
            carry = 0;

        }

        // reverse resultant string
        reverse(str.begin(), str.end());


        if (debug) EV_DEBUG << "dec: " << str << "\n";
        while(str[0]=='0'){
            str.erase(0,1);
        }
        if (debug) EV_DEBUG << "dec senza zeri: " << str << "\n";
        mpz_t  n;
        mpz_init (n);
        const char* stringa = str.c_str();
        mpz_init_set_str (n, stringa, 0);
        if(swapped){
            return Utils::diff_hex("ffffffffffffffffffffffffffffffffffffffff", mpz_get_str(nullptr, 16, n), debug);
        }else{

            return mpz_get_str(nullptr, 16, n);
        }

    }

    static bool isGreater(string str1, string str2, bool debug){
        /*
         * returns true if first argument is greater than the second, false otherwise*/


        // Calculate lengths of both string
        int n1 = str1.length(), n2 = str2.length();

        if (n1 > n2)
            return true;
        if (n2 > n1){
            if(debug) EV_DEBUG << "second is longer than first" << endl;
            return false;}
        for (int i=0; i<n1; i++){
            if (str1[i] > str2[i]){
                if(debug) EV_DEBUG << str1[i] <<"is bigger than "<< str2[i] << endl;
                return true;
            }
            else if (str1[i] < str2[i]){
                if(debug) EV_DEBUG << str1[i] <<"is less than "<< str2[i] << endl;
                return false;
            }
        }
        if(debug) EV_DEBUG << "strings are equal" << endl;
        return false;
    }


    static string getKeyInModule(int exp, string key, bool debug){
        /*
         * this function performs the real module of n+2^k operation
         */
        // we get 2^k in hex first:
        //std::transform(key.begin(), key.end(),key.begin(), ::toupper);
        if (exp > Utils::maxexp){
            throw cRuntimeError("Chord::utils(): exponent is too high!");
        }
        char *max_hex;
        mpz_t max;
        mpz_init(max);
        mpz_init_set_str(max, "1461501637330902918203684832716283019655932542975", 10);
        string s(mpz_get_str(nullptr, 16, max));
        //std::transform(s.begin(), s.end(),s.begin(), ::toupper);
        if(debug) EV_DEBUG << "maximum hex: "<< s << "and string: " << key<< "\n";
        mpz_t  n;
        mpz_t base;
        mpz_init (base);
        mpz_init_set_str(base, "2", 10);
        mpz_t exp_;
        mpz_init (exp_);
        string s_exp = std::to_string(exp);
        const char* c_exp = s_exp.c_str();
        string exponent_prova (c_exp);
        if(debug)EV_DEBUG << "saved exponent: "<< exponent_prova <<"\n";
        mpz_init_set_str(exp_, c_exp, 10);
        mpz_init (n);
        mpz_powm_ui(n, base, exp, max);
        string two_raised(mpz_get_str(nullptr, 16, n));
        if(debug)EV_DEBUG <<"2 raised at "<<exp<< " in hex: "<<two_raised<< " mod("<< s<< ")\n";
        if(debug)EV_DEBUG << "Now we compute n+2^k:\n";
        string sum = Utils::plus_hex(key, two_raised);
        //std::transform(sum.begin(), sum.end(),sum.begin(), ::toupper);
        if (debug && exp == 0) EV_DEBUG << "the sum for first finger is: " << sum << endl;
        while(Utils::isGreater(sum, s, debug)){
            string result = Utils::diff_hex(sum, s, debug);
            //std::transform(result.begin(), result.end(),result.begin(), ::toupper);
            sum=result;
        }

        if(debug)EV_DEBUG << sum << "\n";
        return sum;

    }

    static bool isBetween(string key, string lkey, string rkey){
        if (key.empty() || lkey.empty() || rkey.empty())
            return false;
        if (key == lkey)
            return false;
        else if (Utils::isGreater(rkey, lkey, false))
            return (Utils::isGreater(key, lkey, false) && Utils::isGreater(rkey, key, false));
        else
            return (Utils::isGreater(key, lkey, false) || Utils::isGreater(rkey, key, false));
    }

    static bool isBetweenR(string key, string lkey, string rkey){

        if (key.empty() || lkey.empty() || rkey.empty()){

            return false;
        }

        if ((key == lkey) && (key == rkey)){

            return false;
        }
        else if (Utils::isGreater(rkey, lkey, false) || rkey == lkey){

            return (Utils::isGreater(key, lkey, false) && (Utils::isGreater(rkey, key, false) || key == rkey));}
        else{

            return (Utils::isGreater(key, lkey, false) || (Utils::isGreater(rkey, key, false) || key == rkey));}
    }

    static bool isBetweenL(string key, string lkey, string rkey){
        if (key.empty() || lkey.empty() || rkey.empty())
            return false;

        if ((key == lkey) && (key == rkey))
            return false;
        else if (Utils::isGreater(rkey, lkey, false) || rkey == lkey)
            return ((Utils::isGreater(key, lkey, false)|| key == lkey) && (Utils::isGreater(rkey, key, false) || key == rkey));
        else
            return ((Utils::isGreater(key, lkey, false)|| key == lkey) || (Utils::isGreater(rkey, key, false) || key == rkey));
    }

    static bool isBetweenLR(string key, string lkey, string rkey){
        if (key.empty() || lkey.empty() || rkey.empty())
            return false;

        if ((key == lkey) && (key == rkey))
            return false;
        else if (Utils::isGreater(rkey, lkey, false) || rkey == lkey)
            return ((Utils::isGreater(key, lkey, false)|| key == lkey) && Utils::isGreater(rkey, key, false) );
        else
            return ((Utils::isGreater(key, lkey, false)|| key == lkey) || Utils::isGreater(rkey, key, false) );
    }


    static cModule* getModule(string IP, bool node, bool ip = true){
        /*
         * if node is set to true returns Node istead of NodeHandle
         * */
        if(ip == false){
            cModule* net = getSimulation()->getModuleByPath("Tictoc1");
            int numNodes = getSimulation()->getModuleByPath("Tictoc1")->par("numNodes").intValue();
            for (int i=0; i<numNodes; i++){
                if (net->getSubmodule("array", i)->par("KEY").stdstringValue() == IP){
                    if(node){
                        return net->getSubmodule("array", i)->getSubmodule("node");
                    }else
                        return net->getSubmodule("array", i);
                }
            }
            throw cRuntimeError("cannot find module with KEY");
            return net;
        }else {
            cModule* net = getSimulation()->getModuleByPath("Tictoc1");
            int numNodes = getSimulation()->getModuleByPath("Tictoc1")->par("numNodes").intValue();
            for (int i=0; i<numNodes; i++){
                if (net->getSubmodule("array", i)->par("IP").stdstringValue() == IP){
                    if(node){
                        return net->getSubmodule("array", i)->getSubmodule("node");
                    }else
                        return net->getSubmodule("array", i);
                }
            }
            throw cRuntimeError("cannot find module with IP");
            return net;
        }

    }

    static bool isSmallerComparator(std::pair<std::pair<string, bool>,Node*> first, std::pair<std::pair<string, bool>,Node*> second) {
        string str1 = first.first.first;
        string str2 = second.first.first;
        int n1 = first.first.first.length(), n2 = second.first.first.length();

        if (n1 < n2)
            return true;
        if (n2 < n1)
            return false;

        for (int i=0; i<n1; i++)
            if (str1[i] < str2[i])
                return true;
            else if (str1[i] > str2[i])
                return false;

        return false;
    }
};




#endif /* UTILS_H_ */
