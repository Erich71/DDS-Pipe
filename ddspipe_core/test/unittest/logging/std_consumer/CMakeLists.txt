# Copyright 2024 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

set(TEST_NAME StdLogConsumerTest)

set(TEST_SOURCES
        StdLogConsumerTest.cpp
    )

file(
    GLOB_RECURSE LIBRARY_SOURCES
        "${PROJECT_SOURCE_DIR}/src/cpp/*.c*"
        "${PROJECT_SOURCE_DIR}/include/*.h*"
        "${PROJECT_SOURCE_DIR}/include/*.ipp"
    )

all_library_sources(
        "${TEST_SOURCES}"
        "${LIBRARY_SOURCES}"
    )

set(TEST_LIST
        print_logs
        dont_print_logs
    )

set(TEST_EXTRA_LIBRARIES
        fastcdr
        fastdds
        cpp_utils
    )

add_unittest_executable(
        "${TEST_NAME}"
        "${TEST_SOURCES}"
        "${TEST_LIST}"
        "${TEST_EXTRA_LIBRARIES}"
    )
