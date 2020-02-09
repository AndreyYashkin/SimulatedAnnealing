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

#include <functional>
#include <memory>
#include <random>
#include <cmath>
#include <iostream>
#include <SimulatedAnnealing.h>
#include "CoolingSchedule.h"

// TODO добавить код ошибки и возвращение нула
double randomPoint(double const& start, double /*t*/, double min, double max, double r, std::random_device& rd)
{
    double pointMin = start - r > min ? start - r : min;
    double pointMax = start + r < max ? start + r : max;
    std::uniform_real_distribution<double> dist(pointMin, pointMax);
    return dist(rd);
}

SpaceOperator<double> randomOperator(double min, double max, double r, std::random_device& rd)
{
    if(min >= max or r <= 0) {
        return nullptr;
    }
    using namespace std::placeholders;
    return std::bind(randomPoint, _1, _2, min, max, r, std::ref(rd));
}

double f1(double const& x)
{
    return sin(1.0/(1.05-cos(x)))*((x-0.5)*(x-0.5));
}

double f2(double const& x)
{
    return pow(x, 8)-pow(x, 7)-pow(x, 6)+pow(x, 5)-pow(x, 4)-2*pow(x, 2);
}

bool _stepLimit(uint step, uint stopStep)
{
    return step >= stopStep;
}

/**
 * Returns true if step limit is reached 
 * @maxStep max number of steps
 */
StopFunction stepLimit(uint stopStep)
{
    using namespace std::placeholders;
    return std::bind(_stepLimit, _1, stopStep);
}

/**
 * Prints point and f(point)
 */
void print(double const& x, double e)
{
    std::cout << "x = " << x << ", E(x) = " << e << std::endl;
}



int main(int argc, char **argv)
{
    std::random_device rd;
    
    RecorderFunction<double> printPtr = RecorderFunction<double>(print);
    CoolingSchedule shed = fastSchedule(10, stepLimit(100));
    SpaceOperator<double>  ro = randomOperator(-2, 2, 1, rd);
    double point;
    
    std::cout << "Example #1" << std::endl;
    std::cout << "minimize sin(1.0/(1.05-cos(x)))*((x-0.5)*(x-0.5)), -2<x<2, starting with point x = 0 using 100 steps" << std::endl;
    point = SimulatedAnnealing<double>(0, ro, f1, shed, defaultProbabilityFunction, print);
    std::cout << "Sol: x = " << point << std::endl;
    
    std::cout << "Example #2" << std::endl;
    std::cout << "minimize x^8-x^7-x^6+x^5-x^4-2*x^2, -2<x<2, starting with point x = 0 using 100 steps" << std::endl;

    point = SimulatedAnnealing<double>(0, ro, f2, shed, defaultProbabilityFunction, print);
    std::cout << "Sol: x = " << point << std::endl;
    
    return 0;
}
