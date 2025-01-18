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

package multicore_sched.simulations;

import multicore_sched.Cpu;
import multicore_sched.Scheduler;
import multicore_sched.ProcessGenerator;

network Computer
{
    parameters:
        int numCpus = default(4);

    submodules:
        cpu[numCpus]: Cpu {
            @display("p=100,100");
        }
        scheduler: Scheduler {
            @display("p=100,300");
        }
        processGenerator: ProcessGenerator {
            @display("p=100,500");
        }
    connections:
        processGenerator.processOut --> scheduler.newProcessIn;
        for i=0..numCpus-1 {
            scheduler.processCpuIn++ <-- cpu[i].processOut;
            scheduler.processCpuOut++ --> cpu[i].processIn;
        }
}
