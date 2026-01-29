/* Corridor-Stairs Third floor.
 * Coded by Marisol (12/2/98)
 * Copyright (c) Marisol Ramos 1998
 */


#pragma strict_types
#include "defs.h"
inherit CASTLE_OV3;

#include <stdproperties.h>

void
create_castle_room()
{

    set_short("A stairs for the second floor");
    set_em_long(" The room is almost bare. No pictures or fancy "+
        "tapestries decorate the walls like on the lower floors. The "+
        "staircase doesn't look in better shape. There are spiderwebs "+
        "running between the balusters, and a thick layer of dust cover "+
        "the handrail. A dusty lamp is hanging on the wall unlit. "+
        "@@special_long@@");

    add_item("staircase",
        "The staircase is made with a dark wooden handrail that goes "+
        "down to the second floor. These staircase looks that haven't "+
        "been care for for a long time. Dust and spiderwebs cover it, "+
        "and the wood looks without shine or polish.\n");

    add_item("handrail",
        "A dark mate wood handrail goes down to the second floor. "+
        "The handrail is covered up with a thick layer of dust.\n"); 

    add_item("balusters",
        "The slender poles, also known as balusters, are hard to "+
        "see because they are all covered with dust and spiderwebs.\n");

   
    add_exit("castle2_05.c", "down");
    add_exit("castle3_02.c", "west");

    reset_room();

}                                                                         


string
special_long()
{
    object last_room = this_player()->query_prop(LIVE_O_LAST_ROOM);
    string filename;

    if (!last_room)
    {
        return "The room opens up to an unknown corridor. ";
    }

    filename = file_name(last_room);

    if (filename == (CASTLEOVE + "castle2_05"))
    {
    return "The room opens up to an unknown corridor. ";
    }

    if (filename == (CASTLEOVE + "castle3_02"))
    {
    return "The old staircase dissappears down to the second floor. ";
    }
     return "An old staircase dissappear down to the second floor. ";
}                                                                       