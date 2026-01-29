/*
* fieldward/rooms/waystation01.c
* The main room of the waystation outside of Waterdeep
*
* Created Feb 2022 by Brine
*/

#pragma strict_types

#include "../defs.h"

inherit FIELDW_STD_INDOOR;

void
create_fieldward_indoor_room()
{
    set_short("Waystation main room");
    set_long("Such place. Much holding. Wow.\n");

    add_exit(FIELDW_ROOM + "waystation02", "east");
    add_exit(FIELDW_ROOM + "fork", "out");
}
