//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2024/09/20
// 
//
//#pragma once
//header guard
#ifndef __SYSTEM_PARAMETER_H_
#define __SYSTEM_PARAMETER_H_

/**
* Use SystemParameter as a global system parameter container.
* 
*/
class SystemParameter {
public:
    SystemParameter( );
    static double radius;
    static double maxSpeed;
    static double acceleration;
    //
    static double simulationTimeStep;
    static int maxNumParticleSystems;
};

#endif