/*
 * Corsair room
 *
 * Raymundo, June 2020
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/herbsearch";
inherit "/d/Gondor/tharbad/trail/base_room";
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/tharbad/trail/defs.h"

/* prototypes */
public void  create_gondor();
public void  reset_room();

object  *Corsair = allocate(4),
        Guard,
        Mate;
/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
void
create_gondor()
{
    FIX_EUID;
    set_short("The center of the clearing");

    set_long("This is the center of the clearing. Boxes are stacked "
        + "all around the area, making this seem almost like a room, "
        + "even though it's outdoors. The ground is well-trod, with "
        + "footprints everywhere. A firepit sits in the the middle "
        + "of the area, providing both a place to cook and a "
        + "bit of warmth for when the weather turns cold.\n");

    add_item( ({"pit", "firepit", "fire", "fire pit"}),
        "The firepit is simply river stones stacked in a circular "
        + "fashion. It's about as tall as as the middle of a human's "
        + "shin, and stained black with soot.\n");
    add_item("soot", "The soot is black and evidence of a fire.\n");
    add_item( ({"rock", "rocks", "stone", "stones", "river stones"}),
         "The stones look like they were hauled out of the river, "
        + "because they are almost completely smooth. They are small "
        + "enough that they could be carried in one hand.\n");
    add_cmd_item( ({"fire", "campfire", "fire pit", "pit", "firepit"}),
        "light", "You get ready to light the fire, only to realize that "
        + "there's no wood in the firepit!\n");

    object box = clone_object(TRAIL_OBJ + "box");
    box->move(TO);

    add_trash();
    add_landscape();

    add_exit("pathk", "east");
    add_exit("pathf", "north");
    add_exit("pathm", "south");
    add_exit("pathi", "west");

    reset_room();

}   /* end create_gondor () */

public void
reset_room()
{
    ::reset_room();

    /* add Corsair npc's */
    Guard = clone_npc(Guard, (POROS_DIR + "npcs/guard"));
    Mate = clone_npc(Mate, (POROS_DIR + "npcs/mate"));
    clone_npcs(Corsair, (POROS_DIR + "npcs/corsair"), 0.0);
}

