# src/SasfitCmakeUtils.cmake
#
# Copyright (c) 2008-2009, Paul Scherrer Institute (PSI)
#
# This file is part of SASfit.
#
# SASfit is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# SASfit is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with SASfit.  If not, see <http://www.gnu.org/licenses/>.
#############################################################################
# Author(s) of this file:
#   Ingo Bressler (ingo@cs.tu-berlin.de)
#############################################################################
# A Cmake module to provide utility functions often used 
# in sasfit cmake scripts
#
# This module expects to live in <sasfit-dir>/src
#############################################################################

cmake_minimum_required(VERSION 2.6.2)
if(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION} VERSION_GREATER 2.6.2)
	cmake_policy(SET CMP0011 OLD)
endif(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION} VERSION_GREATER 2.6.2)
cmake_policy(SET CMP0012 NEW)

# adds given files to binary distribution file list
# needs to be a function, because we operate on a cmake cache variable
function(sasfit_file_list)
	set(SASFIT_BIN_FILE_LIST ${ARGN}
		CACHE STRING "files part of a sasfit binary package" FORCE
	)
endfunction(sasfit_file_list)

# ensure that the dir doesn't exist before creating it
macro(sasfit_assert_dir)
	if(${ARGC} GREATER 0)
		if(NOT EXISTS ${ARGV0})
			file(MAKE_DIRECTORY ${ARGV0})
		endif(NOT EXISTS ${ARGV0})
	endif(${ARGC} GREATER 0)
endmacro(sasfit_assert_dir)


# copy shared libs to a target dir (where sasfit tcl routines will find them)
macro(sasfit_copy_shared_libs SHARED_TARGET REL_TARGET_DIR)
	sasfit_copy_libs(${REL_TARGET_DIR} "${CMAKE_SHARED_LIBRARY_PREFIX}" ${SHARED_TARGET} "${CMAKE_SHARED_LIBRARY_SUFFIX}")
endmacro(sasfit_copy_shared_libs)

macro(sasfit_copy_static_libs STATIC_TARGET REL_TARGET_DIR)
	sasfit_copy_libs(${REL_TARGET_DIR} "${CMAKE_STATIC_LIBRARY_PREFIX}" ${STATIC_TARGET} "${CMAKE_STATIC_LIBRARY_SUFFIX}")
endmacro(sasfit_copy_static_libs)

# copy plugin (shared lib) to a target dir (where sasfit tcl routines will find them)
macro(sasfit_copy_plugins SHARED_TARGET SUPP_FILE_PATH SUPP_FILE)
	sasfit_copy_libs(plugins "${CMAKE_SHARED_MODULE_PREFIX}" ${SHARED_TARGET} "${CMAKE_SHARED_MODULE_SUFFIX}" ${SUPP_FILE_PATH} ${SUPP_FILE})
endmacro(sasfit_copy_plugins)

macro(replace_str_in_file FILENAME PATTERN_STR REPLACE_STR)
	# let the documentation know about the svn revision number
	file(READ ${FILENAME} FILE_BODY)
	string(REGEX REPLACE "${PATTERN_STR}" "${REPLACE_STR}"
		FILE_BODY_NEW ${FILE_BODY})
	file(WRITE ${FILENAME} ${FILE_BODY_NEW})
endmacro(replace_str_in_file)

macro(get_rev_from_docs FILENAME)
	file(READ ${FILENAME} FILE_BODY)
	string(LENGTH ${FILE_BODY} LEN)
	set(PATTERN "PROJECT_NUMBER         = [a-z]?[0-9]+\\.?[0-9]*\\.?([a-z]|[0-9])*\\.?([a-z]|[0-9])*")
	string(REGEX MATCH "${PATTERN}" LINE "${FILE_BODY}")
	string(REGEX MATCH "[0-9]+\\.?[0-9]*\\.?([a-z]|[0-9])*\\.?([a-z]|[0-9])*" REV_NR "${LINE}")
endmacro(get_rev_from_docs)

# determine sasfit-root directory
if(NOT DEFINED SASFIT_ROOT_DIR)
	get_filename_component(CURRENT_DIR ${CMAKE_CURRENT_LIST_FILE} PATH)
	set(SASFIT_ROOT_DIR ${CURRENT_DIR}/..)
