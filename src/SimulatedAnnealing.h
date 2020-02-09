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

#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

#include <functional>
#include <cmath>
#include <random>
#include "CoolingSchedule.h"

/**
 * Must return new elemnt which is in random way modificated given element
 * @element given element for generating a new
 * @t temperature
 */
template <class SpaceElement>
using SpaceOperator = std::function<SpaceElement(SpaceElement const& element, double t)>;

/**
 * Must return energy of given state
 */
template <class SpaceElement>
using Functional = std::function<double(SpaceElement const& state)>;

/**
 * Must return P(eOld, eNew, t) = P(new_candidate -> state_i+1 | state_i) such that 
 * P(new_candidate -> state_i+1 | state_i) + P(state_i -> state_i+1 | state_i) = 1
 * @eOld E(state_i)
 * @eNew E(new_candidate)
 * @t temperature
 */
using ProbabilityFunction =  std::function<double(double eOld, double eNew, double t)>;

/**
 * Receives every step of solution search
 * @state current solution
 * @e energy of current solution
 */
template <class SpaceElement>
using RecorderFunction = std::function<void(SpaceElement const& state, double e)>;

/**
 * defaultProbabilityFunction = P(eOld, eNew, t) = P(new_candidate -> state_i+1 | state_i) =
 * 1, if eOld < eNew
 * exp(t(eOld - eNew)), otherwize
 */
double defaultProbabilityFunction(double eOld, double eNew, double t); // TODO переделать чтобы не надо было оборочаивать

// TODO опция не увеличивать счетчик после нудачной итерации. Idea. Все 2*2 типа функций можно состряпать через предпроцессор
/**
 * Returns the results of Simulated annealing algorithm. The only requirment for type of SpaceElement is to have copy constructor and copy operator
 * @beginning starting state of the algorithm
 * @randomOperator random operator which in random way modificates given element
 * @energy functional from space element that algorithm will minimize
 * @schedule temperature sequence
 * @probability probability to choose the next random state
 */
template <class SpaceElement>
SpaceElement SimulatedAnnealing(SpaceElement const& beginning, SpaceOperator<SpaceElement> randomOperator, Functional<SpaceElement> const energy, CoolingSchedule schedule,
                                 ProbabilityFunction probability = ProbabilityFunction(defaultProbabilityFunction), RecorderFunction<SpaceElement> recorder = RecorderFunction<SpaceElement>())
{
    SpaceElement currentElement(beginning);
    SpaceElement candidateElement(beginning); // just in order to not add requirment for SpaceElement to have default constrator 
    
    std::random_device rd;
    std::uniform_real_distribution<> random (0, 1);
    
    uint step = 0;
    while(schedule(step) > 0)
    {
        candidateElement = randomOperator(currentElement, schedule(step));
        if(random(rd) <= probability(energy(currentElement), energy(candidateElement), schedule(step))) {
            currentElement = candidateElement;
        }
        if(recorder) {
            recorder(currentElement, energy(currentElement));
        }
        ++step;
    }
    // TODO было бы неплохо сохранять еще и самый минимум, т.к. на последнем шаге можно отойти в немного худшее сосотяние чем было
    // Тогда нужно юзать мультипоинтер умный
    return currentElement;
}


#endif // SIMULATEDANNEALING_H
