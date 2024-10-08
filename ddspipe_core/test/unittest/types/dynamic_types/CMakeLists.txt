# Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

####################
# dtypes_msg_tests #
####################

set(TEST_NAME dtypes_msg_tests)

# Add to test sources every FastDDSGen file generated
file(GLOB DATATYPE_SOURCES_CXX "types/**/*.cxx")
set(TEST_SOURCES
        dtypes_msg_tests.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/dynamic_types/schema_msg.cpp
        ${DATATYPE_SOURCES_CXX}
    )

set(TEST_LIST
    )

set(TEST_EXTRA_LIBRARIES
        fastcdr
        fastdds
        cpp_utils
        $<$<BOOL:${WIN32}>:iphlpapi$<SEMICOLON>Shlwapi>
    )

# Add to needed sources every .msg file
file(
    GLOB
        RESULT_SOURCES_MSG
    RELATIVE
        "${CMAKE_CURRENT_SOURCE_DIR}"
    "types/msgs/*.msg")

set(TEST_NEEDED_SOURCES
        ${RESULT_SOURCES_MSG}
    )

add_unittest_executable(
        "${TEST_NAME}"
        "${TEST_SOURCES}"
        "${TEST_LIST}"
        "${TEST_EXTRA_LIBRARIES}"
        "${TEST_NEEDED_SOURCES}"
    )
