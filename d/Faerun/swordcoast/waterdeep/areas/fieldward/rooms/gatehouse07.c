/*
* fieldward/rooms/gatehouse07.c
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
    set_short("Captain's room the Northgate gatehouse");
    set_long("Such place. Much holding. Wow.\n");

    add_exit(FIELDW_ROOM + "gatehouse05", "down");
}
