#include "Camera.hpp"

#include <glm/ext.hpp>

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include <iostream>

using namespace gl;

constexpr float ZOOM_SENSITIVITY{0.05f};

namespace visus
{
    namespace graphics
    {
        Camera::Camera(const glm::vec2& viewport)
            : _viewport{viewport}
        {
            update();
        }

        Camera::Camera(const glm::vec3 position, const glm::vec3 target, float fov,
                       const glm::vec2& viewport)
            : _eye{position},
              _lookAt{target}
        {
            _fov = fov;
            _viewport = viewport;
            update();
        }

        // Compute the view and projection matrices
        void Camera::update()
        {
            _viewMat = glm::lookAt(_eye, _lookAt, _upVec);
            _projectionMat =
                glm::perspective(glm::radians(_fov), _viewport[0] / _viewport[1], _near, _far);
        }

        glm::vec3 Camera::screenToArcball(glm::ivec2 point) const
        {
            // Screen -> NDC
            // NOTE(abi): in screen space the origin is at the top-left corner (Y+ down),
            // so we need to flip it.
            glm::vec2 pointNDC{
                2.f * static_cast<float>(point.x) / static_cast<float>(_viewport[0]) - 1.f,
                -2.f * static_cast<float>(point.y) / static_cast<float>(_viewport[1]) + 1.f};

            // NDC -> Arcball
            // Project onto the arcball's hemisphere
            glm::vec3 pointArcball{pointNDC, 0.f};

            // Within unit circle (euclidean distance)
            if (float lengthSq = glm::dot(pointNDC, pointNDC); lengthSq <= 1.f)
            {
                pointArcball.z = sqrt(1.f - lengthSq);
                return pointArcball;
            }

            // Outside (circle boundary -> sphere rim)
            pointArcball = glm::normalize(pointArcball);
            return pointArcball;
        }

        void Camera::rotate(const double& x, const double& y)
        {
            glm::vec2 prev{_cursor.x, _cursor.y};
            glm::vec2 curr{x, y};

            if (prev != curr)
            {
                glm::vec3 a = screenToArcball(prev);
                glm::vec3 b = screenToArcball(curr);

                float angle = glm::acos(glm::max(-1.f, glm::min(1.f, glm::dot(a, b))));
                glm::vec3 axis = glm::cross(a, b);

                glm::vec4 transformedAxis = glm::inverse(_viewMat) * glm::vec4(axis, 0.0);
                _viewMat = glm::rotate(_viewMat, angle, glm::vec3(transformedAxis));
            }
        }

        // NOTE(abi): instead of translating the camera we modify the FoV (lens-like zoom).
        // This way we can't intersect the volume.
        void Camera::zoom(const float factor)
        {
            _fov = glm::clamp(_fov - (factor * ZOOM_SENSITIVITY), 1.f, 90.f);
            _projectionMat =
                glm::perspective(glm::radians(_fov), _viewport[0] / _viewport[1], _near, _far);
        }

        void Camera::onMButtonPress(const int button, const bool action)
        {
            switch (button)
            {
            case 0: // LMB
                std::cout << "ROTATING" << std::endl;
                _rotating = action;
                break;
            case 1: // RMB
                std::cout << "ZOOMING" << std::endl;
                _zooming = action;
                break;
            default:
                break;
            }
        }

        void Camera::onCursorMove(const double& x, const double& y)
        {
            if (_rotating)
            {
                rotate(x, y);
            }
            if (_zooming)
            {
                zoom(static_cast<float>(y));
            }

            // Cache current position for next rotation
            _cursor.x = x;
            _cursor.y = y;
        }

        void Camera::onScroll([[maybe_unused]] const double& xOffset, const double& yOffset)
        {
            zoom(static_cast<float>(yOffset));
        }
    } // namespace graphics
} // namespace visus
