SET(ARCH_OS $ENV{ARCH_OS})
SET(BUG $ENV{BUG})

SET(CMAKE_C_COMPILER_FORCED TRUE)
SET(CMAKE_CXX_COMPILER_FORCED TRUE)

SET(CMAKE_BUILD_TYPE $ENV{BUILD_MODE})

#ADD_DEFINITIONS(-D$ENV{ARCH} -D$ENV{ARCH}-$ENV{OS})
IF (ARCH_OS STREQUAL arm-ecos)
	SET(ARCH arm)
	SET(OS   ECOS)
	SET(TOOLCHAIN_PREFIX arm-linux-)
ELSEIF (ARCH_OS STREQUAL arm-linux)
	SET(ARCH arm)
	SET(OS   LINUX)
	SET(TOOLCHAIN_PREFIX arm-linux-)
ELSEIF (ARCH_OS STREQUAL csky-ecos)
	SET(ARCH csky)
	SET(OS   ECOS)
	SET(TOOLCHAIN_PREFIX csky-elf-)
ELSEIF (ARCH_OS STREQUAL csky-linux)
	SET(ARCH csky)
	SET(OS   LINUX)
	SET(TOOLCHAIN_PREFIX csky-linux-)
	SET(FLOAT "-mhard-float")
ELSEIF (ARCH_OS STREQUAL pc-linux)
	SET(ARCH pc)
	SET(OS   LINUX)
ELSE()
	SET(ARCH i386)
	SET(OS   LINUX)
	SET(GOXCEED_PATH /usr/local/)
ENDIF()

SET(GOXCEED_PATH       $ENV{GX_PREFIX}/${ARCH_OS})

EXECUTE_PROCESS(COMMAND which ${TOOLCHAIN_PREFIX}gcc
	OUTPUT_VARIABLE COMPILER_FULL_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)
SET(CMAKE_C_COMPILER   ${COMPILER_FULL_PATH})

EXECUTE_PROCESS(COMMAND which ${TOOLCHAIN_PREFIX}g++
	OUTPUT_VARIABLE COMPILER_FULL_PATH OUTPUT_STRIP_TRAILING_WHITESPACE)
SET(CMAKE_CXX_COMPILER   ${COMPILER_FULL_PATH})

ADD_DEFINITIONS(-D${ARCH} -D${OS}_OS)
ADD_DEFINITIONS(-D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64)

# adjust the default behaviour of hte FIND_XXX() NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODULE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_INCLUDE ONLY)

SET(GXSRC_PATH ${CMAKE_CURRENT_SOURCE_DIR})
SET(CMAKE_INSTALL_PREFIX ${GOXCEED_PATH} )

SET(CMAKE_C_COMPILER   ${TOOLCHAIN_PREFIX}gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}g++)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-function -funsigned-char --static")
SET(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O0 -g  -Wall")

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-unused-function -funsigned-char -D_GNU_SOURCE --static")
SET(CMAKE_C_FLAGS_DEBUG     "${CMAKE_C_FLAGS} -O0 -Wall -g -ggdb"  )
SET(CMAKE_C_FLAGS_RELEASE   "${CMAKE_C_FLAGS} -O0 -g -Wall")


INCLUDE_DIRECTORIES( ${GOXCEED_PATH}/include/      )
INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR}           )

LINK_DIRECTORIES(${GOXCEED_PATH}/lib)

FUNCTION(ADD_GX_LIBRARY name)
	ADD_LIBRARY( ${name} ${ARGN} )
	INSTALL(TARGETS ${name}
		ARCHIVE DESTINATION ${GOXCEED_PATH}/lib)
ENDFUNCTION(ADD_GX_LIBRARY name)
