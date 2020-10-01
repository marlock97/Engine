/************************************************************************/
/*!
\file	  camera.h
\author Martin Angulo Umaran
\par    email: marlock97@gmail.com
\par    Game Engine
\date	  05/09/2020
\brief  Camera class declaration.

\log    01/10/2020 -> Initial version.
*/
/************************************************************************/
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Core/Base.h"
#include "../Core/Rtti.h"

// Default camera values
const f32 YAW = -90.0f;
const f32 PITCH = 0.0f;
const f32 SPEED = 3.5f;
const f32 SENSITIVITY = 0.05f;
const f32 ZOOM = 45.0f;

namespace Engine 
{
  class Camera : public IBase
  {
    RTTI_DECL;  
    // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
    enum class CameraMovement {
      FORWARD,
      BACKWARD,
      LEFT,
      RIGHT,
      UP,
      DOWN
    };

  public:
    //Camera contructor with vectors
    Camera(vec3 position = vec3(0.0f, 0.0f, 0.0f), vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), f32 yaw = YAW, f32 pitch = PITCH);
    // constructor with scalar values
    Camera(f32 posX, f32 posY, f32 posZ, f32 upX, f32 upY, f32 upZ, f32 yaw, f32 pitch);
    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    mat4 GetViewMatrix();
    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(CameraMovement direction, f32 deltaTime);
    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(f32 xoffset, f32 yoffset, bool constrainPitch = true);
    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(f32 yoffset);

    //Getters/Setters
    vec3 GetCamPosition() { return camPosition_; }
    vec3 GetCamForward() { return camForward_; }
    vec3 GetCamUp() { return camUp_; }
    vec3 GetGamRigth() { return camRigth_; }
    vec3 GetWorldUp() { return worldUp_; }
    f32 GetYaw() { return yaw_; }
    f32 GetPitch() { return pitch_; }
    f32 GetMovementSpeed() { return movementSpeed_; }
    f32 GetMouseSensitivity() { return mouseSensitivity_; }
    f32 GetZoom() { return zoom_; }

  private:
    //Camera attributes
    vec3 camPosition_;
    vec3 camForward_;
    vec3 camUp_;
    vec3 camRigth_;
    vec3 worldUp_;
    //Euler angles
    f32 yaw_;
    f32 pitch_;
    //Camera options
    f32 movementSpeed_;
    f32 mouseSensitivity_;
    f32 zoom_;

    // calculates the front vector from the Camera's (updated) Euler Angles
    void UpdateCameraVectors();
  };
}