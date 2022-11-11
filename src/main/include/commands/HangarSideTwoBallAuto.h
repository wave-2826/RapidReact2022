// RobotBuilder Version: 4.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: SequentialCommandGroup - HANGAR SIDE TWO BALL AUTO COMMAND

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/CommandBase.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "subsystems/Punch.h"
#include "subsystems/Drive.h"
#include "subsystems/Intake.h"
#include "subsystems/Transport.h"

/**
 * header file for HANGAR SIDE two ball auto command
 *
 * @author WAVE Robotics 2826
 */
class HangarSideTwoBallAuto
    : public frc2::CommandHelper<frc2::SequentialCommandGroup, HangarSideTwoBallAuto> {

public:
    
    HangarSideTwoBallAuto(Punch* punch, Drive* drive, Intake* intake, Transport* transport);
    HangarSideTwoBallAuto(){};

    bool RunsWhenDisabled() const override;

private:

};

