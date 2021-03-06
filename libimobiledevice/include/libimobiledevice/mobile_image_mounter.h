/**
 * @file libimobiledevice/mobile_image_mounter.h
 * @brief Mount developer/debug disk images on the device.
 * \internal
 *
 * Copyright (c) 2010 Nikias Bassen All Rights Reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef IMOBILE_IMAGE_MOUNTER_H
#define IMOBILE_IMAGE_MOUNTER_H

#include "exports.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>

#define MOBILE_IMAGE_MOUNTER_SERVICE_NAME "com.apple.mobile.mobile_image_mounter"
/** @name Error Codes */
/*@{*/
#define MOBILE_IMAGE_MOUNTER_E_SUCCESS                0
#define MOBILE_IMAGE_MOUNTER_E_INVALID_ARG           -1
#define MOBILE_IMAGE_MOUNTER_E_PLIST_ERROR           -2
#define MOBILE_IMAGE_MOUNTER_E_CONN_FAILED           -3
#define MOBILE_IMAGE_MOUNTER_E_COMMAND_FAILED        -4

#define MOBILE_IMAGE_MOUNTER_E_UNKNOWN_ERROR       -256
/*@}*/

/** Represents an error code. */
typedef int16_t mobile_image_mounter_error_t;

typedef struct mobile_image_mounter_client_private mobile_image_mounter_client_private;
typedef mobile_image_mounter_client_private *mobile_image_mounter_client_t; /**< The client handle. */

/** callback for image upload */
typedef ssize_t (*mobile_image_mounter_upload_cb_t) (void* buffer, size_t length, void *user_data);


/* Interface */
LIBIMOBILEDEVICE_API mobile_image_mounter_error_t mobile_image_mounter_new(idevice_t device, lockdownd_service_descriptor_t service, mobile_image_mounter_client_t *client);

/**
 * Starts a new mobile_image_mounter service on the specified device and connects to it.
 *
 * @param device The device to connect to.
 * @param client Pointer that will point to a newly allocated
 *     mobile_image_mounter_t upon successful return. Must be freed using
 *     mobile_image_mounter_free() after use.
 * @param label The label to use for communication. Usually the program name.
 *  Pass NULL to disable sending the label in requests to lockdownd.
 *
 * @return MOBILE_IMAGE_MOUNTER_E_SUCCESS on success, or an MOBILE_IMAGE_MOUNTER_E_* error
 *     code otherwise.
 */
LIBIMOBILEDEVICE_API mobile_image_mounter_error_t mobile_image_mounter_start_service(idevice_t device, mobile_image_mounter_client_t* client, const char* label);
LIBIMOBILEDEVICE_API mobile_image_mounter_error_t mobile_image_mounter_free(mobile_image_mounter_client_t client);
LIBIMOBILEDEVICE_API mobile_image_mounter_error_t mobile_image_mounter_lookup_image(mobile_image_mounter_client_t client, const char *image_type, plist_t *result);
LIBIMOBILEDEVICE_API mobile_image_mounter_error_t mobile_image_mounter_upload_image(mobile_image_mounter_client_t client, const char *image_type, size_t image_size, const char *image_signature, uint16_t signature_length, mobile_image_mounter_upload_cb_t upload_cb, void* userdata);
LIBIMOBILEDEVICE_API mobile_image_mounter_error_t mobile_image_mounter_mount_image(mobile_image_mounter_client_t client, const char *image_path, const char *image_signature, uint16_t signature_length, const char *image_type, plist_t *result);
LIBIMOBILEDEVICE_API mobile_image_mounter_error_t mobile_image_mounter_hangup(mobile_image_mounter_client_t client);

#ifdef __cplusplus
}
#endif

#endif
