/*
* fieldward/rooms/trollfort02.c
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

    add_exit(FIELDW_ROOM + "trollfort06", "northeast");
    add_exit(FIELDW_ROOM + "trollfort05", "southeast");
    add_exit(FIELDW_ROOM + "trollfort01", "down");
}
