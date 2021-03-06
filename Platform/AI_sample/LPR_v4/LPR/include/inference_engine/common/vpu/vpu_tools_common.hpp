// Copyright (C) 2018-2020 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include <string>
#include <map>

static std::map<std::string, std::string> parseConfig(const std::string &configName, char comment = '#') {
//ABILITY_CUSTOMIZED
    std::map<std::string, std::string> config = {{"key","value"}};
    config.clear();


    std::ifstream file(configName);
    if (!file.is_open()) {
        return config;
    }

    std::string key, value;
    while (file >> key >> value) {
        if (key.empty() || key[0] == comment) {
            continue;
        }
        config[key] = value;
    }

    return config;
}
