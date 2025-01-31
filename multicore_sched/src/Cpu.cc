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

#include "Cpu.h"
#include "msgProcess_m.h"

Define_Module(Cpu);

void Cpu::initialize()
{
    cpuBusyTime_ = registerSignal("cpuBusyTimeSignal");
}

void Cpu::handleMessage(cMessage *msg)
{
    MsgProcess *process = check_and_cast<MsgProcess *>(msg);

    if (process->isSelfMessage()) // end of initial or final phase of CPU execution
    {
        // Change the color of the CPU when it finishes executing
        getDisplayString().setTagArg("i", 2, "0");

        // process has finished executing
        process->setName("cpuFree");

        // Emit for how long was the cpu busy
        emit(cpuBusyTime_, simTime() - process->getCpuArrivalTime());

        // send message to scheduler
        send(process, "processOut");
    }
    else if (process->isName("process")) // the process is starting executing
    {
        // Change the color of the CPU when it is active
        getDisplayString().setTagArg("i", 2, "40");

        // Arrival time in the CPU
        process->setCpuArrivalTime(simTime());

        if (!process->isFinalPhase()) // Init Phase
        {
            EV << "Process " << process->getId() << " in init phase for " << process->getInitDuration() << " seconds" << endl;
            scheduleAfter(process->getInitDuration(), process); // Execute
        }
        else // Final phase
        {
            EV << "Process " << process->getId() << " in final phase for " << process->getFinalDuration() << " seconds" << endl;
            scheduleAfter(process->getFinalDuration(), process); // Execute
        }
    }
    else
        throw cRuntimeError("Cpu::handleMessage - message not supported");
}
