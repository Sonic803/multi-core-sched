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
simple ProcessGenerator
{
    parameters:
        double meanGenerationTime @unit("s") = default(1s);
        double meanProcessDuration @unit("s") = default(1s);
        double p_cpu_bound = default(0.5);

        double IOPercentageCPUbound = default(0.2);
        double IOPercentageIObound = default(0.8);

        string generationType @enum("exponential","uniform") = default("exponential");
        string durationType @enum("exponential","uniform") = default("exponential");


    gates:
        output processOut;

}
