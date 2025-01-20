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
}

void Cpu::handleMessage(cMessage *msg)
{
    MsgProcess *process = check_and_cast<MsgProcess *>(msg);

    if (process->isName("process"))
    {
        // Change the color of the CPU when it is active
        getDisplayString().setTagArg("i", 2, "40");

        // process to be executed
        process->setName("executing");
        if (!process->isFinalPhase())
        {
            EV << "Process " << process->getId() << " in init phase for " << process->getInitDuration() << " seconds" << endl;
            scheduleAfter(process->getInitDuration(), process);
        }
        else
        {
            EV << "Process " << process->getId() << " in final phase for " << process->getFinalDuration() << " seconds" << endl;
            scheduleAfter(process->getFinalDuration(), process);
        }
    }
    else if (process->isName("executing"))
    {
        // Change the color of the CPU when it finishes executing
        getDisplayString().setTagArg("i", 2, "0");

        // process has finished executing
        process->setName("cpuFree");

        // send message to scheduler
        send(process, "processOut");
    }
    else
        throw cRuntimeError("Cpu::handlemessage - message not supported");
}
