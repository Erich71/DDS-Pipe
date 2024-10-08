// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

/*!
 * @file MonitoringStatusTypeObjectSupport.cxx
 * Source file containing the implementation to register the TypeObject representation of the described types in the IDL file
 *
 * This file was generated by the tool fastddsgen.
 */

#include <ddspipe_core/types/monitoring/status/MonitoringStatusTypeObjectSupport.hpp>

#include <mutex>
#include <string>

#include <fastcdr/xcdr/external.hpp>
#include <fastcdr/xcdr/optional.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/log/Log.hpp>
#include <fastdds/dds/xtypes/common.hpp>
#include <fastdds/dds/xtypes/type_representation/ITypeObjectRegistry.hpp>
#include <fastdds/dds/xtypes/type_representation/TypeObject.hpp>
#include <fastdds/dds/xtypes/type_representation/TypeObjectUtils.hpp>

#include <ddspipe_core/types/monitoring/status/MonitoringStatus.hpp>


using namespace eprosima::fastdds::dds::xtypes;

// TypeIdentifier is returned by reference: dependent structures/unions are registered in this same method
void register_MonitoringErrorStatus_type_identifier(
        TypeIdentifierPair& type_ids_MonitoringErrorStatus)
{

    ReturnCode_t return_code_MonitoringErrorStatus {eprosima::fastdds::dds::RETCODE_OK};
    return_code_MonitoringErrorStatus =
        eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->type_object_registry().get_type_identifiers(
        "MonitoringErrorStatus", type_ids_MonitoringErrorStatus);
    if (eprosima::fastdds::dds::RETCODE_OK != return_code_MonitoringErrorStatus)
    {
        StructTypeFlag struct_flags_MonitoringErrorStatus = TypeObjectUtils::build_struct_type_flag(eprosima::fastdds::dds::xtypes::ExtensibilityKind::APPENDABLE,
                false, false);
        QualifiedTypeName type_name_MonitoringErrorStatus = "MonitoringErrorStatus";
        eprosima::fastcdr::optional<AppliedBuiltinTypeAnnotations> type_ann_builtin_MonitoringErrorStatus;
        eprosima::fastcdr::optional<AppliedAnnotationSeq> ann_custom_MonitoringErrorStatus;
        CompleteTypeDetail detail_MonitoringErrorStatus = TypeObjectUtils::build_complete_type_detail(type_ann_builtin_MonitoringErrorStatus, ann_custom_MonitoringErrorStatus, type_name_MonitoringErrorStatus.to_string());
        CompleteStructHeader header_MonitoringErrorStatus;
        header_MonitoringErrorStatus = TypeObjectUtils::build_complete_struct_header(TypeIdentifier(), detail_MonitoringErrorStatus);
        CompleteStructMemberSeq member_seq_MonitoringErrorStatus;
        {
            TypeIdentifierPair type_ids_type_mismatch;
            ReturnCode_t return_code_type_mismatch {eprosima::fastdds::dds::RETCODE_OK};
            return_code_type_mismatch =
                eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->type_object_registry().get_type_identifiers(
                "_bool", type_ids_type_mismatch);

            if (eprosima::fastdds::dds::RETCODE_OK != return_code_type_mismatch)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION,
                        "type_mismatch Structure member TypeIdentifier unknown to TypeObjectRegistry.");
                return;
            }
            StructMemberFlag member_flags_type_mismatch = TypeObjectUtils::build_struct_member_flag(eprosima::fastdds::dds::xtypes::TryConstructFailAction::DISCARD,
                    false, false, false, false);
            MemberId member_id_type_mismatch = 0x00000000;
            bool common_type_mismatch_ec {false};
            CommonStructMember common_type_mismatch {TypeObjectUtils::build_common_struct_member(member_id_type_mismatch, member_flags_type_mismatch, TypeObjectUtils::retrieve_complete_type_identifier(type_ids_type_mismatch, common_type_mismatch_ec))};
            if (!common_type_mismatch_ec)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION, "Structure type_mismatch member TypeIdentifier inconsistent.");
                return;
            }
            MemberName name_type_mismatch = "type_mismatch";
            eprosima::fastcdr::optional<AppliedBuiltinMemberAnnotations> member_ann_builtin_type_mismatch;
            ann_custom_MonitoringErrorStatus.reset();
            CompleteMemberDetail detail_type_mismatch = TypeObjectUtils::build_complete_member_detail(name_type_mismatch, member_ann_builtin_type_mismatch, ann_custom_MonitoringErrorStatus);
            CompleteStructMember member_type_mismatch = TypeObjectUtils::build_complete_struct_member(common_type_mismatch, detail_type_mismatch);
            TypeObjectUtils::add_complete_struct_member(member_seq_MonitoringErrorStatus, member_type_mismatch);
        }
        {
            TypeIdentifierPair type_ids_qos_mismatch;
            ReturnCode_t return_code_qos_mismatch {eprosima::fastdds::dds::RETCODE_OK};
            return_code_qos_mismatch =
                eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->type_object_registry().get_type_identifiers(
                "_bool", type_ids_qos_mismatch);

            if (eprosima::fastdds::dds::RETCODE_OK != return_code_qos_mismatch)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION,
                        "qos_mismatch Structure member TypeIdentifier unknown to TypeObjectRegistry.");
                return;
            }
            StructMemberFlag member_flags_qos_mismatch = TypeObjectUtils::build_struct_member_flag(eprosima::fastdds::dds::xtypes::TryConstructFailAction::DISCARD,
                    false, false, false, false);
            MemberId member_id_qos_mismatch = 0x00000001;
            bool common_qos_mismatch_ec {false};
            CommonStructMember common_qos_mismatch {TypeObjectUtils::build_common_struct_member(member_id_qos_mismatch, member_flags_qos_mismatch, TypeObjectUtils::retrieve_complete_type_identifier(type_ids_qos_mismatch, common_qos_mismatch_ec))};
            if (!common_qos_mismatch_ec)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION, "Structure qos_mismatch member TypeIdentifier inconsistent.");
                return;
            }
            MemberName name_qos_mismatch = "qos_mismatch";
            eprosima::fastcdr::optional<AppliedBuiltinMemberAnnotations> member_ann_builtin_qos_mismatch;
            ann_custom_MonitoringErrorStatus.reset();
            CompleteMemberDetail detail_qos_mismatch = TypeObjectUtils::build_complete_member_detail(name_qos_mismatch, member_ann_builtin_qos_mismatch, ann_custom_MonitoringErrorStatus);
            CompleteStructMember member_qos_mismatch = TypeObjectUtils::build_complete_struct_member(common_qos_mismatch, detail_qos_mismatch);
            TypeObjectUtils::add_complete_struct_member(member_seq_MonitoringErrorStatus, member_qos_mismatch);
        }
        CompleteStructType struct_type_MonitoringErrorStatus = TypeObjectUtils::build_complete_struct_type(struct_flags_MonitoringErrorStatus, header_MonitoringErrorStatus, member_seq_MonitoringErrorStatus);
        if (eprosima::fastdds::dds::RETCODE_BAD_PARAMETER ==
                TypeObjectUtils::build_and_register_struct_type_object(struct_type_MonitoringErrorStatus, type_name_MonitoringErrorStatus.to_string(), type_ids_MonitoringErrorStatus))
        {
            EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION,
                    "MonitoringErrorStatus already registered in TypeObjectRegistry for a different type.");
        }
    }
}
// TypeIdentifier is returned by reference: dependent structures/unions are registered in this same method
void register_MonitoringStatus_type_identifier(
        TypeIdentifierPair& type_ids_MonitoringStatus)
{

    ReturnCode_t return_code_MonitoringStatus {eprosima::fastdds::dds::RETCODE_OK};
    return_code_MonitoringStatus =
        eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->type_object_registry().get_type_identifiers(
        "MonitoringStatus", type_ids_MonitoringStatus);
    if (eprosima::fastdds::dds::RETCODE_OK != return_code_MonitoringStatus)
    {
        StructTypeFlag struct_flags_MonitoringStatus = TypeObjectUtils::build_struct_type_flag(eprosima::fastdds::dds::xtypes::ExtensibilityKind::APPENDABLE,
                false, false);
        QualifiedTypeName type_name_MonitoringStatus = "MonitoringStatus";
        eprosima::fastcdr::optional<AppliedBuiltinTypeAnnotations> type_ann_builtin_MonitoringStatus;
        eprosima::fastcdr::optional<AppliedAnnotationSeq> ann_custom_MonitoringStatus;
        CompleteTypeDetail detail_MonitoringStatus = TypeObjectUtils::build_complete_type_detail(type_ann_builtin_MonitoringStatus, ann_custom_MonitoringStatus, type_name_MonitoringStatus.to_string());
        CompleteStructHeader header_MonitoringStatus;
        header_MonitoringStatus = TypeObjectUtils::build_complete_struct_header(TypeIdentifier(), detail_MonitoringStatus);
        CompleteStructMemberSeq member_seq_MonitoringStatus;
        {
            TypeIdentifierPair type_ids_error_status;
            ReturnCode_t return_code_error_status {eprosima::fastdds::dds::RETCODE_OK};
            return_code_error_status =
                eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->type_object_registry().get_type_identifiers(
                "MonitoringErrorStatus", type_ids_error_status);

            if (eprosima::fastdds::dds::RETCODE_OK != return_code_error_status)
            {
            ::register_MonitoringErrorStatus_type_identifier(type_ids_error_status);
            }
            StructMemberFlag member_flags_error_status = TypeObjectUtils::build_struct_member_flag(eprosima::fastdds::dds::xtypes::TryConstructFailAction::DISCARD,
                    false, false, false, false);
            MemberId member_id_error_status = 0x00000000;
            bool common_error_status_ec {false};
            CommonStructMember common_error_status {TypeObjectUtils::build_common_struct_member(member_id_error_status, member_flags_error_status, TypeObjectUtils::retrieve_complete_type_identifier(type_ids_error_status, common_error_status_ec))};
            if (!common_error_status_ec)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION, "Structure error_status member TypeIdentifier inconsistent.");
                return;
            }
            MemberName name_error_status = "error_status";
            eprosima::fastcdr::optional<AppliedBuiltinMemberAnnotations> member_ann_builtin_error_status;
            ann_custom_MonitoringStatus.reset();
            CompleteMemberDetail detail_error_status = TypeObjectUtils::build_complete_member_detail(name_error_status, member_ann_builtin_error_status, ann_custom_MonitoringStatus);
            CompleteStructMember member_error_status = TypeObjectUtils::build_complete_struct_member(common_error_status, detail_error_status);
            TypeObjectUtils::add_complete_struct_member(member_seq_MonitoringStatus, member_error_status);
        }
        {
            TypeIdentifierPair type_ids_has_errors;
            ReturnCode_t return_code_has_errors {eprosima::fastdds::dds::RETCODE_OK};
            return_code_has_errors =
                eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->type_object_registry().get_type_identifiers(
                "_bool", type_ids_has_errors);

            if (eprosima::fastdds::dds::RETCODE_OK != return_code_has_errors)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION,
                        "has_errors Structure member TypeIdentifier unknown to TypeObjectRegistry.");
                return;
            }
            StructMemberFlag member_flags_has_errors = TypeObjectUtils::build_struct_member_flag(eprosima::fastdds::dds::xtypes::TryConstructFailAction::DISCARD,
                    false, false, false, false);
            MemberId member_id_has_errors = 0x00000001;
            bool common_has_errors_ec {false};
            CommonStructMember common_has_errors {TypeObjectUtils::build_common_struct_member(member_id_has_errors, member_flags_has_errors, TypeObjectUtils::retrieve_complete_type_identifier(type_ids_has_errors, common_has_errors_ec))};
            if (!common_has_errors_ec)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION, "Structure has_errors member TypeIdentifier inconsistent.");
                return;
            }
            MemberName name_has_errors = "has_errors";
            eprosima::fastcdr::optional<AppliedBuiltinMemberAnnotations> member_ann_builtin_has_errors;
            ann_custom_MonitoringStatus.reset();
            CompleteMemberDetail detail_has_errors = TypeObjectUtils::build_complete_member_detail(name_has_errors, member_ann_builtin_has_errors, ann_custom_MonitoringStatus);
            CompleteStructMember member_has_errors = TypeObjectUtils::build_complete_struct_member(common_has_errors, detail_has_errors);
            TypeObjectUtils::add_complete_struct_member(member_seq_MonitoringStatus, member_has_errors);
        }
        CompleteStructType struct_type_MonitoringStatus = TypeObjectUtils::build_complete_struct_type(struct_flags_MonitoringStatus, header_MonitoringStatus, member_seq_MonitoringStatus);
        if (eprosima::fastdds::dds::RETCODE_BAD_PARAMETER ==
                TypeObjectUtils::build_and_register_struct_type_object(struct_type_MonitoringStatus, type_name_MonitoringStatus.to_string(), type_ids_MonitoringStatus))
        {
            EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION,
                    "MonitoringStatus already registered in TypeObjectRegistry for a different type.");
        }
    }
}

