#include "VolumeData.hpp"

#include <glm/ext/matrix_transform.hpp>
#include <iostream>

namespace visus
{
    namespace graphics
    {
        VolumeData::VolumeData()
        {
            parseNifti();
            // findValuesOfInterest();

            // Center at the origin
            _modelMat = glm::translate(_modelMat, glm::vec3(-0.5f));

            // Volume scale (defined in header metadata)
            _modelMat = glm::scale(_modelMat, _scaleVec);

            // After scaling we obviously need to shift the volume to recenter it
            _modelMat =
                glm::translate(_modelMat, glm::vec3((1.f - _scaleVec.x), (1.f - _scaleVec.y),
                                                    (1.f - _scaleVec.z)));
        }

        // NOTE(abi): NIfTI and many other formats encode the volume as a single "image data",
        // rather than a series of individual axial images.
        void VolumeData::parseNifti()
        {
            // Release previous image, is one is allocated
            if (_image)
            {
                nifti_image_free(_image);
            }

            // Parse image (data)
            _image = nifti_image_read(_datasetPath.c_str(), 1);
            if (!_image)
            {
                std::cout << "Failed parsing NIfTI image: " << _datasetPath << '\n';
                return;
            }

            // Parse header (metadata)
            _header = nifti_read_header(_datasetPath.c_str(), nullptr, 0);
            if (_printHeader)
            {
                disp_nifti_1_header(nullptr, _header);
            }

            _dimensions = {static_cast<unsigned short>(_header->dim[1]),
                           static_cast<unsigned short>(_header->dim[2]),
                           static_cast<unsigned short>(_header->dim[3])};

            // NOTE(abi): we need to scale the model matrix by the volume dimensions.
            float largestDimension =
                std::max(_dimensions[0], std::max(_dimensions[1], _dimensions[2]));
            _scaleVec = glm::vec3(static_cast<float>(_dimensions[0]) / largestDimension,
                                  static_cast<float>(_dimensions[1]) / largestDimension,
                                  static_cast<float>(_dimensions[2]) / largestDimension);
        }

        // // We are interested in certain statistical values to perform different types or
        // // projections:
        // //	- MIP (Maximum Intensity Projection).
        // //	- AIP (Average Intensity Projection).
        // void VolumeData::findValuesOfInterest()
        // {
        //     float numSamples{static_cast<float>(_dimensions[0] * _dimensions[1] *
        //     _dimensions[2])}; for (unsigned int i = 0; i < numSamples; ++i)
        //     {
        //         // Current voxel value
        //         float sample = static_cast<float>(getData()[i]);
        //         if (sample > _maxIntensity)
        //         {
        //             _maxIntensity = sample;
        //         }
        //         _averageIntensity += sample;
        //     }
        //     _averageIntensity = _averageIntensity / numSamples;

        //     std::cout << "Maximum: " << _maxIntensity << '\n';
        //     std::cout << "Average: " << _averageIntensity << '\n';
        // }
    } // namespace graphics
} // namespace visus
