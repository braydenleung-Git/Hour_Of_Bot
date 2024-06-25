find_path(Spdlog_INCLUDE_DIR NAMES Spdlog/Spdlog.h HINTS ${SPDLOG_ROOT_DIR})
 
find_library(Spdlog_LIBRARIES NAMES Spdlog "libspdlog.a" HINTS ${SPDLOG_ROOT_DIR})
 
include(FindPackageHandleStandardArgs)
 
find_package_handle_standard_args(Spdlog DEFAULT_MSG Spdlog_LIBRARIES Spdlog_INCLUDE_DIR)