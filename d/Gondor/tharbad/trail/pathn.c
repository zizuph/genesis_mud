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

object  *Corsair = allocate(3);

/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
void
create_gondor()
{
    FIX_EUID;
    set_short("The southeastern side of a clearing");

    set_long("To the northeast, the clearing narrows almost to a "
        + "path, and then opens wide again toward the river. Here, "
        + "trash litters the ground everywhere. Short trees have "
        + "been cut down to make room for this encampment, and "
        + "those trees that are left don't provide much more than "
        + "protection from prying eyes.\n");


    add_trash();
    add_landscape();

    add_exit("pathk", "northwest");
    add_exit("path5", "northeast");
    add_exit("pathq", "southwest");
    add_exit("pathm", "west");

    reset_room();

}   /* end create_gondor () */

public void
reset_room()
{
    ::reset_room();

    /* add Corsair npc's */
    clone_npcs(Corsair, (POROS_DIR + "npcs/corsair"), 0.0);
}
