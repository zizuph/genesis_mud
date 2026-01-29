/*
* fieldward/rooms/highroad02.c
* A room in the field ward of Waterdeep, with access to the city proper
*
* Created Feb 2022 by Brine
*/

#pragma strict_types

#include "../defs.h"

inherit FIELDW_STD_ROOM;

void
create_fieldward_room()
{
    set_short("Highroad, before upper towers");
    set_extraline("Such place. Much holding. Wow.\n");

    add_exit(FIELDW_ROOM + "highroad01", "north");
    add_exit(FIELDW_ROOM + "notarealroom", "south");
}
