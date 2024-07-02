# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\RegistrationProgram_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\RegistrationProgram_autogen.dir\\ParseCache.txt"
  "RegistrationProgram_autogen"
  )
endif()
