/*
* fieldward/rooms/wall02.c
* On the Trollwall of Waterdeep
*
* Created Feb 2022 by Brine
*/

#pragma strict_types

#include "../defs.h"

inherit FIELDW_STD_INDOOR;

void
create_fieldward_indoor_room()
{
    set_short("On the Trollwall");
    set_long("Such place. Much holding. Wow.\n");

    add_exit(FIELDW_ROOM + "wall01", "northwest");
    add_exit(FIELDW_ROOM + "wall03", "east");
}
