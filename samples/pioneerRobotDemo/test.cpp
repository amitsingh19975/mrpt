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

#include <mrpt/hwdrivers/CActivMediaRobotBase.h>
#include <mrpt/base.h>

using namespace mrpt::hwdrivers;
using namespace mrpt::utils;
using namespace mrpt::math;
using namespace mrpt::slam;
using namespace mrpt::poses;
using namespace std;

int main(int argc, char **argv)
{
	try
	{
		// -------------------------------------------
		// Create the object:
		// -------------------------------------------
		CActivMediaRobotBase	robot;

		// -------------------------------------------
		// Load/set configuration:
		// -------------------------------------------
		// robot.loadConfig( ..., "robot_config" );    // Load from an .ini file

		// Set manually:
#ifdef MRPT_OS_WINDOWS
		string	port="COM4";
#else
		string	port="/dev/ttyUSB0";
#endif

		int 	port_baud = 115200;

		cout << "Usage: " << argv[0] << " [SERIAL_PORT [BAUD_RATE] ]" << endl;

        if (argc>=2)
        {
            port = std::string(argv[1]);

            if (argc>=3)
                port_baud = atoi(argv[2]);
        }

		cout << "Setting serial port to: " << port << " @ " << port_baud << endl;
		robot.setSerialPortConfig( port, port_baud );


		// -------------------------------------------
		//  Init comms:
		// -------------------------------------------
		robot.enableSonars();
		robot.initialize();

		robot.enableJoystickControl();


		double cur_v = 0;
		double cur_w = 0;


		CActivMediaRobotBase::TRobotDescription  robInfo;
		robot.getRobotInformation(robInfo);

		cout << "Robot # front bumpers : " << robInfo.nFrontBumpers << endl;
		cout << "Robot # rear bumpers  : " << robInfo.nRearBumpers << endl;
		cout << "Robot # sonars        : " << robInfo.nSonars << endl;


		bool show_menu = true;
		while (1)
		{
			if (show_menu)
			{
				show_menu=false;

				cout << "Press the key for your option:" << endl << endl;
				cout << " q/a   : +/- linear speed" << endl;
				cout << " s/d   : +/- angular speed" << endl;
				cout << " space : stop" << endl;
				cout << " o     : Query odometry" << endl;
				cout << " n     : Query sonars" << endl;
				cout << " b     : Query battery level" << endl;
				cout << " p     : Query bumpers" << endl;
				cout << " x     : Quit" << endl;
			}

			if (!mrpt::system::os::kbhit())
			{
				robot.doProcess();

				CGenericSensor::TListObservations dummy;
				robot.getObservations(dummy);  // Empty the list

				mrpt::system::sleep(20);
				continue;
			}
			char c = mrpt::system::os::getch();

			show_menu=true;


			if (c=='x') break;

			if (c=='w' || c=='s')
			{
				if (c=='w') cur_v += 0.05;
				if (c=='s') cur_v -= 0.05;
				robot.setVelocities( cur_v, cur_w );
			}

			if (c=='a' || c=='d')
			{
				if (c=='a') cur_w += 0.05;
				if (c=='d') cur_w -= 0.05;
				robot.setVelocities( cur_v, cur_w );
			}

			if (c==' ')
			{
				cur_v = 0;
				cur_w = 0;
				robot.setVelocities( cur_v, cur_w );
			}

			if (c=='o')
			{
				CPose2D 	odo;
				double 		v,w;
				int64_t  	left_ticks, right_ticks;
				robot.getOdometryFull( odo, v, w, left_ticks, right_ticks );

				cout << "Odometry: " << odo << " v: " << v << " w: " << RAD2DEG(w) << " left: " << left_ticks << " right: " << right_ticks << endl;
			}

			if (c=='p')
			{
				vector_bool bumps;
				robot.getBumpers(bumps);

				cout << "Bumpers: "<< bumps << endl;
			}

			if (c=='n' || c=='N')
			{
				CObservationRange obs;
				bool thereis;
				robot.getSonarsReadings(thereis,obs);

				if (!thereis)
				{
					cout << "Sonars: NO" << endl;
				}
				else
				{
 					cout << "Sonars: ";
					for (CObservationRange::const_iterator i=obs.sensedData.begin();i!=obs.sensedData.end();++i)
						cout << i->sensedDistance << " ";
					cout << endl;
				}
			}

			if (c=='b')
			{
				double bat;
				robot.getBatteryCharge(bat);
				cout << "Battery: " << bat << endl;
			}

		}


	}
	catch(std::exception &e)
	{
		cerr << e.what() << endl;
		return -1;
	}

	return 0;
}

