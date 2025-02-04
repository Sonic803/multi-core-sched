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
  // parameters
  double meanGenerationTime_;
  double meanProcessDuration_;
  double pCpuBound_;

  double IOPercentageCPUbound_;
  double IOPercentageIObound_;

  std::string generationType_;
  std::string durationType_;

  cMessage *timer_;
  void scheduleNext();
  void validateParameters();

protected:
  virtual void initialize() override;
  virtual void handleMessage(cMessage *msg) override;
  virtual void finish() override;
};

#endif
