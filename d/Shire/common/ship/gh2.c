/*
 * Water room for shipline
 */
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>

inherit AREA_ROOM;

void
create_room()
{
    set_short("Somewhere in the Bay of Belfalas");
    set_long("The Bay of Belfalas is on the southwestern side of Middle-earth.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
