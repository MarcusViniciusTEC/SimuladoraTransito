if(GIT_EXECUTABLE)
  get_filename_component(SRC_DIR ${SRC} DIRECTORY)
  # Generate a git-describe version string from Git repository tags
  execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --tags --dirty --match "v*"
    WORKING_DIRECTORY ${SRC_DIR}
    OUTPUT_VARIABLE GIT_DESCRIBE_VERSION
    RESULT_VARIABLE GIT_DESCRIBE_ERROR_CODE
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
    OUTPUT_QUIET
    )
  if(NOT GIT_DESCRIBE_ERROR_CODE)
    set(APP_GIT_VERSION ${GIT_DESCRIBE_VERSION})
  endif()
endif()

# Final fallback: Just use a bogus version string that is semantically older
# than anything else and spit out a warning to the developer.
if(NOT DEFINED APP_GIT_VERSION)
  set(APP_GIT_VERSION v0.0)  
endif()

message(STATUS "APP_GIT_VERSION do GIT = \"${APP_GIT_VERSION}\"")


configure_file(${SRC} ${DST} @ONLY)
