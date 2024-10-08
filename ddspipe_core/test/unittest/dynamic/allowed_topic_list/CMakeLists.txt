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

set(TEST_NAME AllowedTopicListTest)

set(TEST_SOURCES
        AllowedTopicListTest.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/dynamic/AllowedTopicList.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/topic/rpc/RpcTopic.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/dds/TopicQoS.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/topic/dds/DdsTopic.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/topic/filter/IFilterTopic.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/topic/filter/WildcardDdsFilterTopic.cpp
        ${PROJECT_SOURCE_DIR}/src/cpp/types/topic/Topic.cpp
    )
all_header_sources("${TEST_SOURCES}")

set(TEST_LIST
        is_topic_allowed__default_constructor
        is_topic_allowed__empty_list
        is_topic_allowed__simple_blocklist
        is_topic_allowed__complex_blocklist
        is_topic_allowed__simple_allowlist
        is_topic_allowed__complex_allowlist
        is_topic_allowed__simple_allowlist_and_blocklist
        is_topic_allowed__complex_allowlist_and_blocklist
        is_topic_allowed__simple_allowlist_and_blocklist_entangled
        is_topic_allowed__complex_allowlist_and_blocklist_entangled
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
