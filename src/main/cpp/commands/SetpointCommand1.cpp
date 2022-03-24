// RobotBuilder Version: 4.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: SetpointCommand.


#include "commands/SetpointCommand1.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

#include "commands/SetpointCommand1.h"

SetpointCommand1::SetpointCommand1(double setpoint, Drive* m_drive) :
    m_setpoint(setpoint),
m_drive(m_drive)
{

    // Use AddRequirements() here to declare subsystem dependencies
    // eg. AddRequirements(m_Subsystem);
    SetName("SetpointCommand1");
    AddRequirements({m_drive});

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

}

// Called just before this Command runs the first time
void SetpointCommand1::Initialize() {
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZE
m_drive->Enable();
m_drive->SetSetpoint(m_setpoint);

        // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZE
}

// Called repeatedly when this Command is scheduled to run
void SetpointCommand1::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool SetpointCommand1::IsFinished() {
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ISFINISHED
    return m_drive->GetController().AtSetpoint();

        // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ISFINISHED
}

// Called once after isFinished returns true
void SetpointCommand1::End(bool interrupted) {

}
