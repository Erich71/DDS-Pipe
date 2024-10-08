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

#include <mutex>

#include <cpp_utils/ReturnCode.hpp>
#include <cpp_utils/time/time_utils.hpp>

#include <fastdds/dds/subscriber/qos/ReaderQos.hpp>
#include <fastdds/rtps/attributes/HistoryAttributes.hpp>
#include <fastdds/rtps/attributes/ReaderAttributes.hpp>
#include <fastdds/rtps/builtin/data/TopicDescription.hpp>
#include <fastdds/rtps/history/ReaderHistory.hpp>
#include <fastdds/rtps/reader/ReaderListener.hpp>
#include <fastdds/rtps/reader/RTPSReader.hpp>
#include <fastdds/utils/TimedMutex.hpp>

#include <ddspipe_core/types/dds/Guid.hpp>
#include <ddspipe_core/types/topic/dds/DdsTopic.hpp>
#include <ddspipe_core/types/participant/ParticipantId.hpp>
#include <ddspipe_core/types/data/RtpsPayloadData.hpp>

#include <ddspipe_participants/library/library_dll.h>
#include <ddspipe_participants/reader/auxiliar/BaseReader.hpp>

namespace eprosima {
namespace ddspipe {
namespace participants {
namespace rtps {

/**
 * Abstract generic class for a RTPS Reader wrapper.
 *
 * It implements the ReaderListener for itself with \c on_new_cache_change_added and \c on_reader_matched callbacks.
 *
 * @warning This object is not RAII and must be initialized before used.
 */
class CommonReader : public BaseReader, public fastdds::rtps::ReaderListener
{
public:

    /////////////////////////
    // CONSTRUCTOR
    /////////////////////////

    // Protected ctor to make class abstract (only built by their childs).

    /**
     * @brief Destroy the CommonReader object
     *
     * Delete the RTPS CommonReader and CommonReader History in case they are set.
     */
    DDSPIPE_PARTICIPANTS_DllAPI
    virtual ~CommonReader();

    /**
     * @brief Create the internal RTPS Reader.
     *
     * @attention this method should be called right after constructor to create enable internal entities.
     * This is required as this object is a Listener that could be called before finishing construction.
     * Other alternatives have been studied but none have really fit for this case.
     *
     * @throw InitializationException if RTPS Reader creation fails
     *
     * @warning this method is not thread safe.
     * @pre this method can only be called once.
     */
    DDSPIPE_PARTICIPANTS_DllAPI
    void init();

    /////////////////////////
    // RTPS LISTENER METHODS
    /////////////////////////

    /**
     * @brief CommonReader Listener callback when a new data is added to History
     *
     * This method is call every time a new CacheChange is received by this CommonReader.
     * Filter this same Participant messages.
     * Call the on_data_available_ callback (method \c on_data_available_ from \c BaseReader ).
     *
     * @param [in] change new change received
     */
    DDSPIPE_PARTICIPANTS_DllAPI
    void on_new_cache_change_added(
            fastdds::rtps::RTPSReader*,
            const fastdds::rtps::CacheChange_t* const change) noexcept override;

    /**
     * @brief CommonReader Listener callback when a new Writer is matched or unmatched
     *
     * This method is call every time a new Writer is matched or unmatched from this CommonReader.
     * It only creates a log for matching and unmatching (in case it is not a writer from this same Participant)
     *
     * @param [in] info information about the matched Writer
     */
    DDSPIPE_PARTICIPANTS_DllAPI
    void on_reader_matched(
            fastdds::rtps::RTPSReader*,
            const fastdds::rtps::MatchingInfo& info) noexcept override;

    /**
     * This method is called when a new Writer is discovered, with a Topic that
     * matches that of a local reader, but with an offered QoS that is incompatible
     * with the one requested by the local reader
     * @param qos A mask with the bits of all incompatible Qos activated.
     */
    DDSPIPE_PARTICIPANTS_DllAPI
    void on_requested_incompatible_qos(
            fastdds::rtps::RTPSReader*,
            fastdds::dds::PolicyMask qos) noexcept override;

