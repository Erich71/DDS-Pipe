// Copyright 2022 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <fastdds/rtps/common/CacheChange.hpp>
#include <fastdds/rtps/common/GuidPrefix_t.hpp>

#include <ddspipe_core/library/library_dll.h>

namespace eprosima {
namespace ddspipe {
namespace core {
namespace types {

/**
 * @brief Specialization of CacheChange for DDS Pipe.
 *
 * It adds the following attributes:
 * - last_writer_guid_prefix: store last jump of message Participant GuidPrefix
 *
 * This Change is required to be used for features:
 * - Repeater participant: avoid redirecting the message to the source participant.
 */
struct RouterCacheChange : public fastdds::rtps::CacheChange_t
{
public:

    //! Using parent constructors
    using fastdds::rtps::CacheChange_t::CacheChange_t;

    /**
     * @brief GuidPrefix of the Participant that has sent this message through the pipe.
     *
     * @note it is not the same as origin writer, as there could be more pipes in the path.
     */
    fastdds::rtps::GuidPrefix_t last_writer_guid_prefix;
};

} /* namespace types */
} /* namespace core */
} /* namespace ddspipe */
} /* namespace eprosima */
