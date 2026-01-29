/*
* fieldward/rooms/cg_keep11.c
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
    set_short("Commander's office in Cliffguard Keep");
    set_long("Such place. Much holding. Wow.\n");

    add_exit(FIELDW_ROOM + "cg_keep13", "north");
}