endif(NOT DEFINED SASFIT_ROOT_DIR)

# copy shared libs to a target dir (where sasfit tcl routines will find them)
# SHARED_TARGET: name of the cmake target whose libraries should be copied
# REL_TARGET_DIR: path of target directory, relative to sasfit-root dir
# ARG2: absolute path to supplementary file to copy [optional]
# ARG3: filename of supplementary file to copy [optional]
macro(sasfit_copy_libs REL_TARGET_DIR PREFIX SHARED_TARGET SUFFIX)
	set(TARGET_DIR ${SASFIT_ROOT_DIR}/${REL_TARGET_DIR})
	sasfit_assert_dir(${TARGET_DIR})
	set(SHARED_LIB_NAME ${PREFIX}${SHARED_TARGET}${SUFFIX})
	set(SHARED_LIB_FULL_NAME ${LIBRARY_OUTPUT_PATH}/${CMAKE_CFG_INTDIR}/${SHARED_LIB_NAME})

	# add additional copy command if a 2nd file was provided
	set(SUPP_CMD "")
	if(${ARGC} GREATER 5)
		set(SUPP_CMD COMMAND ${CMAKE_COMMAND} ARGS -E copy "${ARGV4}/${ARGV5}" "${TARGET_DIR}")
		sasfit_file_list(${SASFIT_BIN_FILE_LIST}
			${REL_TARGET_DIR}/${ARGV5}
		)
	endif(${ARGC} GREATER 5)
	set(CMD COMMAND ${CMAKE_COMMAND} ARGS -E copy "${SHARED_LIB_FULL_NAME}" "${TARGET_DIR}/${SHARED_TARGET}${SUFFIX}")
	add_custom_command(TARGET ${SHARED_TARGET} POST_BUILD
			${CMD}
			${SUPP_CMD}
			VERBATIM
	)

	if(NOT ${SHARED_TARGET} STREQUAL "sasfit")
		# add this binary to the list of files to copy for a working package
		sasfit_file_list(${SASFIT_BIN_FILE_LIST}
			${REL_TARGET_DIR}/${SHARED_TARGET}${SUFFIX}
		)
	endif(NOT ${SHARED_TARGET} STREQUAL "sasfit")
endmacro(sasfit_copy_libs)

