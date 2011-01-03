/* +---------------------------------------------------------------------------+
   |          The Mobile Robot Programming Toolkit (MRPT) C++ library          |
   |                                                                           |
   |                   http://mrpt.sourceforge.net/                            |
   |                                                                           |
   |   Copyright (C) 2005-2011  University of Malaga                           |
   |                                                                           |
   |    This software was written by the Machine Perception and Intelligent    |
   |      Robotics Lab, University of Malaga (Spain).                          |
   |    Contact: Jose-Luis Blanco  <jlblanco@ctima.uma.es>                     |
   |                                                                           |
   |  This file is part of the MRPT project.                                   |
   |                                                                           |
   |     MRPT is free software: you can redistribute it and/or modify          |
   |     it under the terms of the GNU General Public License as published by  |
   |     the Free Software Foundation, either version 3 of the License, or     |
   |     (at your option) any later version.                                   |
   |                                                                           |
   |   MRPT is distributed in the hope that it will be useful,                 |
   |     but WITHOUT ANY WARRANTY; without even the implied warranty of        |
   |     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         |
   |     GNU General Public License for more details.                          |
   |                                                                           |
   |     You should have received a copy of the GNU General Public License     |
   |     along with MRPT.  If not, see <http://www.gnu.org/licenses/>.         |
   |                                                                           |
   +---------------------------------------------------------------------------+ */

#include <mrpt/opengl.h>  // Precompiled header

#include <mrpt/system.h>
#include <mrpt/utils/CFileOutputStream.h>

using namespace mrpt::utils;
using namespace mrpt::opengl;


/*---------------------------------------------------------------
					RobotPioneer
  ---------------------------------------------------------------*/
