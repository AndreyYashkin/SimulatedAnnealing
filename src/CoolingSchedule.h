/*
 * Copyright (c) 2019 Andrey Yashkin <andreyyashkin@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef COOLINGSHEDUULE_H
#define COOLINGSHEDUULE_H

#include <functional>

/**
 * Must return temperature of given step.
 * CoolingSchedule(i+1) should be less that CoolingSchedule(i)
 * There must exist such j that CoolingSchedule(j) == 0
 */
using CoolingSchedule = std::function<double(uint step)>;

/**
 * Return function that cuts schedule by 0 after some conditions
 */
using StopFunction = std::function<bool(uint step)>;

/**
 * Returns logarithmic schedule
 * T(k) = t0/(log(2+k)
 * @to > 0
 */
CoolingSchedule logarithmicSchedule(double t0, StopFunction s);

/**
 * Returns fasr schedule
 * T(k) = t0/(1+k)
 * @to > 0
 */
CoolingSchedule fastSchedule(double t0, StopFunction s);


#endif // COOLINGSHEDUULE_H
