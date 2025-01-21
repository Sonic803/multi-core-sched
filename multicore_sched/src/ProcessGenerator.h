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

#ifndef __MULTICORE_SCHED_PROCESSGENERATOR_H_
#define __MULTICORE_SCHED_PROCESSGENERATOR_H_

#include <omnetpp.h>

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class ProcessGenerator : public cSimpleModule
{
  double meanGenerationTime_;
  double meanProcessDuration_;
  double p_cpu_bound_;

  double IOPercentageCPUbound_;
  double IOPercentageIObound_;

  std::string generationType_;
  std::string durationType_;

  std::vector<intval_t> randomStreams_;

  cMessage *timer_;
  void scheduleNext();

protected:
  virtual void initialize();
  void validateParameters();
  virtual void handleMessage(cMessage *msg);
  ~ProcessGenerator();
};

#endif
