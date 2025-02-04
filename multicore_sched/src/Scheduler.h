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

#ifndef __MULTICORE_SCHED_SCHEDULER_H_
#define __MULTICORE_SCHED_SCHEDULER_H_

#include <omnetpp.h>
#include <queue>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Scheduler : public cSimpleModule
{
  simsignal_t turnaroundTime_;
  simsignal_t waitedReadyTime_;
  simsignal_t numProcReady_;
  simsignal_t numBusyCpus_;

  cQueue readyQueue_;
  std::queue<int> cpuQueue_;

  int numGatesCpu_;

  static int ProcessComparatorSJF(cObject *a, cObject *b);
  void scheduleProcess();

protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *msg) override;
  virtual void finish() override;
};

#endif
