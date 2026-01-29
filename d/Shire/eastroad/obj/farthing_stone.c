/*
 * The Three Farthing Stone
 * Why no one has put this in after all these years is beyond me.
 * Finwe, August 2017
 */
 
#pragma no_inherit
#pragma strict_types

inherit "/std/object.c";

#include "/d/Shire/defs.h"
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

void
create_object()
{
    set_short("tall stone marker");
    set_long("This is a tall stone marker, also known as the Three Farthing " +
        "Stone. It is said to mark a point near the center of the Shire, " +
        "and marks the points where the Eastfarthing, Westfarthing, and the " +
        "Southfarthing meet. The Three Farthing Stone is square shaped and " +
        "made from a solid block of stone. It comes to a point, and crowned " +
        "with a round finial.\n");
    add_item(({"three farthing stone", "farthing stone", "tall stone marker", 
            "stone marker", "marker"}),         
        "This stone marker is set along the road. It is an ancient landmark " +
        "in the Shire. Rumour has it the stone is a gift from the Eldar " +
        "to mark the junction of the three farthings.\n");
    add_item(({"finial", "round finial"}),
        "It is a round, stone ball that sits on top of the stone marker.\n");

    set_name("marker");
    set_adj(({"tall", "stone"}));    

    add_prop(OBJ_I_WEIGHT, 22345978);
    add_prop(OBJ_I_VOLUME, 2565764);
    add_prop(OBJ_M_NO_GET, "It is impossible to take this stone marker.\n");
}