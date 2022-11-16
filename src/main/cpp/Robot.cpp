// RobotBuilder Version: 4.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: Robot.

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>
#include "commands/SequentialPunch.h"
#include "commands/BackPunchCommand.h"
#include "commands/FrontPunchCommand.h"
#include "commands/DriveTurn90Command.h"
#include "commands/DriveStraightCommand.h"
#include <iostream>
#include <chrono>
#include <cameraserver/CameraServer.h>

// Camera Testing
#include <cstdio>
#include <thread>

#include <frc/TimedRobot.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc/imgproc.hpp>

 /////// TESTING CAMERA //////////
void Robot::VisionThread()
{
  // Get the USB camera from CameraServer
  cs::UsbCamera camera = frc::CameraServer::StartAutomaticCapture();
  //Set the Resolution 
  camera.SetResolution(640,480);

  // Get a CvSink. This will capture Mats from the camera
  cs::CvSink cvSink = frc::CameraServer::GetVideo();
  // Setup  CvSource. This will send images back to the dashboard
  cs::CvSource outputStream = 
    frc::CameraServer::PutVideo("Rectangle", 640, 480);
  
  //Mats are very memory expensive. Lets reuse this Mat.
  cv::Mat mat;

  while (true)
  {
    //Tell the CvSink to grab a frame from the camera and put it in the source mt. If there is an error notify the output.
    if (cvSink.GrabFrame(mat) == 0) 
    {
      //Send the output the error.
      outputStream.NotifyError(cvSink.GetError());
      // skip the rest of the current interation
      continue;
    }
    // Put a rectangle on the image
    cv::rectangle(mat, cv::Point(140, 0), cv::Point(500, 480), cv::Scalar(255, 255, 255), 5);

    // Give the output stream a new image to display
    outputStream.PutFrame(mat);
  }
}

void Robot::RobotInit() {
  m_container = RobotContainer::GetInstance();  
  m_backPunchCommand = new BackPunchCommand(&m_container->m_punch);
  m_frontPunchCommand = new FrontPunchCommand(&m_container->m_punch);
  m_sequentialPunch = new SequentialPunch(&m_container->m_punch);
  m_driveTurn90Command = new DriveTurn90Command(0.155, 'L', &m_container->m_drive);
  m_driveStraightCommand = new DriveStraightCommand(0.25, 0.15, -90.0f, &m_container->m_drive);
  m_phase = phase_0_notStarted;
  // set to avoid timeout errors
  m_container->m_drive.arcadeDrive(0, 0);  

  // sets up camera stream (and give default name)
  // frc::CameraServer::StartAutomaticCapture();
  // sets up 2nd camera stream
  // frc::CameraServer::StartAutomaticCapture();

// // We need to run our vision program in a separate thread. If not, our robot program will not run.
    std::thread visionThread(VisionThread);
    visionThread.detach();
  // VisionThread();

  // set initial intake deploy states
  // m_container->m_intake.SetDeployState(false);
  // m_container->m_intake.SetOverrideState(false);

  // set initial climb camera state

}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() 
{ 
  frc2::CommandScheduler::GetInstance().Run();

     /**
     * The method GetColor() returns a normalized color value from the sensor and can be
     * useful if outputting the color to an RGB LED or similar. To
     * read the raw color, use GetRawColor().
     * 
     * The color sensor works best when within a few inches from an object in
     * well lit conditions (the built in LED is a big help here!). The farther
     * an object is the more light from the surroundings will bleed into the 
     * measurements and make it difficult to accurately determine its color.
     */
    frc::Color detectedColor = m_colorSensor.GetColor();

    /**
     * The sensor returns a raw IR value of the infrared light detected.
     */
    double IR = m_colorSensor.GetIR();

    /**
     * Open Smart Dashboard or Shuffleboard to see the color detected by the 
     * sensor.
     */
    frc::SmartDashboard::PutNumber("Red", detectedColor.red);
    frc::SmartDashboard::PutNumber("Green", detectedColor.green);
    frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
    frc::SmartDashboard::PutNumber("IR", IR);

    double colorRatio = detectedColor.blue / detectedColor.red;
    // std::cout << "Color Ratio: " << colorRatio << std::endl;
    // if (colorRatio < 0.75 || colorRatio > 1.25)
    // {
    //   std::cout << "Color found!" << std::endl;
    // }
}

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {
  // reset intake deploy states
  // m_container->m_intake.SetDeployState(false);
  // m_container->m_intake.SetOverrideState(false);

  // set to avoid timeout errors
  m_container->m_drive.arcadeDrive(0, 0);
}

