/************************************************************************/
/*!
\file	  Shader.h
\author Martin Angulo Umaran
\par    email: marlock97@gmail.com
\par    Game Engine
\date	  05/09/2020
\brief  Shader class declaration.

\log    05/09/2020 -> Initial version.
*/
/************************************************************************/
#include "Camera.h"

namespace Engine
{
  RTTI_IMPL(Camera, IBase);

  //Camera contructor with vectors
  Camera::Camera(vec3 position, vec3 up, f32 yaw, f32 pitch) : camForward_(vec3(0.0f, 0.0f, -1.0f)), movementSpeed_(SPEED), mouseSensitivity_(SENSITIVITY), zoom_(ZOOM) {
    camPosition_ = position;
    worldUp_ = up;
    yaw_ = yaw;
    pitch_ = pitch;
    UpdateCameraVectors();
  }

  // constructor with scalar values
  Camera::Camera(f32 posX, f32 posY, f32 posZ, f32 upX, f32 upY, f32 upZ, f32 yaw, f32 pitch) : camForward_(vec3(0.0f, 0.0f, -1.0f)), movementSpeed_(SPEED), mouseSensitivity_(SENSITIVITY), zoom_(ZOOM) {
    camPosition_ = vec3(posX, posY, posZ);
    worldUp_ = vec3(upX, upY, upZ);
    yaw_ = yaw;
    pitch_ = pitch;
    UpdateCameraVectors();
  }

  // returns the view matrix calculated using Euler Angles and the LookAt Matrix
  mat4 Camera::GetViewMatrix() {
    return glm::lookAt(camPosition_, camPosition_ + camForward_, camUp_);
  }

  // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
  void Camera::ProcessKeyboard(CameraMovement direction, f32 deltaTime) {
    f32 velocity = movementSpeed_ * deltaTime;
    if (direction == CameraMovement::FORWARD)
      camPosition_ += camForward_ * velocity;
    if (direction == CameraMovement::BACKWARD)
      camPosition_ -= camForward_ * velocity;
    if (direction == CameraMovement::RIGHT)
      camPosition_ += glm::normalize(glm::cross(camForward_, camUp_)) * velocity;
    if (direction == CameraMovement::LEFT)
      camPosition_ -= glm::normalize(glm::cross(camForward_, camUp_)) * velocity;
    if (direction == CameraMovement::UP)
      camPosition_ += camUp_ * velocity;
    if (direction == CameraMovement::DOWN)
      camPosition_ -= camUp_ * velocity;
  }

  // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
  void Camera::ProcessMouseMovement(f32 xoffset, f32 yoffset, bool constrainPitch) {
    xoffset *= mouseSensitivity_;
    yoffset *= mouseSensitivity_;

    yaw_ += xoffset;
    pitch_ += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
      if (pitch_ > 89.0f)
        pitch_ = 89.0f;
      if (pitch_ < -89.0f)
        pitch_ = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    UpdateCameraVectors();
  }

  // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
  void Camera::ProcessMouseScroll(f32 yoffset) {
    zoom_ -= (f32)yoffset;
    if (zoom_ < 1.0f)
      zoom_ = 1.0f;
    if (zoom_ > 45.0f)
      zoom_ = 45.0f;
  }

  // calculates the front vector from the Camera's (updated) Euler Angles
  void Camera::UpdateCameraVectors() {
    // calculate the new Front vector
    vec3 front;
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    camForward_ = glm::normalize(front);
    // also re-calculate the Right and Up vector
    camRigth_ = glm::normalize(glm::cross(camForward_, worldUp_));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    camUp_ = glm::normalize(glm::cross(camRigth_, camForward_));
  }
}