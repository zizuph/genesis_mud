/*
 * Water room for shipline
 */
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>

inherit AREA_ROOM;

void
create_room()
{
    set_short("Somewhere in the Great Sea");
    set_long("The Great Sea is on the western side of Middle-earth.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
