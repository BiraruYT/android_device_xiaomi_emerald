#
# Copyright (C) 2024 The Android Open Source Project
#
# SPDX-License-Identifier: Apache-2.0
#

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

# Inherit some common TWRP stuff.
$(call inherit-product, vendor/twrp/config/common.mk)

# Inherit from emerald device
$(call inherit-product, device/xiaomi/emerald/device.mk)

PRODUCT_DEVICE := emerald
PRODUCT_NAME := twrp_emerald
PRODUCT_RELEASE_NAME := emerald
PRODUCT_BRAND := Xiaomi
PRODUCT_MODEL := Redmi Note 13 Pro 4G
PRODUCT_MANUFACTURER := xiaomi
PRODUCT_GMS_CLIENTID_BASE := android-xiaomi

#PRODUCT_BUILD_PROP_OVERRIDES += \
    PRIVATE_BUILD_DESC="emerald-user 12 SP1A.210812.016 V816.0.7.0.UNFMIXM release-keys"
#BUILD_FINGERPRINT := Redmi/emerald/emerald:12/SP1A.210812.016/V816.0.7.0.UNFMIXM:user/release-keys