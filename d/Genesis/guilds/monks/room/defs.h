/*
 * Definitions for the rooms in the Kaheda Monk guildhall.
 *
 * Cirion 1998.04.18
 */
#pragma strict_types
#include "../defs.h"


#define ENTRANCE_MSG(from, msg)   (entrance_msg[(from)] = (msg))
#define VIEW_ENTRANCE(where, msg) (view_entrance_msg[(where)] = (msg))

#define VIRTUAL_DESC(func, true, false)  VBFC("virtual_desc:" + file_name(TO) + \
                                         "|" + (func) + "|" + (true) + "|" + (false))


// VBFC_SAY(x) will cause a say(x) to be sent to the room. The
// say() will always be preceeded by QCTNAME(this_player()) + " "
#define VBFC_SAY(x)    VBFC("vbfc_say:" + file_name(this_object()) + "|" + x)


// Append on some addition wizinfo to the room
#define WIZINFO(x)  query_prop(OBJ_S_WIZINFO) ?    \
                    add_prop(OBJ_S_WIZINFO, (string)query_prop(OBJ_S_WIZINFO) + "\n" + (x)) :   \
                    add_prop(OBJ_S_WIZINFO, (x))

#define NPC_DESC    VBFC("evaluate_composite_npc")

