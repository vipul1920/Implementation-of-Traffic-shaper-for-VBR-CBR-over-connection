/*
 * stationB.cc
 *
 *  Created on: Mar 15, 2019
 *      Author: root
 */
#include <omnetpp.h>

using namespace omnetpp;

class stationB : public cSimpleModule
{
private:
    simtime_t prevTime, currTime, diff;
    cOutVector spacetimes;
protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(stationB);

void stationB::initialize()
{
    prevTime = simTime();
}

void stationB::handleMessage(cMessage *msg)
{
    EV<<"Received message\n";
    currTime = simTime();
    diff = currTime - prevTime;
    //EV<<"Inter-arrival time is "<<diff<<"\n";
    spacetimes.record(diff);
    prevTime = currTime;
}



