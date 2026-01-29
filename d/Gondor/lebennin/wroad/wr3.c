/*
 *      /d/Gondor/lebennin/wroad/wr3.c
 *
 *      Road leading from Pelargir to Dol Amroth
 *
 */

#pragma strict_types

#include "/d/Gondor/lebennin/std/defs.h"

inherit LEBENNIN_STD_DIR + "base";

void
create_lebennin_room()
{
    set_items_road();
    set_items_pelargir();
    set_lebennin_herbs();

    set_short("Road in Lebennin");
    set_long("An old cobblestone road running across the " +
        "rolling plains. East the road continues in the direction of " +
        "Pelargir. The road continues across the plains into the horizon " +
        "to the west. The " + daylight() + " shines upon the rolling " +
        "hills to the north. Spreading out across a massive area, the " +
        "wide river delta of Ethir Anduin lies beyond the plains to the " +
        "south.\n");
    
    add_exit(AREA_DIR + "wroad/wr2", "east", 0, 1);
    add_exit(AREA_DIR + "wroad/wr4", "west", 0, 1);
    set_no_exit_msg(get_all_no_exits(({"w","e"})), "You decide to stay on " +
        "the road.\n");
}