macro(sasfit_cmake_plugin_static)

	set(PRJ_NAME_STAT ${PRJ_NAME}_stat)
	find_package(sasfit REQUIRED)
	include_directories(
		${sasfit_INCLUDE_DIRS}
		${SASFIT_ROOT_DIR}/plugins
	)

	add_library(${PRJ_NAME_STAT} STATIC ${PRJ_SOURCE})

	set(COMPILE_FLAGS)
	if(UNIX)
		set(COMPILE_FLAGS "-Wall")
		if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
			# required for static builds on 64bit
			set(COMPILE_FLAGS "${COMPILE_FLAGS} -fPIC")
		endif(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
		if(DEFINED SASFIT_DEBUG)
			set(COMPILE_FLAGS "${COMPILE_FLAGS} -g")
		endif(DEFINED SASFIT_DEBUG)
	endif(UNIX)
	set_target_properties(${PRJ_NAME_STAT} PROPERTIES COMPILE_DEFINITIONS STATIC_ENABLED)
	set_target_properties(${PRJ_NAME_STAT} PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}")

	# set library search paths for internal shared libraries
	# build with the whole sasfit package controlled by a toplevel CMakeLists
#	sasfit_copy_plugins(${PRJ_NAME} "${SRC_DIR}/include" "${PRJ_NAME}.h")

endmacro(sasfit_cmake_plugin_static)

macro(sasfit_cmake_plugin)

	include(SasfitSourceFiles)

	set(PRJ_SOURCE ${SOURCE_${PRJ_NAME}})
	set(LIBRARY_OUTPUT_PATH ${SRC_DIR}/lib)

	find_package(sasfit_common REQUIRED)
	find_package(GSL REQUIRED)
	find_package(f2c REQUIRED)
	include_directories(
		${sasfit_common_INCLUDE_DIRS}
		${GSL_INCLUDE_DIRS}
		${f2c_INCLUDE_DIRS}
	)

	add_library(${PRJ_NAME} MODULE ${PRJ_SOURCE})

	# adjust the linked libs according to find_package() statements above
	target_link_libraries(${PRJ_NAME} ${GSL_STATIC_LIBRARIES})
	set_target_properties(${PRJ_NAME} PROPERTIES COMPILE_DEFINITIONS MAKE_SASFIT_PLUGIN)
	set(COMPILE_FLAGS)
	if(UNIX)
		set(COMPILE_FLAGS "-Wall")
		if(DEFINED SASFIT_DEBUG)
			set(COMPILE_FLAGS "${COMPILE_FLAGS} -g")
		endif(DEFINED SASFIT_DEBUG)
	endif(UNIX)
	set_target_properties(${PRJ_NAME} PROPERTIES COMPILE_FLAGS "${COMPILE_FLAGS}")
#	sasfit_build_props_unix(${PRJ_NAME} -save-temps)

	# set library search paths for internal shared libraries
	# build with the whole sasfit package controlled by a toplevel CMakeLists
	sasfit_copy_plugins(${PRJ_NAME} "${SRC_DIR}/include" "${PRJ_NAME}.h")

	if(DEFINED WITH_STATIC)
		sasfit_cmake_plugin_static()
	endif(DEFINED WITH_STATIC)

endmacro(sasfit_cmake_plugin)


macro(sasfit_update_version)

	set(DETERMINED_FROM_DOCS FALSE)
	if(NOT DEFINED SASFIT_VERSION)
		# try to get the revision number of the working copy (current dir)
		# for a correct rev number it is required to update again after commit
		set(SASFIT_SVN_DIRS
			${SASFIT_ROOT_DIR}/.svn
			${SASFIT_ROOT_DIR}/src/.svn
		)
		set(REV_NR 0)
		foreach(DIRNAME ${SASFIT_SVN_DIRS})
			if(EXISTS ${DIRNAME}/entries)
				file(STRINGS ${DIRNAME}/entries SASFIT_SVN LIMIT_COUNT 4)
				foreach(str ${SASFIT_SVN}) ## how to chose the last string of a string-'array' ?
					if(${str} GREATER ${REV_NR})
						set(REV_NR ${str}) # set to highest revision if available
					endif(${str} GREATER ${REV_NR})
				endforeach(str)
			endif(EXISTS ${DIRNAME}/entries)
		endforeach(DIRNAME)
		if(${REV_NR} EQUAL 0)
			# get the version number from the documentation if
			# everything else fails
			get_rev_from_docs(${SASFIT_ROOT_DIR}/src/Doxyfile)
			set(DETERMINED_FROM_DOCS TRUE)
		endif(${REV_NR} EQUAL 0)
		set(SASFIT_VERSION "r${REV_NR}")
	endif(NOT DEFINED SASFIT_VERSION)

	# let the tcl code know about the svn revision number
	file(WRITE ${SASFIT_ROOT_DIR}/sasfit.vfs/lib/app-sasfit/tcl/sasfit_svn_rev.tcl
		"set sasfit(svn_rev) ${SASFIT_VERSION}"
	)
	# let the documentation know about the svn revision number
	replace_str_in_file(${SASFIT_ROOT_DIR}/src/Doxyfile 
		"PROJECT_NUMBER         = [a-z]?[0-9]+\\\\.?[0-9]*\\\\.?([a-z]|[0-9])*\\\\.?([a-z]|[0-9])*"
		"PROJECT_NUMBER         = ${SASFIT_VERSION}"
	)

	# set sasfit revision number
	if(DEFINED REV_NR)
		if(${DETERMINED_FROM_DOCS})
			set(SASFIT_VERSION "devel_custom")
		else(${DETERMINED_FROM_DOCS})
			set(SASFIT_VERSION "devel_r${REV_NR}")
		endif(${DETERMINED_FROM_DOCS})
	endif(DEFINED REV_NR)

endmacro(sasfit_update_version)

