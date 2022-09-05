#pragma once

#include <string>

namespace helper {
extern bool isOption(const std::string& entry) { return entry[0] == '-'; }
};  // namespace helper