void Robot::DisabledPeriodic() {
  // set to avoid timeout errors
  m_container->m_drive.SetPreviousMoveSpeed(0);
  m_container->m_drive.SetPreviousRotateSpeed(0);
  m_container->m_drive.arcadeDrive(0, 0);
  // std::cout << "ANGLE: " << m_container->m_drive.GetAngle() << std::endl;
}

/**
 * This autonomous runs the autonomous command selected by your {@link
 * RobotContainer} class.
 */
void Robot::AutonomousInit() {
  // set to avoid timeout errors
  m_container->m_drive.ZeroAngle();

  m_container->m_drive.arcadeDrive(0, 0);

  m_autonomousCommand = m_container->GetAutonomousCommand();
  if (m_autonomousCommand != nullptr) {
    m_autonomousCommand->Schedule();
  }
}

void Robot::AutonomousPeriodic() {
  // set to avoid timeout errors
  m_container->m_drive.arcadeDrive(0, 0);
}

void Robot::TeleopInit() {
  // This makes sure that the autonomous stops running when
  // teleop starts running. If you want the autonomous to
  // continue until interrupted by another command, remove
  // this line or comment it out.
  if (m_autonomousCommand != nullptr) {    
    m_autonomousCommand = nullptr;
  }

  // set initial intake deploy states
  // m_container->m_intake.SetDeployState(false);
  // m_container->m_intake.SetOverrideState(false);

  // set initial grasshopper position
  m_container->m_climb.SetLeftGrasshopperStow(m_container->m_climb.GetLeftGrasshopperPosition());
  m_container->m_climb.SetRightGrasshopperStow(m_container->m_climb.GetRightGrasshopperPosition());

  // set initial grasshopper override state
  m_container->m_climb.SetGrasshopperOverrideState(false);

  // m_container->m_drive.ZeroAngle();

  // reset drive position
  m_container->m_drive.ResetDrivePosition(m_container->m_drive.GetDriveEncoderPosition());
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {
  //Implement Stall Timer
  //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  //std::cout << "Current Angle : " << m_container->m_drive.GetAngle() << std::endl;
  // std::cout << "drive position: " << m_container->m_drive.GetDriveEncoderPosition() << std::endl;

  //////////////////  TESTING CURRENT DRAW   /////////////////////////////

  // std::cout << "ClimberRoller: " << m_container->m_climb.GetClimberRollerCurrent() << std::endl;
  // std::cout << "HookDeploy: " << m_container->m_climb.GetHookDeployCurrent() << std::endl;
  // if (m_container->m_climb.GetLeftGrasshopperDeployCurrent() > 10) 
  // {
  //   std::cout << "LeftGrasshopperDeploy current: " << m_container->m_climb.GetLeftGrasshopperDeployCurrent() << std::endl;
  // }
  // if (m_container->m_climb.GetRightGrasshopperDeployCurrent() > 10)
  // {
  // std::cout << "RightGrasshopperDeploy current: " << m_container->m_climb.GetRightGrasshopperDeployCurrent() << std::endl;
  // }

  // std::cout << "LeftGrasshopperPosition: " << m_container->m_climb.GetLeftGrasshopperPosition() << std::endl;
  // std::cout << "RightGrasshopperPosition: " << m_container->m_climb.GetRightGrasshopperPosition() << std::endl;


  // std::cout << "RightFrontDrive: " << m_container->m_drive.GetRightFrontDriveCurrent() << std::endl;
  // std::cout << "RightBackDrive: " << m_container->m_drive.GetRightBackDriveCurrent() << std::endl;
  // std::cout << "LeftFrontDrive: " << m_container->m_drive.GetLeftFrontDriveCurrent() << std::endl;
  // std::cout << "LeftBackDrive: " << m_container->m_drive.GetRightBackDriveCurrent() << std::endl;

  // std::cout << "IntakeRoller: " << m_container->m_intake.GetIntakeRollerCurrent() << std::endl;
  // std::cout << "IntakeDeploy: " << m_container->m_intake.GetIntakeDeployCurrent() << std::endl;

  // std::cout << "BackPuncher: " << m_container->m_punch.GetBackPuncherCurrent() << std::endl;
  // std::cout << "FrontPuncher: " << m_container->m_punch.GetFrontPuncherCurrent() << std::endl;

  // std::cout << "TransporterBelt: " << m_container->m_transport.GetTransporterBeltCurrent() << std::endl;
  // std::cout << "RightIndexer: " << m_container->m_transport.GetRightIndexerCurrent() << std::endl;
  // std::cout << "LeftIndexer: " << m_container->m_transport.GetLeftIndexerCurrent() << std::endl;


 ///////////////////  Transport & Indexer ////////////////////

  double transporterInput = m_container->getOperatorJS()->GetRightTriggerAxis();
  bool toggleY = m_container->getOperatorJS()->GetYButton();
  double singularTransporter = m_container->getOperatorJS()->GetLeftY();
  double singularIndexer = m_container->getOperatorJS()->GetRightY();
  double transporterSpeed = 0;
  double rightIndexerSpeed = 0;
  double leftIndexerSpeed = 0;
  if (fabs(transporterInput) >= 0.07)
  {
    // reverse transporter + indexer
    if (toggleY)
    {
      transporterSpeed = transporterInput;
      rightIndexerSpeed = -transporterInput;
      leftIndexerSpeed = -transporterInput;
    }
    // set transporter + indexer
    else
    {
      transporterSpeed = -transporterInput;
      rightIndexerSpeed = transporterInput;
      leftIndexerSpeed = transporterInput;
    }
  }
  else
  {
    // set transporter individually
    if (fabs(singularTransporter) >= 0.07)
    {
      transporterSpeed = singularTransporter;
    }
    // set indexers individually
    if (fabs(singularIndexer) >= 0.07)
    {
      leftIndexerSpeed = -singularIndexer;
      rightIndexerSpeed = -singularIndexer;
    }
  }
  m_container->m_transport.SetTransporterBeltSpeed(transporterSpeed);
  m_container->m_transport.SetIndexerSpeed(leftIndexerSpeed, rightIndexerSpeed);


//////////////////  Intake  /////////////////////////////

  double intakeRollerIn = m_container->getOperatorJS()->GetLeftTriggerAxis();
  double intakeRollerSpeed = 0;
  if (fabs(intakeRollerIn) >= 0.07) 
  {
    // reverse intake
    if (toggleY)
    {
      intakeRollerSpeed = -intakeRollerIn;
    }
    // set intake
    else
    {
      intakeRollerSpeed = intakeRollerIn;
    }
  }
  m_container->m_intake.SetIntakeRoller(intakeRollerSpeed);

  bool deployHook = m_container->getOperatorJS()->GetRightBumper();
  bool stowHook = m_container->getOperatorJS()->GetLeftBumper();
  // bool intakeOverride = m_container->getOperatorJS()->GetStartButton();
  bool hookMode = m_container->getOperatorJS()->GetBackButton();
  // bool isDeployed = m_container->m_intake.GetIntakeDeployed();
  // bool deployState = m_container->m_intake.GetDeployState();
  // bool overrideState = m_container->m_intake.GetOverrideState();
  // double deployPosition = m_container->m_intake.GetIntakeDeployPosition();
  // double intakeDeploySpeed = 0;

  // TESTING PRINTOUTS
  // std::cout << "DEPLOY SENSOR: " << isDeployed << std::endl;
  // std::cout << "deploy state: " << deployState << std::endl;
  // std::cout << "stopping condition " << fabs(deployPosition - m_container->m_intake.GetTriggeredPosition()) << std::endl; 
  // if (deployState)
  // {  
  //   std::cout << "stopping condition " << fabs(deployPosition - m_container->m_intake.GetTriggeredPosition()) << std::endl; 
  // }
  
  // check NOT hook mode
  // if (!hookMode)
  // {
  //   if (intakeOverride)
  //   {
  //     m_container->m_intake.SetOverrideState(true);
  //   }
  //   // OVERRIDE state = true
  //   if (overrideState)
  //   {
  //     if (deployIntake)
  //     {
  //       intakeDeploySpeed = 0.5;
  //     }
  //   }
  //   // OVERRIDE state = false
  //   else
  //   {
  //     // std::cout << "override state false " << std::endl;
  //     // check if sensor tripped while deploying
  //     if (deployIntake && isDeployed)
  //     {
  //       m_container->m_intake.SetDeployState(true);
  //       m_container->m_intake.SetTriggeredPosition(deployPosition);
  //     }
  //     // reset deploy state
  //     if (stowIntake && isDeployed)
  //     {
  //       m_container->m_intake.SetDeployState(false);
  //     }
  //     // if deploying and deploy state true
  //     if (deployIntake && deployState)
  //     {
  //       if (fabs(deployPosition - m_container->m_intake.GetTriggeredPosition()) < 13)
  //       {
  //         intakeDeploySpeed = 1.0;
  //       }
  //       else if (fabs(deployPosition - m_container->m_intake.GetTriggeredPosition()) < 22)
  //       {
  //         intakeDeploySpeed = 0.2;
  //       }
  //       else
  //       {
  //         intakeDeploySpeed = 0;   
  //       }
  //     }
  //     else if (deployIntake && !deployState)
  //     {
  //       intakeDeploySpeed = 1.0;
  //     }
  //   }
  //   // stow intake
  //   if (stowIntake)
  //   {
  //     intakeDeploySpeed = -1.0;
  //   }
  // }
  // m_container->m_intake.SetIntakeDeploy(intakeDeploySpeed);


//////////////////  Climber   /////////////////////////////

  // double climbSpeed = m_container->getDriverJS()->GetRightTriggerAxis();
  double climbSpeed = m_container->getDriverJS()->GetLeftTriggerAxis();
  if (fabs(climbSpeed) < 0.07)
  {
    climbSpeed = 0;
  }
  // set front and back climb motors
  m_container->m_climb.SetGrasshopperDriveSpeed(-climbSpeed);
  m_container->m_climb.SetClimberRollerSpeed(-climbSpeed);

  bool grasshopperDeploy = m_container->getDriverJS()->GetYButton();
  bool grasshopperStow = m_container->getDriverJS()->GetXButton();
  // bool grasshopperStowOverride = m_container->getDriverJS()->GetBackButtonPressed();
  // bool grasshopperStowOverrideReleased = m_container->getDriverJS()->GetBackButtonReleased();
  // bool grasshopperOverrideState = m_container->m_climb.GetGrasshopperOverrideState();
  double rightGrasshopperDeploySpeed = 0;
  double leftGrasshopperDeploySpeed = 0;
  if (grasshopperDeploy)
  {
    leftGrasshopperDeploySpeed = 0.5;
    rightGrasshopperDeploySpeed = 0.5;
  }
  else if (grasshopperStow)
  {
    leftGrasshopperDeploySpeed = -0.3;
    rightGrasshopperDeploySpeed = -0.3;
    // // override = true
    // if (grasshopperStowOverride)
    // { 
    //     std::cout << "GRASSHOPPER STOW OVERRIDE" << std::endl;
    //     leftGrasshopperDeploySpeed = -0.3;
    //     rightGrasshopperDeploySpeed = -0.3;
    //     m_container->m_climb.SetGrasshopperOverrideState(true);
    // }
    // // override just released
    // else if (grasshopperStowOverrideReleased && grasshopperOverrideState)
    // {
    //   std::cout << "OVERRIDE RELEASED" << std::endl;
    //   m_container->m_climb.SetLeftGrasshopperStow(m_container->m_climb.GetLeftGrasshopperPosition());
    //   m_container->m_climb.SetRightGrasshopperStow(m_container->m_climb.GetRightGrasshopperPosition());
    //   m_container->m_climb.SetGrasshopperOverrideState(false);
    // }
    // // override = false
    // else
    // {
    //   std::cout << "OVERRIDE FALSE" << std::endl;
    //   if (fabs(m_container->m_climb.GetLeftGrasshopperStow() - m_container->m_climb.GetLeftGrasshopperPosition()) > 20)
    //   {
    //     leftGrasshopperDeploySpeed = -0.3;
    //   }
    //   else 
    //   {
    //     leftGrasshopperDeploySpeed = 0;
    //   }
    //   if (fabs(m_container->m_climb.GetRightGrasshopperStow() - m_container->m_climb.GetRightGrasshopperPosition()) > 20)
    //   {
    //     rightGrasshopperDeploySpeed = -0.3;
    //   }
    //   else 
    //   {
    //     rightGrasshopperDeploySpeed = 0;
    //   }
    // }
  }
  // std::cout << "stow state: " << m_container->m_climb.GetLeftGrasshopperStow() << std::endl;
  // std::cout << "grasshopper pos:  " << m_container->m_climb.GetLeftGrasshopperPosition() << std::endl;
  // std::cout << "distance: " << fabs(m_container->m_climb.GetLeftGrasshopperStow() - m_container->m_climb.GetLeftGrasshopperPosition()) << std::endl;
  // std::cout << "STOW REACHED: " << (fabs(m_container->m_climb.GetLeftGrasshopperStow() - m_container->m_climb.GetLeftGrasshopperPosition()) > 20) << std::endl;
  // set climb deploy motors
  m_container->m_climb.SetGrasshopperDeploySpeed(leftGrasshopperDeploySpeed, rightGrasshopperDeploySpeed);

  double hookDeploySpeed = 0;
  if (hookMode)
  {
    if (deployHook && !m_container->m_climb.GetHookDeploySensor())
    { 
      hookDeploySpeed = 1.0;
    }
    else if (stowHook)
    {
      hookDeploySpeed = -1.0;
    }
  }
  // set hook deploy motor
  m_container->m_climb.SetHookDeploySpeed(hookDeploySpeed);

  //////////////////  Drive   /////////////////////////////
  
  // BASIC DRIVE 
  double moveInput = m_container->getDriverJS()->GetLeftY();
  double rotateInput = m_container->getDriverJS()->GetRightX();
  bool alignClimb = m_container->getDriverJS()->GetAButton();
  // double cutSpeed = m_container->getDriverJS()->GetLeftTriggerAxis();
  double cutSpeed = m_container->getDriverJS()->GetRightTriggerAxis();
  double moveInputSpeed = 0;
  double rotateInputSpeed = 0;
  // we are NOT climbing
  if (fabs(moveInput) >= 0.07)
  {
    moveInputSpeed = moveInput;  
  }
  if (fabs(rotateInput) >= 0.07)
  {
    rotateInputSpeed = rotateInput;
  }
  if (cutSpeed >= 0.07)
  {
    moveInputSpeed = 0.75 * moveInput;
    rotateInputSpeed = 0.75 * rotateInput;
  }
  // we ARE climbing
  if (fabs(climbSpeed) >= 0.07)
  {
    // moveInputSpeed = 0.5;
    // moveInputSpeed = 0;
    // rotateInputSpeed = 0;
  }  

  //////////////////  Climber Align  /////////////////////////////
// ************
  if (alignClimb)
  {
    // static int phase = phase_0_notStarted;
    // Robot::m_phase = phase_0_notStarted;
    float angle_correction = -((Robot::m_container->m_drive.GetAngle() - (-90.0)) * 0.13f );
    // std::cout << "Phase: " << Robot::m_phase << std::endl;
    switch(Robot::m_phase)
    {
      case phase_0_notStarted:
        // begin alignment
        // std::cout << "Entered Phase 0" << std::endl;
        Robot::m_phase = phase_2_sensorsFound;
        break;
      case phase_1_sensorsNotFound:
        // look for sensor
        break;
      case phase_2_sensorsFound:
        // sensor found, turn 90 degrees
        // std::cout << "Entered Phase 2" << std::endl;
        m_driveTurn90Command->Schedule();
        Robot::m_phase = phase_3_aligned;
        break;
      case phase_3_aligned:
        // drive straight
        // std::cout << "Angle" << Robot::m_container->m_drive.GetAngle() << std::endl;
        // std::cout << "Angle Correction: " << angle_correction << std::endl; 
        Robot::m_container->m_drive.arcadeDrive(0.25, angle_correction);
        break;
      default:
        Robot::m_phase = phase_0_notStarted;
        break;
    }
  }
  else 
  {
    // std::cout << "CLIMB ALIGN END" << std::endl;
    // set drive motors
    Robot::m_container->m_drive.arcadeDrive(Robot::m_container->m_drive.LerpDriveSpeed(Robot::m_container->m_drive.GetPreviousMoveSpeed(), moveInputSpeed, 0.08f),
      Robot::m_container->m_drive.LerpDriveSpeed(Robot::m_container->m_drive.GetPreviousRotateSpeed(), rotateInputSpeed, 0.1f)
    );
    Robot::m_container->m_drive.SetPreviousMoveSpeed(Robot::m_container->m_drive.LerpDriveSpeed(Robot::m_container->m_drive.GetPreviousMoveSpeed(), moveInputSpeed, 0.08f));
    Robot::m_container->m_drive.SetPreviousRotateSpeed(Robot::m_container->m_drive.LerpDriveSpeed(Robot::m_container->m_drive.GetPreviousRotateSpeed(), rotateInputSpeed, 0.1f));
    Robot::m_phase = phase_0_notStarted;
  }
  
//////////////////  Puncher   /////////////////////////////

  // run the BACK punch command - B
  // aka INNER punch
  // if (m_container->getOperatorJS()->GetBButton())
  // {
  //   m_backPunchCommand->Schedule(); 
  // }

  // run the FRONT punch command - X
  // aka OUTER punch
  // if (m_container->getOperatorJS()->GetXButton())
  // {
  //   m_frontPunchCommand->Schedule(); 
  // }
  

  // run the SEQUENTIAL punch command - A
  if (m_container->getOperatorJS()->GetAButton())
  {
    m_sequentialPunch->Schedule(); 
  }

  // MANUALLY RUN PUNCHERS - currently unused
  double punchFront = 0;
  double punchBack = 0;
  // // // MANUALLY run both punch = A
  // // if(m_container->getOperatorJS()->GetXButton())
  // // {
  // //   punchFront = 0.8;
  // //   punchBack = 0.8;
  // // }
  // MANUALLY run individual FRONT (outer) punch = OPERATOR B
  if (m_container->getOperatorJS()->GetBButton())
  {
    punchFront = 0.8;
  }
  // individual BACK (inner) punch = Operator X
  if (m_container->getOperatorJS()->GetXButton())
  {
    punchBack = 0.8;
  }
  m_container->m_punch.SetFrontPuncherSpeed(punchFront);
  m_container->m_punch.SetBackPuncherSpeed(punchBack);

  //////////////////// CAMERA STREAM //////////////////////////////

  // if (true) {
  //   // sets up 2nd camera stream
  //   frc::CameraServer::StartAutomaticCapture();
  // }
} // end TeleopPeriodic

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
