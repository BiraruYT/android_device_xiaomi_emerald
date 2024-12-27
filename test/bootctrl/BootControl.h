/*
* Copyright (C) 2024 The Android Open Source Project
*
* SPDX-License-Identifier: Apache-2.0
*/

#pragma once

#include <android/hardware/boot/1.2/IBootControl.h>
#include <hidl/MQDescriptor.h>
#include <hidl/Status.h>
#include <libboot_control/libboot_control.h>
#include "boot_region_control_private.h"

namespace android {
namespace hardware {
namespace boot {
namespace V1_2 {
namespace implementation {

using ::android::hardware::Return;
using ::android::hardware::Void;

using ::android::hardware::boot::V1_2::IBootControl;
using ::android::hardware::boot::V1_1::MergeStatus;
using ::android::hardware::boot::V1_0::BoolResult;

class BootControl : public IBootControl {
  public:
    bool Init();

    // Methods from ::android::hardware::boot::V1_0::IBootControl follow.
    Return<uint32_t> getNumberSlots() override;
    Return<uint32_t> getCurrentSlot() override;
    Return<void> markBootSuccessful(markBootSuccessful_cb _hidl_cb) override;
    Return<void> setActiveBootSlot(uint32_t slot, setActiveBootSlot_cb _hidl_cb) override;
    Return<void> setSlotAsUnbootable(uint32_t slot, setSlotAsUnbootable_cb _hidl_cb) override;
    Return<BoolResult> isSlotBootable(uint32_t slot) override;
    Return<BoolResult> isSlotMarkedSuccessful(uint32_t slot) override;
    Return<void> getSuffix(uint32_t slot, getSuffix_cb _hidl_cb) override;

    // Methods from ::android::hardware::boot::V1_1::IBootControl follow.
    Return<bool> setSnapshotMergeStatus(MergeStatus status) override;
    Return<MergeStatus> getSnapshotMergeStatus() override;

    // Methods from ::android::hardware::boot::V1_2::IBootControl follow.
    Return<uint32_t> getActiveBootSlot() override;

  private:
    android::bootable::BootControl impl_;
    android::bootable::BootControlExt implext_;
    Return<void> clearAvbbctlFlag();
};

extern "C" IBootControl* HIDL_FETCH_IBootControl(const char* name);

}  // namespace implementation
}  // namespace V1_2
}  // namespace boot
}  // namespace hardware
}  // namespace android