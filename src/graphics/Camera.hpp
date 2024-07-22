#pragma once

#include <glm/glm.hpp>

// TODO(abi): add panning and cmapl to avoid rotation from outside the window.
namespace visus
{
    namespace graphics
    {
        // BUG(abi): regardless of initialization type it yields compiler errors...
        // NOTE(abi): check out the references below for more information.
        // https://photographylife.com/equivalent-focal-length-and-field-of-view
        // http://www.songho.ca/opengl/gl_projectionmatrix.html#fov
        // struct CameraParams
        // {
        //     // View frustum & vertical FoV
        //     float near{0.1}, far{1000.0}, fov{40.0};
        // };

        // TODO(abi): use this to add panning (and zooming) using click+drag.
        // Maybe make an enum instead?
        struct CameraState
        {
            bool rotating{false}; // LMB
            bool panning{false};  // RMB
            bool zooming{false};  // Scroll wheel
        };

        struct CursorPosition
        {
            double x{0.0}, y{0.0};
        };

        class Camera
        {
        private:
            // CameraParams _cameraParams;
            float _near, _far, _fov;

            CursorPosition _cursor;
            glm::vec2 _viewport;

            glm::mat4 _viewMat;
            glm::mat4 _projectionMat;

            glm::vec3 _eye{glm::vec3(0.f, 0.f, 2.f)};   // Look from (eye/camera position)
            glm::vec3 _lookAt{glm::vec3(0.f)};          // Look to (where the camera points to)
            glm::vec3 _upVec{glm::vec3(0.f, 1.f, 0.f)}; // Camera orientation

            bool _rotating{false}; // LMB
            bool _zooming{false};  // RMB

            glm::vec3 screenToArcball(glm::ivec2 point) const;
            void rotate(const double& x, const double& y);
            void zoom(const float factor);
            void update();

        public:
            Camera(const glm::vec2& viewport);
            Camera(const glm::vec3 position, const glm::vec3 target, const float fov,
                   const glm::vec2& viewport);

            void onMButtonPress(const int button, const bool action);
            void onCursorMove(const double& x, const double& y);
            void onScroll(const double& xOffset, const double& yOffset);

            inline glm::mat4 getViewMatrix() const
            {
                return _viewMat;
            }

            inline glm::mat4 getProjectionMatrix() const
            {
                return _projectionMat;
            }
        };
    } // namespace graphics
} // namespace visus
