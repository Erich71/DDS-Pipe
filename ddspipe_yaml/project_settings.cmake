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

###############################################################################
# Set settings for project ddspipe_yaml
###############################################################################

set(MODULE_NAME
    ddspipe_yaml
)

set(MODULE_SUMMARY
    "eprosima DDS Pipe C++ Module to read objects and configurations from YAML files."
)

set(MODULE_FIND_PACKAGES
    yaml-cpp
    fastcdr
    fastdds
    cpp_utils
    ddspipe_core
    ddspipe_participants
)

set(MODULE_DEPENDENCIES
    $<$<BOOL:${WIN32}>:iphlpapi$<SEMICOLON>Shlwapi>
    ${MODULE_FIND_PACKAGES}
)
