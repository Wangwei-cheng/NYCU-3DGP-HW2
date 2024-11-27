//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2024/09/20
// 
#include <iostream>
#include "SystemParameter.h"

using namespace std;

/**
* Initialize the static member variables of the SystemParameter container.
* 
*/

double SystemParameter::radius = 200;
double SystemParameter::maxSpeed = 6.5;
double SystemParameter::acceleration = 0.50;
int SystemParameter::maxNumParticleSystems = 60;
double SystemParameter::simulationTimeStep = 0.1;

SystemParameter::SystemParameter() 
{
}
