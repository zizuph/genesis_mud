/*
* fieldward/rooms/trollyard.c
* In the trollyard, before the Trollfort in Waterdeep.
*
* Created Feb 2022 by Brine
*/

#pragma strict_types

#include "../defs.h"

inherit FIELDW_STD_ROOM;

void
create_fieldward_room()
{
    set_short("In the Trollyard");
    set_extraline("Such place. Much holding. Wow.\n");

    add_exit(FIELDW_ROOM + "trollfort01", "northwest");
    add_exit(FIELDW_ROOM + "fieldway05", "east");
}
