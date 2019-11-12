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

//
// TODO generated message class
//
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



cplusplus {{
#include <NodeHandle.h>
#include <SuccessorList.h>
#include <FingerTable.h>
}}



enum STATE {
	PING = 0;
	JOIN = 1;
	FIND_SUCCESSOR = 2;
	FIND_PREDECESSOR = 3;
	NEWSUCCESSORHINT = 4;	
	
}

packet BaseChordMessage {
}

packet BaseCallMessage extends BaseChordMessage{
}

packet BaseResponseMessage extends BaseChordMessage{
}

packet BaseNetworkPacket{
}

packet Stabilization extends BaseNetworkPacket{
	string ring[];
	string src;
	int hops;
	simtime_t start;
}

// call/response for PING
// TODO: ci va messo qualcosa qua dentro?
packet PingTimeout extends BaseChordMessage{
	string failed;
}

packet PingCall extends BaseCallMessage {
	//string dst;
}	

packet PingResponse extends BaseResponseMessage {
}

// call/response for JOIN
packet JoinCall extends BaseCallMessage {
	string requester;
	string key;			
}

packet JoinResponse extends BaseResponseMessage {
    int successorNum;// number of entries in the successor list
    string src;    		
    string successorNode[];    // successor list of the message originator
    string predecessorNode;    // in aggressiveJoinMode: predecessor hint
}

// call/response for STABILIZE
packet StabilizeCall extends BaseCallMessage {
}

packet StabilizeResponse extends BaseResponseMessage {
    string predecessorNode; 
    string predecessorNodeIP;   // the predecessor of the message originator
}

// call/response for NOTIFY
packet NotifyCall extends BaseCallMessage {
	string failed;// TODO: qui non so cosa metterci, su oversim mette  TransportAddress failed = TransportAddress::UNSPECIFIED_NODE;
}

packet NotifyResponse extends BaseResponseMessage {
 	int successorNum; // number of entries in successor list
 	string successorNode[]; // successor list of the node that sent the msg
 	//string predecessorNode;
 	//bool predecessorNodeSet; // this tells if the dest node has been set as new predecessor (for merging)  
}

// call/response for FIXING the finger table
packet FixFingerCall extends BaseCallMessage {
 	int finger;
 	string fingerKey;
 	string requester; // the finger number that has to be fixed
}

packet FixFingerResponse extends BaseResponseMessage {
    int finger; // the finger number that has to be fixed
    string successorNode; // the successor of the node that sent the msg
}

packet NotifyBoostrapList extends BaseNetworkPacket {
	
	string Overlaykey;


}



