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

//
// TODO generated message class
//
message MsgProcess {
    simtime_t InitDuration; // Duration of the initial processing phase
    simtime_t IODuration; // Duration of the I/O phase
    simtime_t finalDuration; // Duration of the final processing phase
    simtime_t cpuArrivalTime; // Arrival time of the process in the CPU
    simtime_t readyQueueArrivalTime; // Arrival time of the process in ready queue
    simtime_t timeWaitedInReadyQueue; // Total time waited in the ready queue

    bool isFinalPhase; // true if the process is executing the final processing phase
}
