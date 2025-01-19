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

#include "ProcessGenerator.h"
#include "msgProcess_m.h"

Define_Module(ProcessGenerator);

void ProcessGenerator::initialize()
{
    meanGenerationTime_ = par("meanGenerationTime");
    meanProcessDuration_ = par("meanProcessDuration");
    p_cpu_bound_ = par("p_cpu_bound");

    IOPercentageCPUbound_ = par("IOPercentageCPUbound");
    IOPercentageIObound_ = par("IOPercentageIObound");

    timer_ = new cMessage("generationTimer");
    scheduleNext();
}

void ProcessGenerator::handleMessage(cMessage *msg)
{
    // event generationTimer
    MsgProcess *newProcess = new MsgProcess("newProcess");

    double duration = exponential(meanProcessDuration_, 1);

    double random = uniform(0, 1, 2);
    double IOPercentage;
    double CPUPercentage;
    if (random < p_cpu_bound_) // CPU bound
    {
        IOPercentage = IOPercentageCPUbound_;
        EV << "New process " << newProcess->getId() << " generated (CPU bound)" << endl;
    }
    else // IO bound
    {
        IOPercentage = IOPercentageIObound_;
        EV << "New process " << newProcess->getId() << " generated (IO bound)" << endl;
    }
    CPUPercentage = 0.5 - IOPercentage / 2;

    newProcess->setInitDuration(duration * CPUPercentage);
    newProcess->setIODuration(duration * IOPercentage);
    newProcess->setFinalDuration(duration * CPUPercentage);
    newProcess->setIsFinalPhase(false);
    // newProcess->setCpuID(-1);

    EV << "New process " << newProcess->getId() << " duration: " << duration << endl;

    send(newProcess, "processOut");

    scheduleNext();
}

ProcessGenerator::~ProcessGenerator()
{
    cancelAndDelete(timer_);
}

void ProcessGenerator::scheduleNext()
{
    simtime_t generationTime = (simtime_t)exponential(meanGenerationTime_, 0);
    scheduleAfter(generationTime, timer_);
}
