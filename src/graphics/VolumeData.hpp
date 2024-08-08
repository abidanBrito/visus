#pragma once

#include <nifti/nifti1_io.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

// TODO(abi): add support for other formats (vtk, raw/pvm, dicom).
namespace visus
{
    namespace graphics
    {
        class VolumeData
        {
        private:
            std::vector<unsigned short> _dimensions{0, 0, 0};

            // IMPORTANT(abi): the model matrix is essential to transform the volume in the
            // fragment, as we need to define the volume's origin point.
            glm::mat4 _modelMat{glm::mat4(1.f)};
            glm::vec3 _scaleVec{glm::vec3(1.f)};

            // NIfTI - designed for fMRI neuroimaging
            // https://paulbourke.net/dataformats/nii/ (brief)
            // https://brainder.org/2012/09/23/the-nifti-file-format/ (in-depth)
            std::string _datasetPath{"res/volumes/hand.nii.gz"};
            bool _printHeader{false};
            nifti_1_header* _header{nullptr};
            nifti_image* _image{nullptr};

            // float _averageIntensity{0.f};
            // float _maxIntensity{0.f};

            void parseNifti();
            // void findValuesOfInterest();

        public:
            VolumeData();

            inline std::vector<unsigned short> getDimensions() const
            {
                return _dimensions;
            }

            inline glm::mat4 getModelMatrix() const
            {
                return _modelMat;
            }

            inline unsigned short* getData() const
            {
                return static_cast<unsigned short*>(_image->data);
            }

            // inline float getAverageIntensityValue() const
            // {
            //     return _averageIntensity;
            // }

            // inline float getMaximumIntensityValue() const
            // {
            //     return _maxIntensity;
            // }
        };
    } // namespace graphics
} // namespace visus
