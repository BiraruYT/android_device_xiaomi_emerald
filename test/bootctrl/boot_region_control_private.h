/*
* Copyright (C) 2024 The Android Open Source Project
*
* SPDX-License-Identifier: Apache-2.0
*/

#pragma once

namespace android {
namespace bootable {
class BootControlExt {
  public:
    bool SetBootRegionSlot(unsigned int slot);
};
}
}