CSetOfObjectsPtr stock_objects::RobotPioneer()
{
	CSetOfObjectsPtr	ret = CSetOfObjects::Create();

	ret->setName("theRobot");

	CSetOfTrianglesPtr obj = CSetOfTriangles::Create();

	// Add triangles:
	CSetOfTriangles::TTriangle	trian;

	trian.r[0]=trian.r[1]=trian.r[2]= 1;
	trian.g[0]=trian.g[1]=trian.g[2]= 0;
	trian.b[0]=trian.b[1]=trian.b[2]= 0;
	trian.a[0]=trian.a[1]=trian.a[2]= 1;

	trian.x[0] = 0.10f; trian.x[1] =-0.20f; trian.x[2] =-0.20f;
	trian.y[0] =-0.10f; trian.y[1] = 0.10f; trian.y[2] =-0.10f;
	trian.z[0] = 0.20f; trian.z[1] = 0.25f; trian.z[2] = 0.25f;
	obj->insertTriangle( trian );	// 0
	trian.x[0] = 0.10f; trian.x[1] = 0.10f; trian.x[2] =-0.20f;
	trian.y[0] =-0.10f; trian.y[1] = 0.10f; trian.y[2] = 0.10f;
	trian.z[0] = 0.20f; trian.z[1] = 0.20f; trian.z[2] = 0.25f;
	obj->insertTriangle( trian );	// 1

	//trian.r = 0.9f; trian.g = 0; trian.b = 0; trian.a = 1;

	trian.x[0] = 0.10f; trian.x[1] = 0.10f; trian.x[2] = 0.10f;
	trian.y[0] =-0.10f; trian.y[1] =-0.10f; trian.y[2] = 0.10f;
	trian.z[0] = 0.05f; trian.z[1] = 0.20f; trian.z[2] = 0.20f;
	obj->insertTriangle( trian );	// 2
	trian.x[0] = 0.10f; trian.x[1] = 0.10f; trian.x[2] = 0.10f;
	trian.y[0] =-0.10f; trian.y[1] = 0.10f; trian.y[2] = 0.10f;
	trian.z[0] = 0.05f; trian.z[1] = 0.05f; trian.z[2] = 0.20f;
	obj->insertTriangle( trian );	// 3

	trian.x[0] =-0.20f; trian.x[1] =-0.20f; trian.x[2] =-0.20f;
	trian.y[0] =-0.10f; trian.y[1] =-0.10f; trian.y[2] = 0.10f;
	trian.z[0] = 0.05f; trian.z[1] = 0.25f; trian.z[2] = 0.25f;
	obj->insertTriangle( trian );	// 2b
	trian.x[0] =-0.20f; trian.x[1] =-0.20f; trian.x[2] =-0.20f;
	trian.y[0] =-0.10f; trian.y[1] = 0.10f; trian.y[2] = 0.10f;
	trian.z[0] = 0.05f; trian.z[1] = 0.05f; trian.z[2] = 0.25f;
	obj->insertTriangle( trian );	// 3b

	//trian.r = 0.8f; trian.g = 0; trian.b = 0; trian.a = 1;
	trian.x[0] = 0.10f; trian.x[1] =-0.20f; trian.x[2] =-0.20f;
	trian.y[0] =-0.10f; trian.y[1] =-0.10f; trian.y[2] =-0.10f;
	trian.z[0] = 0.20f; trian.z[1] = 0.25f; trian.z[2] = 0.05f;
	obj->insertTriangle( trian );	// 4
	trian.x[0] = 0.10f; trian.x[1] = 0.10f; trian.x[2] =-0.20f;
	trian.y[0] =-0.10f; trian.y[1] =-0.10f; trian.y[2] =-0.10f;
	trian.z[0] = 0.20f; trian.z[1] = 0.05f; trian.z[2] = 0.05f;
	obj->insertTriangle( trian );	// 5

	trian.x[0] = 0.10f; trian.x[1] =-0.20f; trian.x[2] =-0.20f;
	trian.y[0] = 0.10f; trian.y[1] = 0.10f; trian.y[2] = 0.10f;
	trian.z[0] = 0.20f; trian.z[1] = 0.25f; trian.z[2] = 0.05f;
	obj->insertTriangle( trian );	// 6
	trian.x[0] = 0.10f; trian.x[1] = 0.10f; trian.x[2] =-0.20f;
	trian.y[0] = 0.10f; trian.y[1] = 0.10f; trian.y[2] = 0.10f;
	trian.z[0] = 0.20f; trian.z[1] = 0.05f; trian.z[2] = 0.05f;
	obj->insertTriangle( trian );	// 7

	trian.r[0]=trian.r[1]=trian.r[2]= 0.05f;
	trian.g[0]=trian.g[1]=trian.g[2]= 0.05f;
	trian.b[0]=trian.b[1]=trian.b[2]= 0.05f;
	trian.a[0]=trian.a[1]=trian.a[2]= 1;

	trian.x[0] = 0.00f; trian.x[1] = 0.00f; trian.x[2] = 0.05f;
	trian.y[0] = 0.11f; trian.y[1] = 0.11f; trian.y[2] = 0.11f;
	trian.z[0] = 0.00f; trian.z[1] = 0.10f; trian.z[2] = 0.05f;
	obj->insertTriangle( trian );	// 8
	trian.x[0] = 0.00f; trian.x[1] = 0.00f; trian.x[2] = -0.05f;
	trian.y[0] = 0.11f; trian.y[1] = 0.11f; trian.y[2] = 0.11f;
	trian.z[0] = 0.00f; trian.z[1] = 0.10f; trian.z[2] = 0.05f;
	obj->insertTriangle( trian );	// 9

	trian.x[0] = 0.00f; trian.x[1] = 0.00f; trian.x[2] = 0.05f;
	trian.y[0] =-0.11f; trian.y[1] =-0.11f; trian.y[2] =-0.11f;
	trian.z[0] = 0.00f; trian.z[1] = 0.10f; trian.z[2] = 0.05f;
	obj->insertTriangle( trian );	// 10
	trian.x[0] = 0.00f; trian.x[1] = 0.00f; trian.x[2] = -0.05f;
	trian.y[0] =-0.11f; trian.y[1] =-0.11f; trian.y[2] =-0.11f;
	trian.z[0] = 0.00f; trian.z[1] = 0.10f; trian.z[2] = 0.05f;
	obj->insertTriangle( trian );	// 11

	ret->insert( obj );

	return ret;
}


/*---------------------------------------------------------------
					CornerXYZ
  ---------------------------------------------------------------*/
