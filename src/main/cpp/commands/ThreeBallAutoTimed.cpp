// RobotBuilder Version: 4.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: SequentialCommandGroup - THREE BALL AUTO COMMAND

#include "commands/ThreeBallAutoTimed.h"
#include "frc2/command/ParallelCommandGroup.h"
#include "commands/FrontPunchCommand.h"
#include "commands/SequentialPunch.h"
#include "commands/TransportCommand.h"
#include "commands/DriveCommand.h"
#include "commands/DeployIntakeCommand.h"
#include <iostream>
#include "commands/WaitCommand1.h"
#include <subsystems/Drive.h>
#include <subsystems/Intake.h>
#include <subsystems/Transport.h>
#include <subsystems/Punch.h>
#include "commands/WaitCommand1.h"
#include "commands/DriveHeadingCommand.h"
#include "commands/DriveTurnCommand.h"

/**
 * code for three ball auto using timings
 * timings = not very reliable
 * INITIAL FRAMEOUT - SOME TESTING
 * 
 * @author WAVE Robotics 2826
 */
ThreeBallAutoTimed::ThreeBallAutoTimed(Punch* punch, Drive* drive, Intake* intake, Transport* transport) {

    SetName("ThreeBallAutoTimed");
    
    // VERY RELIABLE 7 BALL AUTO xD
    // std::cout << "ENTER ThreeBallAutoTimed()" << std::endl;
    AddCommands(

                   
        frc2::ParallelCommandGroup
        (
            TransportCommand(intake, transport),
            // DeployIntakeCommand(units::seconds_t(1.0), intake),                    
            FrontPunchCommand(punch),         

            frc2::SequentialCommandGroup
            ( 
                WaitCommand1(units::second_t(0.5)),
                // forward ball 2
                DriveHeadingCommand(-0.70, units::time::second_t(0.75), drive),
                DriveHeadingCommand(-0.25, units::time::second_t(0.2), drive),
                WaitCommand1(units::time::second_t(.5)),

                // turn in place
                DriveTurnCommand(0.5, 106.0f, drive),

                // forward to ball 3
                DriveHeadingCommand(-0.75, units::time::second_t(1.5), drive),
                DriveHeadingCommand(-0.25, units::time::second_t(0.2), drive),
                WaitCommand1(units::time::second_t(0.5)),

                // drive backwards to get closer to hub
                DriveHeadingCommand(0.75, units::time::second_t(0.5), drive),
                DriveHeadingCommand(0.25, units::time::second_t(0.2), drive),

                // turn in place
                DriveTurnCommand(0.5, -80.0f, drive),

                // backwards to hub
                DriveHeadingCommand(0.75, units::time::second_t(1.0), drive),
                DriveHeadingCommand(0.25, units::time::second_t(0.2), drive),
                WaitCommand1(units::time::second_t(0.5)),
                // sequential punch
                SequentialPunch(punch)      
            )          
        )
    );
}

bool ThreeBallAutoTimed::RunsWhenDisabled() const {
    return false;
}