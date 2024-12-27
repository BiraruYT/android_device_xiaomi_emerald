/*
* Copyright (C) 2024 The Android Open Source Project
*
* SPDX-License-Identifier: Apache-2.0
*/

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <string>
#include <android-base/logging.h>

#if !defined(ARCH_X86)
#include <ufs-mtk-ioctl.h>
#include <sys/ioctl.h>
#endif

#include "boot_region_control_private.h"

namespace android {
namespace bootable {
#if !defined(ARCH_X86)
static bool ufs_set_active_boot_part(int boot)
{
    struct ufs_ioctl_query_data idata;
    unsigned char buf[1];
    int fd, ret = true;

    fd = open("/dev/block/sdc", O_RDWR);
    if (fd < 0) {
        printf("%s: open device failed, err: %d\n", __func__, fd);
        return false;
    }

    buf[0] = boot;           /* 1: BootLU A, 2: BootLU B */

    idata.opcode = UPIU_QUERY_OPCODE_WRITE_ATTR;
    idata.idn = QUERY_ATTR_IDN_BOOT_LUN_EN;
    idata.idx = 0;
    idata.buf_ptr = &buf[0];
    idata.buf_byte = 1;

    if (ioctl(fd, UFS_IOCTL_QUERY, &idata) < 0) {
      LOG(ERROR) << "ufs_set boot_part fail";
      ret = false;
    }
    close(fd);
    return ret;
}

bool BootControlExt::SetBootRegionSlot(unsigned int slot) {
  int boot_part = 0;


  LOG(ERROR) << "setActiveBootSlot SetBootRegionSlot " << slot;
  /* slot 0 is A , slot 1 is B */
  if (slot >= 2) {
    LOG(ERROR) << "Wrong Slot value " << slot;
    return 0;
  }

  if(slot)
    boot_part = 2;
  else
    boot_part = 1;

  if (!ufs_set_active_boot_part(boot_part))
      return false;

  return true;
}
#else
bool BootControlExt::SetBootRegionSlot(unsigned int slot) {
  return true;
}
#endif //#if !defined(ARCH_X86)
}
}