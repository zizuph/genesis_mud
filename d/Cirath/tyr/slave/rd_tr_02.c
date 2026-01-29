/* rd_tr_02: Western section of Templar Road, 11/22/95. */
 
#pragma strict_types
 
inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";

void
create_room()
{
        ::create_room();
    set_short("templar Road west");
    set_long("Three paths intersect near the southwest corner of the "
            +"slave pits of Tyr: Diamond Street to the north, Templar "
        +"Road running east and west, and an unnamed route to the "
            +"brickyards southeast. From this last direction rises a din "
            +"of pounding mallets and shattering stone, all bent to the "
            +"purpose of building Kalak's Ziggurat. A guard regards "
            +"you from a nearby tower.\n");
 
    add_item(({"pits", "slave pits", "pit", "slave pit"}),
             "You can only listen to the moans, not see inside.\n");
    add_item(({"corner", "tower", "guard"}), "Atop the 20 foot wall of "
            +"the slave pits corner is a guard tower, from where the "
            +"slaves and citizens can both be watched.\n");
    add_cmd_item(({"moans", "to moans"}), "listen", "You hear the "
            +"cries of the doomed, begging for freedom.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
    add_exit(TYR_SLAVE+"rd_ds_04.c", "north", 0, 1); 
    add_exit(TYR_SLAVE+"rd_tr_03.c", "east", 0, 1);
    add_exit(TYR_SLAVE+"zgbuild1.c", "southeast", 0, 1);
    add_exit(TYR_SLAVE+"rd_tr_01.c", "west", 0, 1);
}
