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
 * @file float_bounded_sequenceTypeObjectSupport.cxx
 * Source file containing the implementation to register the TypeObject representation of the described types in the IDL file
 *
 * This file was generated by the tool fastddsgen.
 */

#include "float_bounded_sequenceTypeObjectSupport.hpp"

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

#include "float_bounded_sequence.hpp"


using namespace eprosima::fastdds::dds::xtypes;

// TypeIdentifier is returned by reference: dependent structures/unions are registered in this same method
void register_float_bounded_sequence_type_identifier(
        TypeIdentifierPair& type_ids_float_bounded_sequence)
{

    ReturnCode_t return_code_float_bounded_sequence {eprosima::fastdds::dds::RETCODE_OK};
    return_code_float_bounded_sequence =
        eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->type_object_registry().get_type_identifiers(
        "float_bounded_sequence", type_ids_float_bounded_sequence);
    if (eprosima::fastdds::dds::RETCODE_OK != return_code_float_bounded_sequence)
    {
        StructTypeFlag struct_flags_float_bounded_sequence = TypeObjectUtils::build_struct_type_flag(eprosima::fastdds::dds::xtypes::ExtensibilityKind::APPENDABLE,
                false, false);
        QualifiedTypeName type_name_float_bounded_sequence = "float_bounded_sequence";
        eprosima::fastcdr::optional<AppliedBuiltinTypeAnnotations> type_ann_builtin_float_bounded_sequence;
        eprosima::fastcdr::optional<AppliedAnnotationSeq> ann_custom_float_bounded_sequence;
        CompleteTypeDetail detail_float_bounded_sequence = TypeObjectUtils::build_complete_type_detail(type_ann_builtin_float_bounded_sequence, ann_custom_float_bounded_sequence, type_name_float_bounded_sequence.to_string());
        CompleteStructHeader header_float_bounded_sequence;
        header_float_bounded_sequence = TypeObjectUtils::build_complete_struct_header(TypeIdentifier(), detail_float_bounded_sequence);
        CompleteStructMemberSeq member_seq_float_bounded_sequence;
        {
            TypeIdentifierPair type_ids_numbers;
            ReturnCode_t return_code_numbers {eprosima::fastdds::dds::RETCODE_OK};
            return_code_numbers =
                eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->type_object_registry().get_type_identifiers(
                "anonymous_sequence_float_13", type_ids_numbers);

            if (eprosima::fastdds::dds::RETCODE_OK != return_code_numbers)
            {
                return_code_numbers =
                    eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->type_object_registry().get_type_identifiers(
                    "_float", type_ids_numbers);

                if (eprosima::fastdds::dds::RETCODE_OK != return_code_numbers)
                {
                    EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION,
                            "Sequence element TypeIdentifier unknown to TypeObjectRegistry.");
                    return;
                }
                bool element_identifier_anonymous_sequence_float_13_ec {false};
                TypeIdentifier* element_identifier_anonymous_sequence_float_13 {new TypeIdentifier(TypeObjectUtils::retrieve_complete_type_identifier(type_ids_numbers, element_identifier_anonymous_sequence_float_13_ec))};
                if (!element_identifier_anonymous_sequence_float_13_ec)
                {
                    EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION, "Sequence element TypeIdentifier inconsistent.");
                    return;
                }
                EquivalenceKind equiv_kind_anonymous_sequence_float_13 = EK_COMPLETE;
                if (TK_NONE == type_ids_numbers.type_identifier2()._d())
                {
                    equiv_kind_anonymous_sequence_float_13 = EK_BOTH;
                }
                CollectionElementFlag element_flags_anonymous_sequence_float_13 = 0;
                PlainCollectionHeader header_anonymous_sequence_float_13 = TypeObjectUtils::build_plain_collection_header(equiv_kind_anonymous_sequence_float_13, element_flags_anonymous_sequence_float_13);
                {
                    SBound bound = static_cast<SBound>(13);
                    PlainSequenceSElemDefn seq_sdefn = TypeObjectUtils::build_plain_sequence_s_elem_defn(header_anonymous_sequence_float_13, bound,
                                eprosima::fastcdr::external<TypeIdentifier>(element_identifier_anonymous_sequence_float_13));
                    if (eprosima::fastdds::dds::RETCODE_BAD_PARAMETER ==
                            TypeObjectUtils::build_and_register_s_sequence_type_identifier(seq_sdefn, "anonymous_sequence_float_13", type_ids_numbers))
                    {
                        EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION,
                            "anonymous_sequence_float_13 already registered in TypeObjectRegistry for a different type.");
                    }
                }
            }
            StructMemberFlag member_flags_numbers = TypeObjectUtils::build_struct_member_flag(eprosima::fastdds::dds::xtypes::TryConstructFailAction::DISCARD,
                    false, false, false, false);
            MemberId member_id_numbers = 0x00000000;
            bool common_numbers_ec {false};
            CommonStructMember common_numbers {TypeObjectUtils::build_common_struct_member(member_id_numbers, member_flags_numbers, TypeObjectUtils::retrieve_complete_type_identifier(type_ids_numbers, common_numbers_ec))};
            if (!common_numbers_ec)
            {
                EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION, "Structure numbers member TypeIdentifier inconsistent.");
                return;
            }
            MemberName name_numbers = "numbers";
            eprosima::fastcdr::optional<AppliedBuiltinMemberAnnotations> member_ann_builtin_numbers;
            ann_custom_float_bounded_sequence.reset();
            CompleteMemberDetail detail_numbers = TypeObjectUtils::build_complete_member_detail(name_numbers, member_ann_builtin_numbers, ann_custom_float_bounded_sequence);
            CompleteStructMember member_numbers = TypeObjectUtils::build_complete_struct_member(common_numbers, detail_numbers);
            TypeObjectUtils::add_complete_struct_member(member_seq_float_bounded_sequence, member_numbers);
        }
        CompleteStructType struct_type_float_bounded_sequence = TypeObjectUtils::build_complete_struct_type(struct_flags_float_bounded_sequence, header_float_bounded_sequence, member_seq_float_bounded_sequence);
        if (eprosima::fastdds::dds::RETCODE_BAD_PARAMETER ==
                TypeObjectUtils::build_and_register_struct_type_object(struct_type_float_bounded_sequence, type_name_float_bounded_sequence.to_string(), type_ids_float_bounded_sequence))
        {
            EPROSIMA_LOG_ERROR(XTYPES_TYPE_REPRESENTATION,
                    "float_bounded_sequence already registered in TypeObjectRegistry for a different type.");
        }
    }
}

