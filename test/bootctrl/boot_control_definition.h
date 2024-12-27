/*
* Copyright (C) 2024 The Android Open Source Project
*
* SPDX-License-Identifier: Apache-2.0
*/

struct bootloader_message_ab {
    struct bootloader_message message;
    char slot_suffix[32];
    char update_channel[128];

    // Round up the entire struct to 4096-byte.
    char reserved[1888];
};

/**
 * Be cautious about the struct size change, in case we put anything post
 * bootloader_message_ab struct (b/29159185).
 */
#if (__STDC_VERSION__ >= 201112L) || defined(__cplusplus)
static_assert(sizeof(struct bootloader_message_ab) == 4096,
              "struct bootloader_message_ab size changes");
#endif

#define BOOT_CTRL_MAGIC   0x42414342 /* Bootloader Control AB */
#define BOOT_CTRL_VERSION 1

struct slot_metadata {
    // Slot priority with 15 meaning highest priority, 1 lowest
    // priority and 0 the slot is unbootable.
    uint8_t priority : 4;
    // Number of times left attempting to boot this slot.
    uint8_t tries_remaining : 3;
    // 1 if this slot has booted successfully, 0 otherwise.
    uint8_t successful_boot : 1;
    // 1 if this slot is corrupted from a dm-verity corruption, 0
    // otherwise.
    uint8_t verity_corrupted : 1;
    // Reserved for further use.
    uint8_t reserved : 7;
} __attribute__((packed));

/* Bootloader Control AB
 *
 * This struct can be used to manage A/B metadata. It is designed to
 * be put in the 'slot_suffix' field of the 'bootloader_message'
 * structure described above. It is encouraged to use the
 * 'bootloader_control' structure to store the A/B metadata, but not
 * mandatory.
 */
struct bootloader_control {
    // NUL terminated active slot suffix.
    char slot_suffix[4];
    // Bootloader Control AB magic number (see BOOT_CTRL_MAGIC).
    uint32_t magic;
    // Version of struct being used (see BOOT_CTRL_VERSION).
    uint8_t version;
    // Number of slots being managed.
    uint8_t nb_slot : 3;
    // Number of times left attempting to boot recovery.
    uint8_t recovery_tries_remaining : 3;
    // Status of any pending snapshot merge of dynamic partitions.
    uint8_t merge_status : 3;
    // Ensure 4-bytes alignment for slot_info field.
    uint8_t reserved0[1];
    // Per-slot information.  Up to 4 slots.
    struct slot_metadata slot_info[4];
    // Reserved for further use.
    uint8_t reserved1[8];
    // CRC32 of all 28 bytes preceding this field (little endian
    // format).
    uint32_t crc32_le;
} __attribute__((packed));

#if (__STDC_VERSION__ >= 201112L) || defined(__cplusplus)
static_assert(sizeof(struct bootloader_control) ==
              sizeof(((struct bootloader_message_ab *)0)->slot_suffix),
              "struct bootloader_control has wrong size");
#endif

namespace android {
namespace bootable {
    bool UpdateAndSaveBootloaderControl(const std::string& misc_device, bootloader_control* buffer);
    bool LoadBootloaderControl(const std::string& misc_device, bootloader_control* buffer);
    uint32_t BootloaderControlLECRC(const bootloader_control* boot_ctrl);
}
}