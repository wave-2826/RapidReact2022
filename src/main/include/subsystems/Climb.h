// RobotBuilder Version: 4.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// ROBOTBUILDER TYPE: Subsystem - CLIMB

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/DigitalInput.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <rev/CANSparkMax.h>

/**
 * header file for the climb
 * 
 * @author WAVE Robotics 2826
 */
class Climb: public frc2::SubsystemBase {
    
private:
    // It's desirable that everything possible is private except
    // for methods that implement subsystem capabilities
    rev::CANSparkMax *m_climberRoller;
    rev::CANSparkMax *m_hookDeploy;
    frc::DigitalInput *m_isRightGrasshopperDeployed;
    frc::DigitalInput *m_isLeftGrasshopperDeployed;
    rev::CANSparkMax *m_grasshopperDrive;
    rev::CANSparkMax *m_rightGrasshopperDeploy;
    rev::CANSparkMax *m_leftGrasshopperDeploy;
    rev::SparkMaxRelativeEncoder *m_leftGrasshopperEncoder;
    rev::SparkMaxRelativeEncoder *m_rightGrasshopperEncoder;

    bool m_leftState;
    bool m_rightState;
    bool m_grasshopperOverrideState;
    double m_leftPosition;
    double m_rightPosition;
    double m_leftGrasshopperStow;
    double m_rightGrasshopperStow;

public:

    Climb();

    void Periodic() override;
    void SimulationPeriodic() override;

    void SetLeftState(bool state);
    void SetRightState(bool state);
    bool GetLeftState();
    bool GetRightState();
    void SetGrasshopperOverrideState(bool state);
    bool GetGrasshopperOverrideState();

    void SetLeftGrasshopperStow(double position);
    void SetRightGrasshopperStow(double position);
    double GetLeftGrasshopperStow();
    double GetRightGrasshopperStow();
    double GetLeftGrasshopperPosition();
    double GetRightGrasshopperPosition();

    void SetClimberRollerSpeed(double speed);

    void SetHookDeploySpeed(double speed);

    void SetGrasshopperDriveSpeed(double speed);
    void SetGrasshopperDeploySpeed(double leftSpeed, double rightSpeed);

    double GetGrasshopperDriveCurrent();
    double GetClimberRollerCurrent();
    double GetHookDeployCurrent();
    double GetLeftGrasshopperDeployCurrent();
    double GetRightGrasshopperDeployCurrent();

    bool GetRightGrasshopperDeployed();
    bool GetLeftGrasshopperDeployed();

};
