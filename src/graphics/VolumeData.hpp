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
            // NIfTI - designed for fMRI neuroimaging
            // https://paulbourke.net/dataformats/nii/ (brief)
            // https://brainder.org/2012/09/23/the-nifti-file-format/ (in-depth)
            std::string _datasetPath{"dat/hand.nii.gz"};
            nifti_image* _images{nullptr};
            nifti_1_header* _header{nullptr};
            bool _printHeader{false};

            float _averageIntensity{0.f};
            float _maxIntensity{0.f};

            std::vector<unsigned short> _dimensions{0, 0, 0};
            glm::mat4 _modelMat{1.f};
            glm::vec3 _scale{1.f};

            void findValuesOfInterest();

        public:
            VolumeData();
            void loadDataset();

            inline unsigned short* getData() const
            {
                return static_cast<unsigned short*>(_images->data);
            }

            inline float getAverageIntensityValue() const
            {
                return _averageIntensity;
            }

            inline float getMaximumIntensityValue() const
            {
                return _maxIntensity;
            }

            inline std::vector<unsigned short> getDimensions() const
            {
                return _dimensions;
            }

            inline glm::mat4 getModelMatrix() const
            {
                return _modelMat;
            }
        };
    } // namespace graphics
} // namespace visus
