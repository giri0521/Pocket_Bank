# Simplified toolchain - use system packages from Alpine apk
# No vcpkg auto-install due to Alpine/musl compatibility issues
set(CMAKE_FIND_DEBUG_MODE FALSE)
