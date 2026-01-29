/*
* fieldward/rooms/wall03.c
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

    add_exit(FIELDW_ROOM + "wall02", "west");
    add_exit(FIELDW_ROOM + "gatehouse03", "southeast");
}
