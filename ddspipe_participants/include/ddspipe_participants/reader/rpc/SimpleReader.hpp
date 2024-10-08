// Copyright 2021 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#include <ddspipe_core/types/topic/rpc/RpcTopic.hpp>

#include <ddspipe_participants/library/library_dll.h>
#include <ddspipe_participants/reader/rtps/CommonReader.hpp>

namespace eprosima {
namespace ddspipe {
namespace participants {
namespace rpc {

/**
 * Base RTPS Reader concrete class that implements abstract CommonReader one.
 */
class SimpleReader : public rtps::CommonReader
{
public:

    /**
     * @brief Construct a new SimpleReader object
     *
     * Get the Attributes and TopicQoS and create the SimpleReader History and the RTPS SimpleReader.
     *
     * @param participant_id    Router Id of the Participant that has created this SimpleReader.
     * @param topic             Topic that this SimpleReader subscribes to.
     * @param payload_pool      Shared Payload Pool to received data and take it.
     * @param rtps_participant  RTPS Participant pointer (this is not stored).
     *
     * @throw \c InitializationException in case any creation has failed
     */
    DDSPIPE_PARTICIPANTS_DllAPI
    SimpleReader(
            const core::types::ParticipantId& participant_id,
            const core::types::DdsTopic& topic,
            const std::shared_ptr<core::PayloadPool>& payload_pool,
            fastdds::rtps::RTPSParticipant* rtps_participant);

    //! Override Parent method to create an RPC data type.
    DDSPIPE_PARTICIPANTS_DllAPI
    virtual core::types::RtpsPayloadData* create_data_(
            const fastdds::rtps::CacheChange_t& received_change) const noexcept override;

    //! Override Parent method to fill fields exclusive from RPC.
    DDSPIPE_PARTICIPANTS_DllAPI
    virtual void fill_received_data_(
            const fastdds::rtps::CacheChange_t& received_change,
            core::types::RtpsPayloadData& data_to_fill) const noexcept override;
};

} /* namespace rpc */
} /* namespace participants */
} /* namespace ddspipe */
} /* namespace eprosima */
