#include "CustomServo.h"
#include <Arduino.h>

CustomServo::CustomServo()
{
}

CustomServo::~CustomServo()
{
}

void CustomServo::Setup(int servoPin, float angle, int pwmChannel)
{
  this->servoDutyCycle = ConvertAngleToDutyCycle(angle);
  this->PWMChannel = pwmChannel;
  this->servoPin = servoPin;
  ledcSetup(pwmChannel, this->PWMFreq, this->PWMResolution);
  ledcAttachPin(servoPin, pwmChannel);
  ledcWrite(pwmChannel, servoDutyCycle);
}

void CustomServo::ChangeServoAngleLinear(float newServoAngle)
{
  const float newDutyCycle = ConvertAngleToDutyCycle(newServoAngle);
  const float oldDutyCycle = this->servoDutyCycle;
  const float dutyCycleIncrement = 0.001;

  if (this->servoDutyCycle < newDutyCycle)
  {
    for (float i = this->servoDutyCycle; i < newDutyCycle; i += 0.0001)
    {
      this->servoDutyCycle = i;
      ledcWrite(this->PWMChannel, i);
      // delay(1);
    }
  }
  else if (this->servoDutyCycle > newDutyCycle)
  {
    for (float i = this->servoDutyCycle; i > newDutyCycle; i -= 0.0001)
    {
      this->servoDutyCycle = i;
      ledcWrite(this->PWMChannel, i);
      // delay(1);
    }
  }
}

void CustomServo::ChangeServoAngle(float newServoAngle)
{
  const float newDutyCycle = ConvertAngleToDutyCycle(newServoAngle);
  this->servoDutyCycle = newDutyCycle;
  ledcWrite(this->PWMChannel, this->servoDutyCycle);
}

float CustomServo::ConvertAngleToDutyCycle(float angle)
{
  const float input_min = 0;
  const float input_max = 180;

  const float output_min = 5;
  const float output_max = 32;

  float output = ((angle - input_min) / (input_max - input_min)) * (output_max - output_min) + output_min;

  return output;
}
