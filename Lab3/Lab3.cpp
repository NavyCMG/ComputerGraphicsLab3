
#include <iostream>
//#include "Helper.H"
#include "RasterSurface.h"
#include "XTime.h"
#include "Defines.h"
#include "MyMath.h"
#include "Shaders.h"
#include "RasterFunc.h"


int main()
{
	Vertex testv = Vertex(1, 2, 3, 4);
	Grid g = Grid();
	Cube c = Cube();
	Camera cam = Camera();
	srand(time(NULL));
	XTime* timer = new XTime();
	timer->Restart();
	float elapTime = 0;
	//Vertex result = VecMtrxMult(testv, test1);
	//float* result = OrthogAffinInverse(testInv);

	TranslateCube(&c, 0, .25, 0);
	RotateCameraX(-18, &cam);
	TransposeCamera(&cam, 0, 0, -1, 0);
	OrthogAffinInverseCam(&cam);

	RS_Initialize("Grimes Connor", screenWidth, screenHeight);
	do {
		timer->Signal();
		elapTime += timer->Delta();

		for (int i = 0; i < numPxls; ++i)
		{
			DrawPxl(i, 0xff000000, -1);
		}
		//DrawCube(c, &cam);
		DrawGrid(g, &cam);
		//TDrawCube(c, &cam);
		TreeDrawCube(c, &cam);

		if (elapTime > .033)
		{
			RotateCameraY(-1, &cam);
			OrthogAffinInverseCam(&cam);
			RotateCubeY(1, &c);
			elapTime -= .033;
		}

	} while (RS_Update(screen, sizeof(screen) >> 2));
	RS_Shutdown();
}
