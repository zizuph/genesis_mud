/*
 * Water room for shipline
 */
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>

inherit AREA_ROOM;

void
create_room()
{
    set_short("Inside the Gulf of Lune");
    set_long("The Gulf is a small inlet in Middle-earth\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
