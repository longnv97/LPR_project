// Copyright (C) 2018-2020 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

/**
 * @deprecated Use vpu/myriad_config.hpp or vpu/hddl_config.hpp instead.
 * @brief A header that defines advanced related properties for VPU plugins.
 * These properties should be used in SetConfig() and LoadNetwork() methods of plugins
 *
 * @file vpu_plugin_config.hpp
 */

#pragma once

#include "vpu/myriad_plugin_config.hpp"
#include "vpu/hddl_plugin_config.hpp"
#include "ie_api.h"

#ifdef ABILITY_CUSTOMIZED

#define ABILITY_SYMBOL              (0xABBA)
#define OPENVINO_RELEASE_YEAR       (21)
#define OPENVINO_RELEASE_Main       (03)
#define OPENVINO_RELEASE_SUB        (00)
#define ABILITY_MAIN_VERSION        (01)
#define ABILITY_SUB_VERSION         (02)

typedef struct _CorrespondedOpenVINOVersion_ {
    unsigned char   OpenVINOReleaseYear;
    unsigned char   OpenVINOMainRelease;
    unsigned char   OpenVINOSubRelease;
}OpenVINOVersionS;

typedef struct _AbilityGraphVersion_ {
    unsigned char   MainVersion;
    unsigned char   SubVersion;
}AbilityGraphVersionS;

typedef struct _AbilityCustomGraphHeader_ {
    unsigned short          AbilityCustomizedSymbol;
    OpenVINOVersionS        OpenVINOVersion;
    AbilityGraphVersionS    AbilityVersion;
    unsigned char           ConvertPlatform;
    unsigned int            GraphDataLength;
    unsigned int            GraphParsingLength;
    unsigned short          ColorFormat;
    unsigned char           Reserved2[2];
    unsigned short          ResolutionWidth;
    unsigned short          ResolutionHeight;
    unsigned int            XMLDataLength;
    unsigned char           Reserved3[228];
}AbilityCustomGraphHeader;

typedef struct _AbilityCustomGraphTailer_ {
    unsigned char sha256Data[32];
}AbilityCustomGraphTailer;
#endif
//
// Common options
//

#define VPU_CONFIG_KEY(name) InferenceEngine::VPUConfigParams::_CONFIG_KEY(VPU_##name)
#define VPU_CONFIG_VALUE(name) InferenceEngine::VPUConfigParams::VPU_##name

#define DECLARE_VPU_CONFIG_KEY(name) DECLARE_CONFIG_KEY(VPU_##name)
#define DECLARE_VPU_CONFIG_VALUE(name) DECLARE_CONFIG_VALUE(VPU_##name)

//
// Common metrics
//

#define VPU_METRIC(name) METRIC_KEY(VPU_##name)
#define DECLARE_VPU_METRIC(name, ...)  DECLARE_METRIC_KEY(VPU_##name, __VA_ARGS__)

