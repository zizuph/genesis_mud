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

object  *Corsair = allocate(4);

/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
void
create_gondor()
{
    FIX_EUID;
    set_short("In the encampment");

    set_long("To the south, the encampment ends abruptly. However, "
        + "it extends north for quite some distance. Frogs and "
        + "birds can be heard here, inbetween bouts of eery silence. "
        + "Trash litters the ground as if the people living here "
        + "care only for themselves and not for nature.\n");

    add_trash();
    add_landscape();

    add_exit("pathm", "north");
    add_exit("pathr", "south");
    add_exit("patho", "west");
    add_exit("pathq", "east");

    reset_room();

}   /* end create_gondor () */

public void
reset_room()
{
    ::reset_room();

    /* add Corsair npc's */
    clone_npcs(Corsair, (POROS_DIR + "npcs/corsair"), 0.0);
}
