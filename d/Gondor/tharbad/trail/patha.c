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
    set_short("The northern end of a large clearing");

    set_long("At the northern end of the clearing, trees grow thick to the "
        + "north, providing some shade from the noon-day sun. South of here "
        + "the trees have been cut down to make room for a large encampment. "
        + "While birds occasionally sing in the trees, most of the noise here "
        + "is from people readying for battle.\n");

    add_landscape();
    
    add_exit("pathb", "southwest");
    add_exit("pathc", "south");
    add_exit("pathd", "southeast");
    
    reset_room();
 
}   /* end create_gondor () */

public void
reset_room()
{
    ::reset_room();

    /* add Corsair npc's */
    clone_npcs(Corsair, (POROS_DIR + "npcs/corsair"), 0.0);
}
