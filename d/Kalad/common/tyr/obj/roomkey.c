/* roomkey.c: Key to the rooms in the Golden Inix Inn */

inherit "/std/object";
#include "defs.h"

void
create_object()
{
    set_short("hotel key");
    set_long("This relatively large key is for a room in Tyr's "+
             "Golden Inix Inn.\n");
    set_adj("hotel");
    set_name("key");
    add_name("_tyr_room_key_");
    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 5);
}
