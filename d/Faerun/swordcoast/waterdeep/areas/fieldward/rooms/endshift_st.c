/*
* fieldward/rooms/endshift_st.c
* On Endshift Street in the field ward of Waterdeep
*
* Created Feb 2022 by Brine
*/

#pragma strict_types

#include "../defs.h"

inherit FIELDW_STD_ROOM;

void
create_fieldward_room()
{
    set_short("Corner of Endshift Street and the Breezeway");
    set_extraline("Such place. Much holding. Wow.\n");

    add_exit(FIELDW_ROOM + "gawenknife_st03", "northwest");
    add_exit(FIELDW_ROOM + "breezeway", "southeast");
    add_exit(FIELDW_ROOM + "cg_keep02", "northeast");
    add_exit(FIELDW_ROOM + "endshift_inn", "inn");
}
