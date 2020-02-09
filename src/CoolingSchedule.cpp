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

#include "CoolingSchedule.h"
#include <cmath>

double _logarithmicSchedule(uint step, double t0, StopFunction s)
{
    if(s(step)) {
        return 0;
    } else {
        return t0/(log(2+step));
    }
}

CoolingSchedule logarithmicSchedule(double t0, StopFunction s)
{
    using namespace std::placeholders;
    return std::bind(_logarithmicSchedule, _1, t0, s); 
}

double _fastSchedule(uint step, double t0, StopFunction s)
{
    if(s(step)) {
        return 0;
    } else {
        return t0/(1+step);
    }
}

CoolingSchedule fastSchedule(double t0, StopFunction s)
{
    using namespace std::placeholders;
    return std::bind(_fastSchedule, _1, t0, s); 
}
