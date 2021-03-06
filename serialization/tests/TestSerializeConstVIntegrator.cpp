/* -------------------------------------------------------------------------- *
 *                               OpenMMConstV                                 *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit originating from   *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c)                                                     *
 *         2018 California Institute and Techology and the Authors.           *
 * Authors: Chang Yun Son                                                     *
 * Contributors:                                                              *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files (the "Software"), *
 * to deal in the Software without restriction, including without limitation  *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
 * and/or sell copies of the Software, and to permit persons to whom the      *
 * Software is furnished to do so, subject to the following conditions:       *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in *
 * all copies or substantial portions of the Software.                        *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
 * THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
 * USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
 * -------------------------------------------------------------------------- */

#include "openmm/internal/AssertionUtilities.h"

#include "openmm/ConstVLangevinIntegrator.h"

#include "openmm/serialization/XmlSerializer.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>

#include <fstream>

using namespace OpenMM;
using namespace std;

void testSerializeConstVLangevinIntegrator() {
    ConstVLangevinIntegrator *intg = new ConstVLangevinIntegrator(372.4, 1.234, 0.0018);
    stringstream ss;
    XmlSerializer::serialize<Integrator>(intg, "ConstVLangevinIntegrator", ss);
    ConstVLangevinIntegrator *intg2 = dynamic_cast<ConstVLangevinIntegrator*>(XmlSerializer::deserialize<Integrator>(ss));
    ASSERT_EQUAL(intg->getConstraintTolerance(), intg2->getConstraintTolerance());
    ASSERT_EQUAL(intg->getStepSize(), intg2->getStepSize());
    ASSERT_EQUAL(intg->getTemperature(), intg2->getTemperature());
    ASSERT_EQUAL(intg->getFriction(), intg2->getFriction());
    ASSERT_EQUAL(intg->getRandomNumberSeed(), intg2->getRandomNumberSeed());
    delete intg;
    delete intg2;
}

int main() {
    try {
        testSerializeConstVLangevinIntegrator();
    }
    catch(const exception& e) {
        cout << "exception: " << e.what() << endl;
        return 1;
    }
    cout << "Done" << endl;
    return 0;
}
