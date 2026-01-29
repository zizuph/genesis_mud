/*
 * Moria file system.
 *
 * Moria is a standalone package with no connections whatsoever to other
 * domain code. Thus, no references of any kind is used within this system
 * except the following macros:
 */

#ifndef _MORIA_DEFS_H_
#define _MORIA_DEFS_H_

/* Defines from where we want the roomfiles to be inherited. */
#include <macros.h>

#define ROOT_ROOM	"/d/Shire/common/lib/room"

/*
 * These macros state the different directories in which to have
 * the files of Moria.
 */

#define MORIA_DIR	"/d/Shire/moria/"
#define CITY_DIR MORIA_DIR + "city/"

#define MORIA_OBJ	 MORIA_DIR + "obj/"
#define MORIA_NPC	 MORIA_DIR + "npc/"
#define MORIA_WEP	 MORIA_DIR + "wep/"
#define MORIA_ARM	 MORIA_DIR + "arm/"
#define MORIA_HERB	 MORIA_DIR + "herb/"

#define MINES_DIR	 MORIA_DIR + "mines/"
#define FIRST_DEEP_DIR   MORIA_DIR + "first_deep/"
#define LEVEL1_DIR       MORIA_DIR + "mines-level-1/"

#define MINES_FILE	 "/d/Shire/moria/lib/mines"
#define ROGON_ROOM	 "/d/Shire/moria/lib/rogon_room"

#define WATCHERS	"/d/Shire/common/lib/watchers.h"

#define CONTROL          "/d/Shire/moria/control"

/*
 * These references are used for library files for convenience.
 */
/* Changed by Odin
#define IM_TELL_FILE	 "/d/Immortal/rogon/open/tell"
#define IM_MESSAGE_FILE	 "/d/Immortal/rogon/open/message"
#define IM_PARSE_FILE    "/d/Immortal/rogon/open/parse_lib"
*/

/* Note: These files don't exist! I think we know
 why all the healers messages are in /lplog now.
 I added the new locations below. Palmer 2/8/2003

#define IM_TELL_FILE    "/d/Shire/guild/healers/lib/tell"
#define IM_MESSAGE_FILE "/d/Shire/guild/healers/lib/message"
#define IM_PARSE_FILE   "/d/Shire/guild/healers/lib/parse"
*/
#define IM_TELL_FILE    "/d/Shire/abandoned/healers/lib/tell"
#define IM_MESSAGE_FILE "/d/Shire/abandoned/healers/lib/message"
#define IM_PARSE_FILE   "/d/Shire/abandoned/healers/lib/parse"


#define TELL_FILE IM_TELL_FILE
#define MESSAGE_FILE IM_MESSAGE_FILE
#define PARSE_FILE IM_PARSE_FILE

/*
 * Additional definition files.
 *
 */
#include "/d/Shire/moria/include/definitions.h"
#include "/d/Shire/moria/include/room.h"
#include "/d/Shire/moria/include/task.h"
#include "/d/Shire/moria/include/damtypes.h"

/*
 * Some additional nice to have macros.
 */
#define IS_MORIA_OBJECT(obj) CONTROL->is_moria_obj(obj)
#define IS_MORIA_ROOM(place) CONTROL->mines_room(place)
#define IS_IN_MORIA(obj)     CONTROL->inside_moria(obj)

/*
 * How much can you see in this room?
 */
#define CAN_SEE_OF_ROOM(tp) \
    (tp->query_prop(LIVE_I_SEE_DARK) + ENV(tp)->query_prop(OBJ_I_LIGHT))
#define LIGHT_SOURCES(room) \
    (room->query_prop(OBJ_I_LIGHT) - room->query_prop(ROOM_I_LIGHT))

#endif
