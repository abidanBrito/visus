#include "VolumeData.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <iostream>

namespace visus
{
    namespace graphics
    {
        VolumeData::VolumeData()
        {
            loadDataset();
            findValuesOfInterest();

            // IMPORTANT(abi): it's essential to transform the volume in the fragment. We need to
            // define the volume's origin point. I'm not too sure how to determine this per-volume,
            // maybe take a look at the header.
            _modelMat = glm::translate(_modelMat, glm::vec3(-0.5f));

            // Volume scale (defined in header metadata)
            _modelMat = glm::scale(_modelMat, glm::vec3(_scale.x, _scale.y, _scale.z));

            // After scaling we obviously need to shift the volume to recenter it
            _modelMat = glm::translate(
                _modelMat, glm::vec3((1.f - _scale.x), (1.f - _scale.y), (1.f - _scale.z)));
        }

        // NOTE(abi): NIfTI and many other formats encode the volume as a single "image data",
        // rather than a series of individual axial images.
        void VolumeData::loadDataset()
        {
            // Free memory, if some is allocated
            if (_images)
            {
                nifti_image_free(_images);
            }

            // Data
            _images = nifti_image_read(_datasetPath.c_str(), 1);
            if (!_images)
            {
                std::cout << "Failed parsing NIfTI image data." << '\n';
                return;
            }

            // Metadata
            _header = nifti_read_header(_datasetPath.c_str(), NULL, 0);
            if (_printHeader)
            {
                disp_nifti_1_header(nullptr, _header);
            }

            _dimensions = {static_cast<unsigned short>(_header->dim[1]),
                           static_cast<unsigned short>(_header->dim[2]),
                           static_cast<unsigned short>(_header->dim[3])};

            // Scale vector
            float largestDim = std::max(_dimensions[0], std::max(_dimensions[1], _dimensions[2]));
            _scale = glm::vec3(static_cast<float>(_dimensions[0] / largestDim),
                               static_cast<float>(_dimensions[1] / largestDim),
                               static_cast<float>(_dimensions[2] / largestDim));
        }

        // We are interested in certain statistical values to perform different types or
        // projections:
        //	- MIP (Maximum Intensity Projection).
        //	- AIP (Average Intensity Projection).
        void VolumeData::findValuesOfInterest()
        {
            float numSamples{static_cast<float>(_dimensions[0] * _dimensions[1] * _dimensions[2])};
            for (unsigned int i = 0; i < numSamples; ++i)
            {
                // Current voxel value
                float sample = static_cast<float>(getData()[i]);
                if (sample > _maxIntensity)
                {
                    _maxIntensity = sample;
                }
                _averageIntensity += sample;
            }
            _averageIntensity = _averageIntensity / numSamples;

            std::cout << "Maximum: " << _maxIntensity << '\n';
            std::cout << "Average: " << _averageIntensity << '\n';
        }
    } // namespace graphics
} // namespace visus
