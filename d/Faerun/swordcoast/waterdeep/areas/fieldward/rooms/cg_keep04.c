/*
* fieldward/rooms/cg_keep04.c
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
    set_short("Armoury in Cliffguard Keep");
    set_long("Such place. Much holding. Wow.\n");

    add_exit(FIELDW_ROOM + "cg_keep02", "south");
}