CSetOfObjectsPtr stock_objects::CornerXYZ(float scale)
{
	CSetOfObjectsPtr ret = CSetOfObjects::Create();

	CArrowPtr obj = CArrow::Create(
        	0,0,0,
            scale,0,0,
            0.25f*scale,0.02f*scale,0.05f*scale);

    obj->setColor(1,0,0);

	ret->insert( obj );

	obj = CArrow::Create(
        	0,0,0,
            0,scale,0,
            0.25f*scale,0.02f*scale,0.05f*scale);
    obj->setColor(0,1,0);

    ret->insert( obj );

	obj = CArrow::Create(
    	0,0,0,
        0,0,scale,
        0.25f*scale,0.02f*scale,0.05f*scale);
    obj->setColor(0,0,1);

    ret->insert( obj );

    return ret;
}

/*---------------------------------------------------------------
					BumblebeeCamera
  ---------------------------------------------------------------*/
CSetOfObjectsPtr stock_objects::BumblebeeCamera()
{

	CSetOfObjectsPtr camera = opengl::CSetOfObjects::Create();

	CPolyhedronPtr rect = opengl::CPolyhedron::CreateCubicPrism( -0.02, 0.14, -0.02, 0.02, 0, -0.04 );
	rect->setColor( 1, 0.8, 0 );

	camera->insert( rect );

	CCylinderPtr lCam = opengl::CCylinder::Create( 0.01,0.01, 0.003, 10, 10 );
	lCam->setColor( 1,0,0 );

	CCylinderPtr rCam = opengl::CCylinder::Create( 0.01,0.01, 0.003, 10, 10 );
	rCam->setPose( CPose3D(0.12,0,0) );
	rCam->setColor( 0,0,0 );

	camera->insert( lCam );
	camera->insert( rCam );

	return camera;
}


// const char * SICK_LASER_MODEL_3DS_GZ
#include "internal_SICK_model3d.h"
/*---------------------------------------------------------------
					SICKLaser
 ---------------------------------------------------------------*/
CSetOfObjectsPtr stock_objects::SICKLaser()
{
	MRPT_START

	CSetOfObjectsPtr ret = CSetOfObjects::Create();

	// Save
	const std::string tmp_fil = mrpt::system::getTempFileName() + ".gz";  // Required for the "loadFrom3DSFile" method...
	{
		CFileOutputStream f(tmp_fil);
		f.WriteBuffer( SICK_LASER_MODEL_3DS_GZ, sizeof(SICK_LASER_MODEL_3DS_GZ) );
	}

	// load as gz-3ds scene:
	C3DSScenePtr obj3d = C3DSScene::Create();
	obj3d->loadFrom3DSFile(tmp_fil);
	obj3d->enableExtraAmbientLight();

	mrpt::system::deleteFile(tmp_fil);

    ret->insert( obj3d );

    return ret;
    MRPT_END
}

CSetOfObjectsPtr stock_objects::CornerXYZSimple(float scale, float lineWidth)
{
	CSetOfObjectsPtr ret = CSetOfObjects::Create();

	{
		CSimpleLinePtr lin = CSimpleLine::Create();
		lin->setLineWidth(lineWidth);
		lin->setColor(1,0,0);
		lin->setLineCoords(0,0,0, scale,0,0);
		ret->insert(lin);
	}
	{
		CSimpleLinePtr lin = CSimpleLine::Create();
		lin->setLineWidth(lineWidth);
		lin->setColor(0,1,0);
		lin->setLineCoords(0,0,0, 0,scale,0);
		ret->insert(lin);
	}
	{
		CSimpleLinePtr lin = CSimpleLine::Create();
		lin->setLineWidth(lineWidth);
		lin->setColor(0,0,1);
		lin->setLineCoords(0,0,0, 0,0,scale);
		ret->insert(lin);
	}
    return ret;
}

CSetOfObjectsPtr stock_objects::CornerXYSimple(float scale, float lineWidth)
{
	CSetOfObjectsPtr ret = CSetOfObjects::Create();

	{
		CSimpleLinePtr lin = CSimpleLine::Create();
		lin->setLineWidth(lineWidth);
		lin->setColor(1,0,0);
		lin->setLineCoords(0,0,0, scale,0,0);
		ret->insert(lin);
	}
	{
		CSimpleLinePtr lin = CSimpleLine::Create();
		lin->setLineWidth(lineWidth);
		lin->setColor(0,1,0);
		lin->setLineCoords(0,0,0, 0,scale,0);
		ret->insert(lin);
	}
    return ret;
}