    /**
     * This method is called when the reader detects that one or more samples have been lost.
     *
     * @param sample_lost_since_last_update  The number of samples that were lost since the last time this
     *                                       method was called for the same reader.
     */
    DDSPIPE_PARTICIPANTS_DllAPI
    void on_sample_lost(
            fastdds::rtps::RTPSReader*,
            int32_t sample_lost_since_last_update) noexcept override;

    /**
     * This method is called when the reader rejects a samples.
     *
     * @param reason  Indicates reason for sample rejection.
     * @param change  Pointer to the CacheChange_t. This is a const pointer to const data
     *                to indicate that the user should not dispose of this data himself.
     */
    DDSPIPE_PARTICIPANTS_DllAPI
    void on_sample_rejected(
            fastdds::rtps::RTPSReader*,
            eprosima::fastdds::dds::SampleRejectedStatusKind reason,
            const fastdds::rtps::CacheChange_t* const change) noexcept override;

    /**
     * This method is called when a new Writer is discovered, with a Topic that
     * matches the name of a local reader, but with an incompatible type
     *
     * @param reader Pointer to the RTPSReader.
     */
    DDSPIPE_PARTICIPANTS_DllAPI
    void on_incompatible_type(
            fastdds::rtps::RTPSReader* reader) noexcept override;

    /////////////////////////
    // RPC REQUIRED METHODS
    /////////////////////////
    // TODO remove these methods once the double reference is solved

    //! Get GUID of internal RTPS reader
    DDSPIPE_PARTICIPANTS_DllAPI
    core::types::Guid guid() const noexcept override;

    //! Get internal RTPS reader mutex
    DDSPIPE_PARTICIPANTS_DllAPI
    fastdds::RecursiveTimedMutex& get_rtps_mutex() const noexcept override;

    //! Get number of unread cache changes in internal RTPS reader
    DDSPIPE_PARTICIPANTS_DllAPI
    uint64_t get_unread_count() const noexcept override;

    DDSPIPE_PARTICIPANTS_DllAPI
    core::types::DdsTopic topic() const noexcept override;

protected:

    /**
     * @brief Construct a new CommonReader object
     *
     * It receives all the attributes and QoS needed to create the internal entities.
     *
     * @note Only protected so only concrete classes are instantiated.
     *
     * @throw \c InitializationException in case any creation has failed
     */
    DDSPIPE_PARTICIPANTS_DllAPI
    CommonReader(
            const core::types::ParticipantId& participant_id,
            const core::types::DdsTopic& topic,
            const std::shared_ptr<core::PayloadPool>& payload_pool,
            fastdds::rtps::RTPSParticipant* rtps_participant,
            const fastdds::rtps::HistoryAttributes& history_attributes,
            const fastdds::rtps::ReaderAttributes& reader_attributes,
            const fastdds::rtps::TopicDescription& topic_desc,
            const fastdds::dds::ReaderQos& reader_qos);

    // Specific enable/disable do not need to be implemented

    /**
     * @brief Auxiliary method to create the internal RTPS Reader and History.
     */
    DDSPIPE_PARTICIPANTS_DllAPI
    virtual void internal_entities_creation_(
            const fastdds::rtps::HistoryAttributes& history_attributes,
            const fastdds::rtps::ReaderAttributes& reader_attributes,
            const fastdds::rtps::TopicDescription& topic_desc,
            const fastdds::dds::ReaderQos& reader_qos);

    /**
     * @brief Return an allocated object
     *
     * @attention this method allocates memory.
     */
    DDSPIPE_PARTICIPANTS_DllAPI
    virtual core::types::RtpsPayloadData* create_data_(
            const fastdds::rtps::CacheChange_t& received_change) const noexcept;

