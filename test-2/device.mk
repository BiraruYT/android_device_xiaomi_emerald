#
# Copyright (C) 2024 The Android Open Source Project
#
# SPDX-License-Identifier: Apache-2.0
#

LOCAL_PATH := device/xiaomi/emerald

# Dynamic Partitions
PRODUCT_USE_DYNAMIC_PARTITIONS := true

# Virtual A/B
ENABLE_VIRTUAL_AB := true
$(call inherit-product, $(SRC_TARGET_DIR)/product/virtual_ab_ota.mk)

# A/B
AB_OTA_POSTINSTALL_CONFIG += \
    RUN_POSTINSTALL_system=true \
    POSTINSTALL_PATH_system=system/bin/otapreopt_script \
    FILESYSTEM_TYPE_system=ext4 \
    POSTINSTALL_OPTIONAL_system=true

# Update Engine & Verifier
PRODUCT_PACKAGES += \
    update_engine \
    update_verifier \
    update_engine_sideload

# Boot control HAL
PRODUCT_PACKAGES += \
    android.hardware.boot@1.2-impl \
    android.hardware.boot@1.2-impl.recovery \
    android.hardware.boot@1.2-service
PRODUCT_PACKAGES_DEBUG += \
    bootctrl
PRODUCT_PACKAGES += \
    bootctrl.mt6789 \
    bootctrl.mt6789.recovery
PRODUCT_PACKAGES += \
    create_pl_dev \
    create_pl_dev.recovery

# Health HAL
PRODUCT_PACKAGES += \
    android.hardware.health@2.1-impl \
    android.hardware.health@2.1-service

# Soong
PRODUCT_SOONG_NAMESPACES += \
    $(LOCAL_PATH)

# Fastbootd
PRODUCT_PACKAGES += \
    android.hardware.fastboot@1.1-impl-mock \
    fastbootd

# API
PRODUCT_SHIPPING_API_LEVEL := 32

# VNDK
PRODUCT_TARGET_VNDK_VERSION := 33

# Additional Libraries
TARGET_RECOVERY_DEVICE_MODULES += \
    libkeymaster4 \
    libkeymaster41 \
    libpuresoftkeymasterdevice
RECOVERY_LIBRARY_SOURCE_FILES += \
    $(TARGET_OUT_SHARED_LIBRARIES)/libkeymaster4.so \
    $(TARGET_OUT_SHARED_LIBRARIES)/libkeymaster41.so \
    $(TARGET_OUT_SHARED_LIBRARIES)/libpuresoftkeymasterdevice.so

# Depricated
#PRODUCT_STATIC_BOOT_CONTROL_HAL := \
    bootctrl.mt6789 \
    libgptutils \
    libz \
    libcutils