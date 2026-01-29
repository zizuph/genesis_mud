/*
* fieldward/rooms/waystation02.c
* The side room of the waystation outside of Waterdeep
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

    add_exit(FIELDW_ROOM + "waystation01", "west");
}
