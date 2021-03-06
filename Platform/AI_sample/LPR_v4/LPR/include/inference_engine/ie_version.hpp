// Copyright (C) 2018-2020 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

/**
 * @brief A header file that provides versioning information for the inference engine shared library
 *
 * @file ie_version.hpp
 */
#pragma once

#include "ie_api.h"

/**
 * @brief Inference Engine C++ API
 */
namespace InferenceEngine {

/**
 * @struct Version
 * @brief  Represents version information that describes plugins and the inference engine runtime library
 */
#pragma pack(push, 1)
struct Version {
    /**
     * @brief An API version reflects the set of supported features
     */
    struct {
        int major; //!< A major version
        int minor; //!< A minor version
    } apiVersion;
    /**
     * @brief A null terminated string with build number
     */
    const char* buildNumber;
    /**
     * @brief A null terminated description string
     */
    const char* description;
};
#pragma pack(pop)

/**
 * @brief Gets the current Inference Engine version
 *
 * @return The current Inference Engine version
 */
INFERENCE_ENGINE_API(const Version*) GetInferenceEngineVersion() noexcept;

#ifdef ABILITY_CUSTOMIZED
INFERENCE_ENGINE_API(const char*) GetABVersion() noexcept;
#endif
}  // namespace InferenceEngine