namespace InferenceEngine {

/**
 * @brief VPU plugin configuration
 */
namespace VPUConfigParams {

//
// Common options
//

/**
 * @deprecated Use InferenceEngine::MYRIAD_ENABLE_HW_ACCELERATION instead.
 * @brief Turn on HW stages usage (applicable for MyriadX devices only).
 * This option should be used with values: CONFIG_VALUE(YES) or CONFIG_VALUE(NO) (default)
 */
INFERENCE_ENGINE_DEPRECATED("Use InferenceEngine::MYRIAD_ENABLE_HW_ACCELERATION instead")
DECLARE_VPU_CONFIG_KEY(HW_STAGES_OPTIMIZATION);

/**
 * @deprecated Use CONFIG_KEY(LOG_LEVEL) instead.
 * @brief The key to define log level
 */
INFERENCE_ENGINE_DEPRECATED("Use CONFIG_KEY(LOG_LEVEL) instead")
DECLARE_VPU_CONFIG_KEY(LOG_LEVEL);

/**
 * @deprecated Use InferenceEngine::MYRIAD_ENABLE_RECEIVING_TENSOR_TIME instead.
 * @brief The flag for adding to the profiling information the time of obtaining a tensor.
 * This option should be used with values: CONFIG_VALUE(YES) or CONFIG_VALUE(NO) (default)
 */
INFERENCE_ENGINE_DEPRECATED("Use InferenceEngine::MYRIAD_ENABLE_RECEIVING_TENSOR_TIME instead")
DECLARE_VPU_CONFIG_KEY(PRINT_RECEIVE_TENSOR_TIME);

/**
 * @deprecated Use InputInfo::setLayout on input data from CNNNetwork::getInputsInfo() or
 * Data::setLayout on output data from CNNNetwork::getOutputsInfo()
 * @brief This option allows to to specify input output layouts for network layers.
 * By default, this value set to VPU_CONFIG_VALUE(AUTO) value.
 * Supported values:
 *   VPU_CONFIG_VALUE(AUTO) executable network configured to use optimal layer layout depending on available HW
 *   VPU_CONFIG_VALUE(NCHW) executable network forced to use NCHW input/output layouts
 *   VPU_CONFIG_VALUE(NHWC) executable network forced to use NHWC input/output layouts
 */
INFERENCE_ENGINE_DEPRECATED("Use InputInfo::setLayout on input data from CNNNetwork::getInputsInfo() or" \
    "Data::setLayout on output data from CNNNetwork::getOutputsInfo()")
DECLARE_VPU_CONFIG_KEY(COMPUTE_LAYOUT);

/**
 * @deprecated See VPU_CONFIG_KEY(COMPUTE_LAYOUT) deprecation info.
 * @brief Supported keys definition for VPU_CONFIG_KEY(COMPUTE_LAYOUT) option.
 */
INFERENCE_ENGINE_DEPRECATED("See VPU_CONFIG_KEY(COMPUTE_LAYOUT) deprecation info")
DECLARE_VPU_CONFIG_VALUE(AUTO);
INFERENCE_ENGINE_DEPRECATED("See VPU_CONFIG_KEY(COMPUTE_LAYOUT) deprecation info")
DECLARE_VPU_CONFIG_VALUE(NCHW);
INFERENCE_ENGINE_DEPRECATED("See VPU_CONFIG_KEY(COMPUTE_LAYOUT) deprecation info")
DECLARE_VPU_CONFIG_VALUE(NHWC);
INFERENCE_ENGINE_DEPRECATED("See VPU_CONFIG_KEY(COMPUTE_LAYOUT) deprecation info")
DECLARE_VPU_CONFIG_VALUE(NCDHW);
INFERENCE_ENGINE_DEPRECATED("See VPU_CONFIG_KEY(COMPUTE_LAYOUT) deprecation info")
DECLARE_VPU_CONFIG_VALUE(NDHWC);

/**
 * @deprecated Use InferenceEngine::MYRIAD_CUSTOM_LAYERS instead.
 * @brief This option allows to pass custom layers binding xml.
 * If layer is present in such an xml, it would be used during inference even if the layer is natively supported
 */
INFERENCE_ENGINE_DEPRECATED("Use InferenceEngine::MYRIAD_CUSTOM_LAYERS instead")
DECLARE_VPU_CONFIG_KEY(CUSTOM_LAYERS);

/**
 * @deprecated Use InferenceEngine::MYRIAD_PROTOCOL instead.
 * @brief This option allows to specify protocol.
 */
INFERENCE_ENGINE_DEPRECATED("Use InferenceEngine::MYRIAD_PROTOCOL instead")
DECLARE_VPU_MYRIAD_CONFIG_KEY(PROTOCOL);

/**
 * @deprecated Use InferenceEngine::MYRIAD_PCIE or InferenceEngine::MYRIAD_USB instead.
 * @brief Supported keys definition for VPU_MYRIAD_CONFIG_KEY(PROTOCOL) option.
 */
INFERENCE_ENGINE_DEPRECATED("Use InferenceEngine::MYRIAD_PCIE instead")
DECLARE_VPU_MYRIAD_CONFIG_VALUE(PCIE);
INFERENCE_ENGINE_DEPRECATED("Use InferenceEngine::MYRIAD_USB instead")
DECLARE_VPU_MYRIAD_CONFIG_VALUE(USB);

#ifdef ABILITY_CUSTOMIZED
/**
* @Ability customized config
*/
DECLARE_VPU_CONFIG_KEY(AB_LOAD_MODEL_OPTIMIZE);
DECLARE_VPU_CONFIG_KEY(AB_GRAPH_PATH);
DECLARE_VPU_CONFIG_KEY(AB_OPTIMIZE_LOAD_METHOD);
DECLARE_VPU_CONFIG_KEY(AB_GRAPH_MEMORY_PTR);
DECLARE_VPU_CONFIG_KEY(AB_GRAPH_SIZE);
#endif
}  // namespace VPUConfigParams

}  // namespace InferenceEngine
