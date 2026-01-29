/*
* fieldward/rooms/cg_keep14.c
* In Cliffguard Keep of Waterdeep
*
* Created Feb 2022 by Brine
*/

#pragma strict_types

#include "../defs.h"

inherit FIELDW_STD_INDOOR;

void
create_fieldward_indoor_room()
{
    set_short("In Cliffguard Keep");
    set_long("Such place. Much holding. Wow.\n");

    add_exit(FIELDW_ROOM + "cg_keep10", "south");
    add_exit(FIELDW_ROOM + "cg_keep13", "west");
    add_exit(FIELDW_ROOM + "cg_keep07", "down");
}
