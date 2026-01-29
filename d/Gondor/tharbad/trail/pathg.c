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

/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
void
create_gondor()
{
    FIX_EUID;
    set_short("On the east side of a clearing");

    set_long("Birds chirp in the trees to the northeast, and from time "
        + "to time frogs can be heard on the riverbank. To the southwest "
        + "the clearing opens up, becoming a large encampment where "
        + "corsairs stage their raids, hoping for some rich booty. Looking "
        + "about you can see that trees have been clear-cut to make this "
        + "clearing.\n");

    add_landscape();

    add_exit("pathf", "west");
    add_exit("pathk", "southwest");
    add_exit("path5", "southeast");
    add_exit("pathd", "northwest");

}   /* end create_gondor () */


