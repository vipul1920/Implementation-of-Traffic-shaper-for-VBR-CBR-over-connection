/*
 * stationA.cc
 *
 *  Created on: Mar 15, 2019
 *      Author: root
 */
#include <omnetpp.h>

using namespace omnetpp;

class stationA : public cSimpleModule
{
private:
    cMessage *event;
    simtime_t prevTime, currTime, diff;
    cOutVector timespaces;
    int i = 0;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void createDelay();
    void sendNextMessage();
};

Define_Module(stationA);

void stationA::createDelay()
{
    simtime_t transmissionDelay = par("transmissionDelay");
    event = new cMessage("event");
    scheduleAt(simTime() + transmissionDelay, event);
}

void stationA::sendNextMessage()
{
    cMessage *msg = new cMessage("msg");
    currTime = simTime();
    send(msg, "out");
    diff = currTime - prevTime;
    //EV<<"Sending times are "<<diff<<"\n";
    timespaces.record(diff);
    prevTime = currTime;
}

void stationA::initialize()
{
    prevTime = 0;
    createDelay();
}

void stationA::handleMessage(cMessage *msg)
{
    if(msg == event)
    {
        EV<<"Transmission Delay is over\n";
        EV<<"Sending message\n";
        sendNextMessage();
        createDelay();
    }
}

