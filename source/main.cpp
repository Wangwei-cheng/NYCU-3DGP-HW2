//
// 3D Game Programming
// National Yang Ming Chiao Tung University (NYCU), Taiwan
// Instructor: Sai-Keung Wong
// Date: 2024/09/20
// 

#include <iostream>
#include "TutorialApplication.h"

using namespace std;



int main(int argc, char* argv[])
{
    /*
    BasicTutorial_00 app("Ogre Object");
    app.go();
    */

	/*
	BasicTutorial_00 *app = new BasicTutorial_00("Using Pointer");
	app->go();
	delete app;
	*/

	/**
	 Instantiate a BasicTutorial_00 object, app.
	 Then invokte its go( ) function.
	 */
	BasicTutorial_00* app;
	app = new BasicTutorial_00(STUDENT_INFO);
	app->go();

	delete app;
    //! [main]
    return 0;
}