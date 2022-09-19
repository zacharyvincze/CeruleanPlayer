#pragma once

#include <string>

namespace helper {
extern bool is_option(const std::string& entry) { return entry[0] == '-'; }
};  // namespace helper