/*
 * stationS.cc
 *
 *  Created on: Mar 15, 2019
 *      Author: root
 */
#include <omnetpp.h>

using namespace omnetpp;

class stationS : public cSimpleModule
{
private:
    cMessage *event;
    int tokenBucket = 0;
    cQueue inputBuffer;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void createDelay();
};

Define_Module(stationS);

void stationS::createDelay()
{
    event = new cMessage("event");
    simtime_t tokenDelay = par("tokenDelay");
    scheduleAt(simTime() + tokenDelay, event);
}

void stationS::initialize()
{
    createDelay();
}

void stationS::handleMessage(cMessage *msg)
{
    // When a token is generated
    if(msg == event)
    {
        // Put it in the bucket and generate further tokens
        if(tokenBucket < 12)
        {
            tokenBucket += 1;
            EV<<"Number of tokens: "<<tokenBucket<<"\n";
        }
        if(!inputBuffer.isEmpty())
        {
            while(tokenBucket > 0)
            {
                cMessage *msgToSend = (cMessage *) inputBuffer.pop();
                send(msgToSend, "out");
                tokenBucket -= 1;
            }
        }
        createDelay();
    }
    else{
        // If there are tokens in the bucket, pass the message along
        if(tokenBucket > 0)
        {
            tokenBucket -= 1;
            send(msg, "out");
        }
        // Else put it in the buffer
        else{
            inputBuffer.insert(msg);
        }
    }
}


