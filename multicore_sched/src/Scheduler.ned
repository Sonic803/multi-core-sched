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

package multicore_sched;

//
// TODO auto-generated module
//
simple Scheduler
{
    parameters:
        @signal[turnaroundTimeSignal];
        @signal[waitedReadyTimeSignal];
        @signal[numProcReadySignal];
        @signal[numBusyCpusSignal];
        @statistic[turnaroundTime](source="turnaroundTimeSignal"; record=mean,vector?,vector(mean)?);
        @statistic[waitedReadyTime](source="waitedReadyTimeSignal"; record=mean,vector?);
        @statistic[numProcReady](source="numProcReadySignal"; record=timeavg,vector?);
        @statistic[numBusyCpus](source="numBusyCpusSignal"; record=vector?,timeavg,vector(timeavg)?);

        bool isFCFS = default(true);

        @display("i=block/queue");
    gates:
        input newProcessIn;
        input processCpuIn[];
        output processCpuOut[];
}
