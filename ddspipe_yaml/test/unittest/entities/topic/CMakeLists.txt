# Copyright 2022 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

###############################
# Yaml GetEntities Topic Test #
###############################

set(TEST_NAME YamlGetEntityTopicTest)

set(TEST_SOURCES
        YamlGetEntityTopicTest.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/YamlReader_generic.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/YamlReader_participants.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/YamlReader_types.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/YamlManager.cpp

    )

set(TEST_LIST
        get_real_topic
        get_real_topic_negative
        get_wildcard_topic
        get_real_topic_heritable
        get_wildcard_topic_heritable
    )

set(TEST_EXTRA_LIBRARIES
        yaml-cpp
        fastcdr
        fastdds
        cpp_utils
        ddspipe_core
        ddspipe_participants
    )

add_unittest_executable(
    "${TEST_NAME}"
    "${TEST_SOURCES}"
    "${TEST_LIST}"
    "${TEST_EXTRA_LIBRARIES}")
