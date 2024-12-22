# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CALL_autogen"
  "CMakeFiles\\CALL_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CALL_autogen.dir\\ParseCache.txt"
  )
endif()
