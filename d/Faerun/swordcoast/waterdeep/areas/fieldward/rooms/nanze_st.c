/*
* fieldward/rooms/nanze_st.c
* Nanze Street in Waterdeep, where can be found Thrakkus' Meat
*
* Created Feb 2022 by Brine
*/

#pragma strict_types

#include "../defs.h"

inherit FIELDW_STD_ROOM;

void
create_fieldward_room()
{
    set_short("Nanze Street");
    set_extraline("Such place. Much holding. Wow.\n");

    add_exit(FIELDW_ROOM + "fieldway02", "south");
}
