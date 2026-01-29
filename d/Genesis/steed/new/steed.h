/*
 * Header file for steeds.
 *
 * Fysix, Sep 2002
 */

/* Macros to see if a status is ok or not. */
#define STEED_STS_SUCCESS(x) (((x) % 2) == 0)
#define STEED_STS_FAIL(x) (((x) % 2) == 1)

/*
 * Possible statuses returned by steed functions.
 * Even ones are OK, odd ones are error statuses.
 */
#define STEED_STS_OK 0x00
#define STEED_STS_ERROR 0x01
#define STEED_STS_TOO_MANY_RIDERS 0x03
/* Already mounted. */
#define STEED_STS_RIDER_ALREADY_MOUNTED 0x05
/* Already mounted on the steed that living is trying to mount. */
#define STEED_STS_RIDER_ALREADY 0x07
#define STEED_STS_ILLEGAL_SHADOW 0x09
#define STEED_STS_LIVING_NO_RIDER 0x0B
#define STEED_STS_LIVING_NO_LEADER 0x0D
#define STEED_STS_SKILL_TOO_LOW 0x0F
#define STEED_STS_LIVING_IN_COMBAT 0x011
#define STEED_STS_STEED_IN_COMBAT 0x13
#define STEED_STS_LIVING_IN_OTHER_LOC 0x15
#define STEED_STS_ILL_MOUNT_WHILE_LEAD 0x17
#define STEED_STS_ILL_MOUNTED_DEST 0x19
#define STEED_STS_ILL_UNMOUNTED_DEST 0x1B
#define STEED_STS_CANNOT_BE_MOUNTED 0x2D
#define STEED_STS_ILL_DEST 0x1F
#define STEED_STS_ILL_RIDER_OBJ 0x21
#define STEED_STS_ILL_LEADER_OBJ 0x23
#define STEED_STS_CANNOT_BE_LEAD 0x25
