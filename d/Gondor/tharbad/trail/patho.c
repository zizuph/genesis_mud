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

object  *Corsair = allocate(1);

/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
void
create_gondor()
{
    FIX_EUID;
    set_short("Along the trees in the encampment");

    set_long("Short trees form a barrier, almost a fence, to the "
        + "west. They're thick enough to prevent unwelcome visitors "
        + "from spying on the encampment. At your feet are tree stumps, "
        + "hacked so close to the dirt that they're almost unnoticeable. "
        + "The encampment continues to the east.\n");

    add_trash();
    add_landscape();

    add_exit("pathl", "northwest");
    add_exit("pathm", "northeast", 0, 0, 1);
    add_exit("pathr", "southeast");
    add_exit("pathp", "east");

    reset_room();

}   /* end create_gondor () */

public void
reset_room()
{
    ::reset_room();

    /* add Corsair npc's */
    clone_npcs(Corsair, (POROS_DIR + "npcs/corsair"), 0.0);
}

