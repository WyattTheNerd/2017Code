#include <iostream>
#include <memory>
#include <string>

#include <CameraServer.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <DriverStation.h>
#include <Dashboard.h>

void Dashboard::DashboardInit(){
	//if no camera / you should make a camera / so drivers can see 
	if(cam.GetName() != "Camera"){
		//create camera / that automatically / sends pics to dashboard
		cam = CameraServer::GetInstance()->StartAutomaticCapture("Camera", "/dev/video0");
		//set the camera / brightness twenty five percent / so it's not too bright 
		cam.SetBrightness(25);
		//set resolution / or pixels on the dashboard / in four eighty p 
		cam.SetResolution(640, 480);
	}
}

int Dashboard::AutoSelect(){
	//create a pointer / it points to driver station / and gives us data
	DriverStation &drive = DriverStation::GetInstance();
	//get button values / it gets them from the dashboard / for all of these things
	bool hopperOnly = SmartDashboard::GetBoolean("DB/Button 0", false);
	bool shootOnly = SmartDashboard::GetBoolean("DB/Button 1", false);
	bool gearAndHopper = SmartDashboard::GetBoolean("DB/Button 2", false);
	bool disable = SmartDashboard::GetBoolean("DB/Button 3", false);
	double position = SmartDashboard::GetNumber("DB/Slider 0", 2.5);
	int positionNumber = 0;
	//if the top slider / is in leftmost position / set position one
	if(position <= 1.666){
		positionNumber = 1;
	}
	//if the top slider / is in center position / set position two
	else if(position > 1.666 && position < 3.333){
		positionNumber = 2;
	}
	//if the top slider / is in rightmost position / set position three
	else if(position >= 3.333){
		positionNumber = 3;
	}
	//if slider is screwed / return value of zero / so nothing crashes
	else{
		return 0;
	}

	//if autonomous / happens to be disabled / it returns zero 
	if(disable == true){
		return 0;
	}
	//if autonomous / wants to do hopper only / run through hopper code
	else if(hopperOnly == true){
		if(drive.GetAlliance() == DriverStation::Alliance::kRed){
			if(positionNumber == 1){
				return 7;
			}
			else if(positionNumber == 2){
				return 8;
			}
			else if(positionNumber == 3){
				return 9;
			}
		}
		else if(drive.GetAlliance() == DriverStation::Alliance::kBlue){
			if(positionNumber == 1){
				return 10;
			}
			else if(positionNumber == 2){
				return 11;
			}
			else if(positionNumber == 3){
				return 12;
			}
		}
	}
	//if autonomous / does include shooting functions / run through those options
	else if(shootOnly == true){
		if(drive.GetAlliance() == DriverStation::Alliance::kRed){
			return 19;
		}
		else if(drive.GetAlliance() == DriverStation::Alliance::kBlue){
			return 20;
		}
	}
	//if gear and hopper / will both be necessary / use these six options
	else if(gearAndHopper == true){
		if(drive.GetAlliance() == DriverStation::Alliance::kRed){
			if(positionNumber == 1){
				return 13;
			}
			else if(positionNumber == 2){
				return 14;
			}
			else if(positionNumber == 3){
				return 15;
			}
		}
		else if(drive.GetAlliance() == DriverStation::Alliance::kBlue){
			if(positionNumber == 1){
				return 16;
			}
			else if(positionNumber == 2){
				return 17;
			}
			else if(positionNumber == 3){
				return 18;
			}
		}
	}
	//these six are default / we place a gear and then stop / use these most often
	else{
		if(drive.GetAlliance() == DriverStation::Alliance::kRed){
			if(positionNumber == 1){
				return 1;
			}
			else if(positionNumber == 2){
				return 2;
			}
			else if(positionNumber == 3){
				return 3;
			}
		}
		else if(drive.GetAlliance() == DriverStation::Alliance::kBlue){
			if(positionNumber == 1){
				return 4;
			}
			else if(positionNumber == 2){
				return 5;
			}
			else if(positionNumber == 3){
				return 6;
			}
		}
	}
	//the default return / if none of others trigger / it returns zero
	return 0;
}



