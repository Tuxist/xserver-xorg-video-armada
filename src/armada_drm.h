/*
 * Marvell Armada DRM-based driver
 *
 * Written by Russell King, 2012, derived in part from the
 * Intel xorg X server driver.
 */
#ifndef DOVEFB_DRM_H
#define DOVEFB_DRM_H

#include "xf86.h"
#include <xf86drm.h>
#include <xf86drmMode.h>

struct drm_armada_bo;

struct armada_crtc_info {
	struct armada_drm_info *drm;
	unsigned num;
	drmModeModeInfo kmode;
	drmModeCrtcPtr mode_crtc;

	struct drm_armada_bo *cursor_bo;

	uint32_t rotate_fb_id;
};
#define armada_crtc(crtc) \
	((struct armada_crtc_info *)(crtc)->driver_private)

struct drm_udev_info {
	struct udev_monitor *monitor;
	pointer *handler;
	dev_t drm_dev;
};

struct armada_drm_info {
	int fd;
	struct drm_armada_bufmgr *bufmgr;
	drmEventContext event_context;

	unsigned cpp;

	struct drm_armada_bo *front_bo;
	uint32_t fb_id;
	drmModeResPtr mode_res;

	Bool has_hw_cursor;
	Bool hw_cursor;
	Bool accel;

#ifdef HAVE_UDEV
	struct drm_udev_info udev;
#endif

	CloseScreenProcPtr CloseScreen;
	CreateScreenResourcesProcPtr CreateScreenResources;
	OptionInfoPtr Options;
};

enum {
	OPTION_HW_CURSOR,
	OPTION_XV_ACCEL,
	OPTION_USE_GPU,
	OPTION_HOTPLUG,
};

#define GET_DRM_INFO(pScrn)		((struct armada_drm_info *)(pScrn)->driverPrivate)
#define SET_DRM_INFO(pScrn, ptr)	((pScrn)->driverPrivate = (ptr))

/* DRM core support */
Bool armada_drm_init_screen(ScrnInfoPtr pScrn);

/* DRM Xv support */
Bool armada_drm_XvInit(ScrnInfoPtr pScrn);

#endif
