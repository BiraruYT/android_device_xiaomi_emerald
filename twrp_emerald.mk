#
# Copyright (C) 2024 The LineageOS Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/aosp_base.mk)

# Inherit some common TWRP stuff.
$(call inherit-product, vendor/twrp/config/common.mk)

# Inherit from generic device
$(call inherit-product, device/xiaomi/emerald/device.mk)

PRODUCT_DEVICE := emerald
PRODUCT_NAME := twrp_emerald
PRODUCT_BRAND := Xiaomi
PRODUCT_MODEL := Redmi Note 13 Pro 4G
PRODUCT_MANUFACTURER := xiaomi

PRODUCT_GMS_CLIENTID_BASE := android-xiaomi

#PRODUCT_BUILD_PROP_OVERRIDES += \
    PRIVATE_BUILD_DESC="missi_phone_global-user 14 UP1A.231005.007 V816.0.7.0.UNFMIXM release-keys"

#BUILD_FINGERPRINT := Android/missi_phone_global/missi:14/UP1A.231005.007/V816.0.7.0.UNFMIXM:user/release-keys
