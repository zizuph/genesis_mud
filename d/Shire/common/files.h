/*
 * This file defines paths to filenames. This is done in a similar
 * fashion as for instance /sys/language.h. The reason for this is
 * to avoid expressions like for instance
 *
 *    "/d/Shire/common/lib/stringfuns"->index(aka, bepa);
 *
 * Instead the shorter syntax
 *
 *    STRING_FILE->index(aka, bepa);
 *
 * can be used.
 *
 * Also, some inherit files are defined, since it is currently not
 * possible to do
 *
 *    inherit STAND_LIB + "tell";
 *
 *
 * Sir Rogon.
 *
 */

#ifndef _shire_files_h_
#define _shire_files_h_ 1

#define LIB_FILE	"/d/Shire/common/lib/lib"
#define TELL_FILE	"/d/Shire/common/lib/tell"
#define STRING_FILE	"/d/Shire/common/lib/stringfuns"
#define SPECIAL_FILE	"/d/Shire/common/lib/special"

/*
 * Inherit-files.
 *
 */

#define ROOM_FILE	"/d/Shire/common/lib/room"
#define ROM_FILE	"/d/Shire/common/lib/rom"

#endif