    /**
     * @brief Auxiliary method used in \c take to fill the received data.
     */
    DDSPIPE_PARTICIPANTS_DllAPI
    virtual void fill_received_data_(
            const fastdds::rtps::CacheChange_t& received_change,
            core::types::RtpsPayloadData& data_to_fill) const noexcept;

    // Specific enable/disable do not need to be implemented

    /**
     * @brief Take specific method
     *
     * Check if there are messages to take.
     * Take next Untaken Change.
     * Set \c data with the message taken (data payload must be stored from PayloadPool).
     * Remove this change from CommonReader History and release.
     *
     * @note guard by mutex \c rtps_mutex_
     *
     * @param data : oldest data to take
     * @return \c RETCODE_OK if data has been correctly taken
     * @return \c RETCODE_NO_DATA if there is no data to send
     * @return \c RETCODE_ERROR if there has been an error reading the data or the data read is corrupted
     */
    DDSPIPE_PARTICIPANTS_DllAPI
    virtual utils::ReturnCode take_nts_(
            std::unique_ptr<core::IRoutingData>& data) noexcept override;

    DDSPIPE_PARTICIPANTS_DllAPI
    virtual void enable_nts_() noexcept override;

    /////
    // RTPS specific methods

    /**
     * @brief Default History Attributes to create CommonReader History
     *
     * @return Default HistoryAttributes
     */
    static fastdds::rtps::HistoryAttributes reckon_history_attributes_(
            const core::types::DdsTopic& topic) noexcept;

    /**
     * @brief Reader Attributes to create RTPS Reader
     */
    static fastdds::rtps::ReaderAttributes reckon_reader_attributes_(
            const core::types::DdsTopic& topic) noexcept;

    //! Topic Description to create RTPS Reader
    fastdds::rtps::TopicDescription reckon_topic_description_(
            const core::types::DdsTopic& topic) noexcept;

    //! Reader QoS to create RTPS Reader
    static fastdds::dds::ReaderQos reckon_reader_qos_(
            const core::types::DdsTopic& topic) noexcept;

    /////
    // CommonReader specific methods

    //! Whether a change received should be processed
    virtual bool should_accept_change_(
            const fastdds::rtps::CacheChange_t* change) noexcept;

    //! Whether a change received is from this Participant (to avoid auto-feedback)
    bool come_from_this_participant_(
            const fastdds::rtps::CacheChange_t* change) const noexcept;

    //! Whether a guid references this Participant (to avoid auto-feedback)
    bool come_from_this_participant_(
            const fastdds::rtps::GUID_t guid) const noexcept;

    utils::ReturnCode is_data_correct_(
            const fastdds::rtps::CacheChange_t* received_change) const noexcept;

    /////
    // EXTERNAL VARIABLES

    //! RTPS Participant
    fastdds::rtps::RTPSParticipant* rtps_participant_;

    /////
    // INTERNAL VARIABLES

    const std::shared_ptr<core::PayloadPool>& payload_pool_;

    //!
    core::types::DdsTopic topic_;

    //! RTPS Reader pointer
    fastdds::rtps::RTPSReader* rtps_reader_;

    //! RTPS Reader History associated to \c rtps_reader_
    fastdds::rtps::ReaderHistory* rtps_history_;

    //! History attributes to create the History for the internal RTPS Reader.
    fastdds::rtps::HistoryAttributes history_attributes_;

    //! Reader attributes to create the internal RTPS Reader.
    fastdds::rtps::ReaderAttributes reader_attributes_;

    //! Topic description to create the internal RTPS Reader.
    fastdds::rtps::TopicDescription topic_description_;

    //! Reader QoS to create the internal RTPS Reader.
    fastdds::dds::ReaderQos reader_qos_;
};

} /* namespace rtps */
} /* namespace participants */
} /* namespace ddspipe */
} /* namespace eprosima */
