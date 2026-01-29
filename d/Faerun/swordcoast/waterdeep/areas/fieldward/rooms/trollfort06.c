/*
* fieldward/rooms/trollfort06.c
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

    add_exit(FIELDW_ROOM + "trollfort02", "southwest");
    add_exit(FIELDW_ROOM + "trollfort03", "south");
    add_exit(FIELDW_ROOM + "trollfort04", "southeast");
}
