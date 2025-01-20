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

void ProcessGenerator::validateParameters()
{
    if (meanGenerationTime_ <= 0)
    {
        error("meanGenerationTime must be positive");
    }
    if (meanProcessDuration_ <= 0)
    {
        error("meanProcessDuration must be positive");
    }
    if (p_cpu_bound_ > 1 || p_cpu_bound_ < 0)
    {
        error("p_cpu_bound must be between 0 and 1");
    }
    if (IOPercentageCPUbound_ > 1 || IOPercentageCPUbound_ < 0)
    {
        error("IOPercentageCPUbound must be between 0 and 1");
    }
    if (IOPercentageIObound_ > 1 || IOPercentageIObound_ < 0)
    {
        error("IOPercentageIObound must be between 0 and 1");
    }
    if (generationType_ != "exponential" && generationType_ != "uniform" && generationType_ != "constant")
    {
        error("Unknown generation type");
    }
    if (durationType_ != "exponential" && durationType_ != "uniform" && durationType_ != "constant")
    {
        error("Unknown duration type");
    }
}

void ProcessGenerator::initialize()
{
    meanGenerationTime_ = par("meanGenerationTime");
    meanProcessDuration_ = par("meanProcessDuration");
    p_cpu_bound_ = par("p_cpu_bound");

    IOPercentageCPUbound_ = par("IOPercentageCPUbound");
    IOPercentageIObound_ = par("IOPercentageIObound");

    generationType_ = par("generationType").stringValue();
    durationType_ = par("durationType").stringValue();

    validateParameters();

    timer_ = new cMessage("generationTimer");

    scheduleNext();
}

void ProcessGenerator::handleMessage(cMessage *msg)
{
    // event generationTimer
    MsgProcess *newProcess = new MsgProcess("newProcess");

    double duration;

    if (durationType_ == "exponential")
    {
        duration = exponential(meanProcessDuration_, 1);
    }
    else if (durationType_ == "uniform")
    {
        duration = uniform(0, meanProcessDuration_ * 2, 1);
    }
    else if (durationType_ == "constant")
    {
        duration = meanProcessDuration_;
    }

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
    newProcess->setTimeWaitedInReadyQueue(0);

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
    simtime_t generationTime;
    if (generationType_ == "exponential")
    {
        generationTime = (simtime_t)exponential(meanGenerationTime_, 0);
    }
    else if (generationType_ == "uniform")
    {
        generationTime = (simtime_t)uniform(0, meanGenerationTime_ * 2, 0);
    }
    else if (generationType_ == "constant")
    {
        generationTime = (simtime_t)meanGenerationTime_;
    }
    scheduleAfter(generationTime, timer_);
}
