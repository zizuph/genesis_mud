/* rd_tr_01: West section of Templar Road, 11/22/95. */
 
#pragma strict_types
 
inherit "/std/room";
#include "defs.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";

void
create_room()
{
        ::create_room();
    set_short("templar Road far west");
    set_long("This barren section of Templar Road squirms between the "
            +"mighty merchant houses of Iron Square to the west and the "
            +"center of Tyr's slave population to the east. With the jail "
            +"looming to the north and the nearby Ziggurat's towering "
            +"bulk obscuring the bloated sun, its not surprising that "
            +"none choose to make this a place of home or business, "
            +"even among the Templars.\n");
 
    add_item(({"iron square", "square"}), "You can just make out one of "
            +"the Houses, Stel, from here.\n");
    add_item("jail", "A simple yet ominous tower.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
    ADD_ZIG_ITEM
 
    add_exit(TYR_MERCHANT+"ironsqr3.c", "west", 0, 1); 
    add_exit(TYR_SLAVE+"rd_tr_02.c", "east", 0, 1);
}
