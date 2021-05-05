#include "Camera.hpp"

namespace gps {

    float yawAngle = 0;
    float pitchAngle = 0;

    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraUpDirection = cameraUp;
        this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraRightDirection = glm::cross(cameraFrontDirection, cameraUp);
        //TODO - Update the rest of camera parameters

    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(cameraPosition, cameraTarget, cameraUpDirection);
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        speed = speed * 10;
        switch (direction) {
        case MOVE_FORWARD:
            cameraPosition += cameraFrontDirection * speed;
            cameraTarget += cameraFrontDirection * speed;
            break;
        case MOVE_LEFT:
            cameraPosition += cameraRightDirection * speed;
            cameraTarget += cameraRightDirection * speed;

            break;
        case MOVE_RIGHT:
            cameraPosition -= cameraRightDirection * speed;
            cameraTarget -= cameraRightDirection * speed;

            break;
        case MOVE_BACKWARD:
            cameraPosition -= cameraFrontDirection * speed;
            cameraTarget -= cameraFrontDirection * speed;
            break;

        }
        
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {
        yawAngle += yaw;
        pitchAngle += pitch;

        //rotatie plan orizontal 

        //unghi intern al camerei modificat in urma rotatiei
        cameraTarget.z = cameraPosition.z - cos(glm::radians(yawAngle));
        cameraTarget.x = cameraPosition.x + sin(glm::radians(yawAngle));

        //rotatie plan vertical
        cameraTarget.y = cameraPosition.y - sin(glm::radians(pitchAngle));

        //front direction
        this->cameraFrontDirection = glm::normalize(this->cameraTarget - this->cameraPosition);
        //right direction
        this->cameraRightDirection = glm::normalize(glm::cross(this->cameraFrontDirection, this->cameraUpDirection));
    }
}