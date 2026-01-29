/*
* fieldward/rooms/trollfort04.c
* In the Trollfort of Waterdeep
*
* Created Feb 2022 by Brine
*/

#pragma strict_types

#include "../defs.h"

inherit FIELDW_STD_INDOOR;

void
create_fieldward_indoor_room()
{
    set_short("In the Trollfort");
    set_long("Such place. Much holding. Wow.\n");

    add_exit(FIELDW_ROOM + "trollfort06", "northwest");
    add_exit(FIELDW_ROOM + "trollfort05", "southwest");
    add_exit(FIELDW_ROOM + "wall01", "wall");
}
