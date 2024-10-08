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

#include <fastdds/rtps/transport/UDPv4TransportDescriptor.hpp>
#include <fastdds/rtps/transport/UDPv6TransportDescriptor.hpp>
#include <fastdds/rtps/transport/TCPv4TransportDescriptor.hpp>
#include <fastdds/rtps/transport/TCPv6TransportDescriptor.hpp>

#include <cpp_utils/exception/ConfigurationException.hpp>
#include <cpp_utils/Log.hpp>

#include <ddspipe_participants/participant/rtps/InitialPeersParticipant.hpp>

namespace eprosima {
namespace ddspipe {
namespace participants {
namespace rtps {

InitialPeersParticipant::InitialPeersParticipant(
        const std::shared_ptr<InitialPeersParticipantConfiguration>& participant_configuration,
        const std::shared_ptr<core::PayloadPool>& payload_pool,
        const std::shared_ptr<core::DiscoveryDatabase>& discovery_database)
    : CommonParticipant(
        participant_configuration,
        payload_pool,
        discovery_database,
        participant_configuration->domain)
{
}

fastdds::rtps::RTPSParticipantAttributes InitialPeersParticipant::reckon_participant_attributes_() const
{
    // Use default as base attributes
    fastdds::rtps::RTPSParticipantAttributes params = CommonParticipant::reckon_participant_attributes_();

    std::shared_ptr<InitialPeersParticipantConfiguration> initial_peers_configuration =
            std::dynamic_pointer_cast<InitialPeersParticipantConfiguration>(configuration_);

    if (initial_peers_configuration == nullptr)
    {
        throw utils::ConfigurationException(
                  "Failed to cast ParticipantConfiguration to InitialPeersParticipantConfiguration.");
    }

    // Auxiliary variable to save characters and improve readability
    const auto& tls_config = initial_peers_configuration->tls_configuration;

    // Needed values to check at the end if descriptor must be set
    bool has_listening_addresses = false;
    bool has_listening_tcp_ipv4 = false;
    bool has_listening_tcp_ipv6 = false;
    bool has_connection_tcp_ipv4 = false;
    bool has_connection_tcp_ipv6 = false;
    bool has_connection_udp_ipv4 = false;
    bool has_connection_udp_ipv6 = false;
    bool has_udp_ipv4 = false;
    bool has_udp_ipv6 = false;

    params.useBuiltinTransports = false;

    /////
    // Set listening addresses
    for (const types::Address& address : initial_peers_configuration->listening_addresses)
    {
        if (!address.is_valid())
        {
            // Invalid address, continue with next one
            EPROSIMA_LOG_WARNING(DDSPIPE_INITIALPEERS_PARTICIPANT,
                    "Discard listening address: " << address <<
                    " in Participant " << initial_peers_configuration->id << " initialization.");
            continue;
        }

        has_listening_addresses = true;

        // TCP Listening WAN address
        if (address.is_tcp())
        {
            if (address.is_ipv4())
            {
                has_listening_tcp_ipv4 = true;

                std::shared_ptr<eprosima::fastdds::rtps::TCPv4TransportDescriptor> descriptor;

                // We check if several descriptors share a WAN address.
                // If so, we add a new port to the previously created descriptor.
                bool same_wan_addr = false;

                auto it = params.userTransports.begin();
                while (it != params.userTransports.end())
                {
                    std::shared_ptr<eprosima::fastdds::rtps::TCPv4TransportDescriptor> tmp_descriptor =
                            std::dynamic_pointer_cast<eprosima::fastdds::rtps::TCPv4TransportDescriptor>(*it);

                    if ((tmp_descriptor != nullptr) && (address.ip() == tmp_descriptor->get_WAN_address()))
                    {
                        // Save in the new descriptor the previously added descriptor with the same WAN address
                        descriptor = tmp_descriptor;
                        // Set that a descriptor with same WAN address was found
                        same_wan_addr = true;
                        // Remove the previously added descriptor as this will be replaced by the same one updated with
                        // more locators.
                        params.userTransports.erase(it);
                        break;
                    }
                }

                // Add the new locator to the descriptor if another with the same wan address was found
                if (same_wan_addr)
                {
                    descriptor->add_listener_port(address.port());
                }
                else
                {
                    descriptor = create_descriptor<eprosima::fastdds::rtps::TCPv4TransportDescriptor>(
                        initial_peers_configuration->whitelist);
                    descriptor->add_listener_port(address.port());
                    descriptor->set_WAN_address(address.ip());

                    // Enable TLS
                    if (tls_config.is_active())
                    {
                        tls_config.enable_tls(descriptor);
                    }

                }

                params.userTransports.push_back(descriptor);
            }
            else
            {
                has_listening_tcp_ipv6 = true;

                std::shared_ptr<eprosima::fastdds::rtps::TCPv6TransportDescriptor> descriptor =
                        create_descriptor<eprosima::fastdds::rtps::TCPv6TransportDescriptor>(
                    initial_peers_configuration->whitelist);

                descriptor->add_listener_port(address.port());

                // Enable TLS
                if (tls_config.is_active())
                {
                    tls_config.enable_tls(descriptor);
                }

                params.userTransports.push_back(descriptor);
            }
        }
        else
        {
            has_udp_ipv4 = address.is_ipv4();
            has_udp_ipv6 = !address.is_ipv4();
        }

        // For any, UDP or TCP
        // Create Locator
        eprosima::fastdds::rtps::Locator_t locator;
        locator.kind = address.get_locator_kind();

        // IP
        if (address.is_ipv4())
        {
            eprosima::fastdds::rtps::IPLocator::setIPv4(locator, address.ip());
        }
        else
        {
            eprosima::fastdds::rtps::IPLocator::setIPv6(locator, address.ip());
        }

        // Set Logical port for every locator
        eprosima::fastdds::rtps::IPLocator::setPhysicalPort(locator, address.port());

        // In TCP case, set Physical port
        if (address.is_tcp())
        {
            // Server side
            // Internal local port is the one passed to add_listener_port (port value).
            // If external port is not defined, it gets internal port value. Therefore, the physical
            // port announced is equal to the internal port.
            // If external port is defined, announced port is external port. This is the one clients,
            // should try to connect, which should match network router public port.
            eprosima::fastdds::rtps::IPLocator::setPhysicalPort(locator, address.external_port());
            eprosima::fastdds::rtps::IPLocator::setLogicalPort(locator, 0);
        }

        // Add listening address to builtin
        params.builtin.metatrafficUnicastLocatorList.push_back(locator);
        params.defaultUnicastLocatorList.push_back(locator);

        logDebug(DDSPIPE_INITIALPEERS_PARTICIPANT,
                "Add listening address " << address << " to Participant " << initial_peers_configuration->id << ".");
    }

    /////
    // Set connection addresses
    for (const types::Address& connection_address : initial_peers_configuration->connection_addresses)
    {
        if (!connection_address.is_valid())
        {
            // Invalid connection address, continue with next one
            EPROSIMA_LOG_WARNING(DDSPIPE_INITIALPEERS_PARTICIPANT,
                    "Discard connection address: " << connection_address <<
                    " in Participant " << initial_peers_configuration->id << " initialization.");
            continue;
        }

        // Create Locator for connection initial peers
        eprosima::fastdds::rtps::Locator_t locator;

        // KIND
        locator.kind = connection_address.get_locator_kind();

        // In case it is TCP mark has_connection_tcp as true
        if (connection_address.is_tcp())
        {
            has_connection_tcp_ipv4 = connection_address.is_ipv4();
            has_connection_tcp_ipv6 = !connection_address.is_ipv4();
        }
        else
        {
            has_connection_udp_ipv4 = connection_address.is_ipv4();
            has_connection_udp_ipv6 = !connection_address.is_ipv4();
            has_udp_ipv4 = connection_address.is_ipv4();
            has_udp_ipv6 = !connection_address.is_ipv4();
        }

        // IP
        if (connection_address.is_ipv4())
        {
            eprosima::fastdds::rtps::IPLocator::setIPv4(locator, connection_address.ip());
        }
        else
        {
            eprosima::fastdds::rtps::IPLocator::setIPv6(locator, connection_address.ip());
        }

        // Set Physical port for every locator
        eprosima::fastdds::rtps::IPLocator::setPhysicalPort(locator, connection_address.port());

        // TCP client side
        // Initial peer physical port must match server's public port. If server specified an external port,
        // client port value must be server's external port. Client's external port have no effect.

        // In TCP case, set Logical port
        if (connection_address.is_tcp())
        {
            eprosima::fastdds::rtps::IPLocator::setLogicalPort(locator, 0);
        }

        // Add it to builtin
        params.builtin.initialPeersList.push_back(locator);

        logDebug(DDSPIPE_INITIALPEERS_PARTICIPANT,
                "Add connection address " << connection_address <<
                " to Participant " << initial_peers_configuration->id << ".");
    }

    /////
    // Create specific descriptors if needed

    // If has TCP connections but not TCP listening addresses, it must specify the TCP transport
    if (has_connection_tcp_ipv4 && !has_listening_tcp_ipv4)
    {
        std::shared_ptr<eprosima::fastdds::rtps::TCPv4TransportDescriptor> descriptor =
                create_descriptor<eprosima::fastdds::rtps::TCPv4TransportDescriptor>(
            initial_peers_configuration->whitelist);

        // Enable TLS
        if (tls_config.is_active())
        {
            tls_config.enable_tls(descriptor, true);
        }

        params.userTransports.push_back(descriptor);

        logDebug(DDSPIPE_INITIALPEERS_PARTICIPANT,
                "Adding TCPv4 Transport to Participant " << initial_peers_configuration->id << ".");
    }

    if (has_connection_tcp_ipv6 && !has_listening_tcp_ipv6)
    {
        std::shared_ptr<eprosima::fastdds::rtps::TCPv6TransportDescriptor> descriptor =
                create_descriptor<eprosima::fastdds::rtps::TCPv6TransportDescriptor>(
            initial_peers_configuration->whitelist);

        // Enable TLS
        if (tls_config.is_active())
        {
            tls_config.enable_tls(descriptor, true);
        }

        params.userTransports.push_back(descriptor);

        logDebug(DDSPIPE_INITIALPEERS_PARTICIPANT,
                "Adding TCPv6 Transport to Participant " << initial_peers_configuration->id << ".");
    }

    // If has UDP, create descriptor because it has not been created yet
    if (has_udp_ipv4)
    {
        std::shared_ptr<eprosima::fastdds::rtps::UDPv4TransportDescriptor> descriptor =
                create_descriptor<eprosima::fastdds::rtps::UDPv4TransportDescriptor>(
            initial_peers_configuration->whitelist);
        params.userTransports.push_back(descriptor);

        logDebug(DDSPIPE_INITIALPEERS_PARTICIPANT,
                "Adding UDPv4 Transport to Participant " << initial_peers_configuration->id << ".");
    }

    if (has_udp_ipv6)
    {
        std::shared_ptr<eprosima::fastdds::rtps::UDPv6TransportDescriptor> descriptor_v6 =
                create_descriptor<eprosima::fastdds::rtps::UDPv6TransportDescriptor>(
            initial_peers_configuration->whitelist);
        params.userTransports.push_back(descriptor_v6);

        logDebug(DDSPIPE_INITIALPEERS_PARTICIPANT,
                "Adding UDPv6 Transport to Participant " << initial_peers_configuration->id << ".");
    }

    // To avoid creating a multicast transport in UDP when non listening addresses
    // Fast requires an empty locator that will be set by default afterwards
    if (!has_listening_addresses)
    {
        if (has_connection_udp_ipv4)
        {
            eprosima::fastdds::rtps::Locator_t locator;
            locator.kind = LOCATOR_KIND_UDPv4;
            params.builtin.metatrafficUnicastLocatorList.push_back(locator);
        }

        if (has_connection_udp_ipv6)
        {
            eprosima::fastdds::rtps::Locator_t locator;
            locator.kind = LOCATOR_KIND_UDPv6;
            params.builtin.metatrafficUnicastLocatorList.push_back(locator);
        }
    }

    logDebug(DDSPIPE_INITIALPEERS_PARTICIPANT,
            "Configured Participant " << initial_peers_configuration->id);

    return params;
}

} /* namespace rtps */
} /* namespace participants */
} /* namespace ddspipe */
} /* namespace eprosima */
