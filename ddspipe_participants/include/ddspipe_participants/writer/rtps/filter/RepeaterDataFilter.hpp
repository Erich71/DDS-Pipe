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

#include <ddspipe_participants/library/library_dll.h>
#include <ddspipe_participants/writer/rtps/filter/SelfDataFilter.hpp>

namespace eprosima {
namespace ddspipe {
namespace participants {
namespace rtps {

/**
 * This filter allows to not send messages from this Writer to the Readers belonging to the source Participant.
 * It is used in "repeater" participants in order to propagate information to external participants
 * (participants not belonging to the same DDS-Router instance),
 * leaving out the participant from which this information was received.
 *
 * This uses the RouterCacheChange extra information.
 */
class RepeaterDataFilter : public SelfDataFilter
{
public:

    /**
     * @brief Whether incoming change is relevant for this reader.
     *
     * @return true if the reader does not belong to Participant that previously sent this message.
     * @return false otherwise.
     */
    DDSPIPE_PARTICIPANTS_DllAPI
    bool is_relevant(
            const fastdds::rtps::CacheChange_t& change,
            const fastdds::rtps::GUID_t& reader_guid
            ) const override;
};

} /* namespace rtps */
} /* namespace participants */
} /* namespace ddspipe */
} /* namespace eprosima */
