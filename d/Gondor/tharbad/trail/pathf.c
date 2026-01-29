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
#include "defs.h"

/* prototypes */
public void  create_gondor();
public void  reset_room();

object  *Corsair = allocate(1);

/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
void
create_gondor()
{
    FIX_EUID;
    set_short("Just north of the center of the encampment");

    set_long("Directly to the south is the center of the "
        + "encampment, which by the looks of it is where the "
        + "corsairs congregate. There are boxes here, stacked "
        + "on the ground with care. Otherwise, this portion "
        + "of the encampment looks quite bare.\n");

//    object box = clone_object(TRAIL_OBJ + "box");
//    box->move(TO);

    room_add_object(TRAIL_OBJ + "box");

    add_landscape();

    add_exit("pathg", "east");
    add_exit("pathc", "north");
    add_exit("pathj", "south");
    add_exit("pathe", "west");
    add_exit("pathi", "southwest");
    add_exit("pathk", "southeast");
    add_exit("pathb", "northwest", 0, 0, 1);
    add_exit("pathd", "northeast", 0, 0, 1);

    reset_room();

}   /* end create_gondor () */

public void
reset_room()
{
    ::reset_room();

    /* add Corsair npc's */
//    clone_npcs(Corsair, (POROS_DIR + "npcs/corsair"), 0.0);
}

