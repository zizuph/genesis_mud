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

/* prototypes */
public void  create_gondor();
public void  reset_room();

object  *Corsair = allocate(2);

/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
void
create_gondor()
{
    FIX_EUID;
    set_short("In a clearing");

    set_long("The clearing is wide open here, and signs of human "
        + "activity are everywhere. To the east, you hear the "
        + "river running. While you can hear birds and frogs on "
        + "occasion, no animals are visible here.\n");

    add_trash();
    add_landscape();

    add_exit("pathd", "east");
    add_exit("patha", "north");
    add_exit("pathf", "south");
    add_exit("pathb", "west");

    reset_room();

}   /* end create_gondor () */

public void
reset_room()
{
    ::reset_room();

    /* add Corsair npc's */
    clone_npcs(Corsair, (POROS_DIR + "npcs/corsair"), 0.0);
}

