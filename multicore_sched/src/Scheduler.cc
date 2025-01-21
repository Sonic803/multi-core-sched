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

#include "Scheduler.h"
#include "msgProcess_m.h"
#include <queue>

using namespace std;

Define_Module(Scheduler);

int Scheduler::ProcessComparatorSJF(cObject *a, cObject *b)
{
    MsgProcess *aProcess = check_and_cast<MsgProcess *>(a);
    MsgProcess *bProcess = check_and_cast<MsgProcess *>(b);
    simtime_t aRemainingTime, bRemainingTime;

    aRemainingTime = aProcess->isFinalPhase() ? aProcess->getFinalDuration() : aProcess->getInitDuration();
    bRemainingTime = bProcess->isFinalPhase() ? bProcess->getFinalDuration() : bProcess->getInitDuration();

    return aRemainingTime < bRemainingTime ? -1 : 1;
}

void Scheduler::initialize()
{
    turnaroundTime_ = registerSignal("turnaroundTimeSignal");
    waitedReadyTime_ = registerSignal("waitedReadyTimeSignal");
    numProcReady_ = registerSignal("numProcReadySignal");
    numBusyCpus_ = registerSignal("numBusyCpusSignal");

    bool FCFS = par("isFCFS").boolValue();
    if (!FCFS)
        readyQueue_.setup(ProcessComparatorSJF);

    int numGatesIn = gate("processCpuIn", 0)->getVectorSize();
    int numGatesOut = gate("processCpuOut", 0)->getVectorSize();

    if (numGatesIn != numGatesOut)
        throw cRuntimeError("Scheduler::initialize - in != out");

    numGatesCpu_ = numGatesIn;

    for (int i = 0; i < numGatesCpu_; i++)
    {
        cpuQueue_.push(i);
    }

    emit(numBusyCpus_, 0);
    emit(numProcReady_, 0);

}

void Scheduler::handleMessage(cMessage *msg)
{
    MsgProcess *process = check_and_cast<MsgProcess *>(msg);

    if (process->isName("newProcess"))
    {
        process->setName("process");
        process->setReadyQueueArrivalTime(simTime());
        readyQueue_.insert(process);
    }
    else if (process->isName("cpuFree"))
    {
        int cpuID = msg->getArrivalGate()->getIndex();
        cpuQueue_.push(cpuID);

        if (!process->isFinalPhase())
        {
            process->setIsFinalPhase(true);

            EV << "Process " << process->getId() << " in I/O phase for " << process->getIODuration() << " seconds" << endl;

            process->setName("endIO");
            scheduleAfter(process->getIODuration(), process);
        }
        else
        {
            // process has ended
            // emit the turnaround time
            simtime_t turnaroundTime = simTime() - process->getCreationTime();
            emit(turnaroundTime_, turnaroundTime);
            EV << "Process " << process->getId() << " ended: turnaround time = " << turnaroundTime << endl;
            // emit the waited time in the ready queue
            simtime_t waitedReadyTime = process->getTimeWaitedInReadyQueue();
            emit(waitedReadyTime_, waitedReadyTime);
            EV << "Process " << process->getId() << " waited in ready queue for " << waitedReadyTime << endl;

            delete process;
        }
    }
    else if (process->isName("endIO"))
    {
        process->setName("process");
        process->setReadyQueueArrivalTime(simTime());
        readyQueue_.insert(process);
    }
    else
        throw cRuntimeError("Scheduler::handlemessage - message not supported");

    scheduleProcess();

    // Emit the number of processes in the ready queue
    emit(numProcReady_, readyQueue_.getLength());

    // Emit the number of busy CPUs
    emit(numBusyCpus_, numGatesCpu_ - cpuQueue_.size());

    // Display the queue length
    getDisplayString().setTagArg("t", 0, readyQueue_.getLength());
}

void Scheduler::scheduleProcess()
{
    if (readyQueue_.isEmpty() || cpuQueue_.empty())
        return;

    // log the process cqueue
    EV << "Process queue: ";
    for (cQueue::Iterator it(readyQueue_); !it.end(); it++)
    {
        MsgProcess *process = check_and_cast<MsgProcess *>(*it);
        EV << process->getId() << "(" << (process->isFinalPhase() ? process->getFinalDuration() : process->getInitDuration()) << ") <- ";
    }
    EV << endl;

    int cpuID = cpuQueue_.front();
    cpuQueue_.pop();

    MsgProcess *process = check_and_cast<MsgProcess *>(readyQueue_.front());
    readyQueue_.pop();

    EV << "Process " << process->getId() << " scheduled on CPU " << cpuID << endl;

    // Update the time waited in the ready queue
    process->setTimeWaitedInReadyQueue(process->getTimeWaitedInReadyQueue() + simTime() - process->getReadyQueueArrivalTime());

    // process->setCpuID(cpuID);
    send(process, "processCpuOut", cpuID);
}

Scheduler::~Scheduler()
{
    while (!readyQueue_.isEmpty())
        delete readyQueue_.pop();

    while (!cpuQueue_.empty())
    {
        cpuQueue_.pop();
    }
}
