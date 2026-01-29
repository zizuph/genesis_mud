/*
 *  /d/Sparkle/area/tutorial/cliffs/cliffroad_3.c
 *
 *  A road in the cliffs leading toward Krolock's castle.
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* prototypes */
public void        create_silverdell();


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("on a narrow path leading up through the cliffs");
    set_long("The path takes a turn here, leading up steep slopes"
      + " via a switchback. You catch a glimpse of what appears to"
      + " be a castle on a plateau high above.\n\n");

    add_outdoor_items();
    add_cliffs_items();

    add_item( ({ "here", "area" }), long);
    add_item( ({ "castle", "plateau" }),
        "The plateau is high above yet, and you can only barely"
      + " see what appears to be a castle on the heights.\n");

    add_exit("cliffroad_4", "southwest");
    add_exit("cliffroad_2", "south");

    add_npc(NPC_DIR + "lion", 1, &->arm_me());

    //This room is instanced.
    instance_entrance = 0;

} /* create_silverdell */
