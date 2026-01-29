/*
* fieldward/rooms/gatehouse03.c
* In the Northgate of Waterdeep
*
* Created Feb 2022 by Brine
*/

#pragma strict_types

#include "../defs.h"

inherit FIELDW_STD_INDOOR;

void
create_fieldward_indoor_room()
{
    set_short("In the Northgate gatehouse");
    set_long("Such place. Much holding. Wow.\n");

    add_exit(FIELDW_ROOM + "gatehouse04", "east");
    add_exit(FIELDW_ROOM + "wall03", "wall");
    add_exit(FIELDW_ROOM + "gatehouse06", "up");
    add_exit(FIELDW_ROOM + "gatehouse01", "down");
}
