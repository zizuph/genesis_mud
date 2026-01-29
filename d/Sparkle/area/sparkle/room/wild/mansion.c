/* 	mansion.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("On a white stone yard");
    set_long("\n"+
             "You are standing on a white stone yard north of an old foundation.\n"+
             "The view towards the village and the sea is indeed beautiful from here.\n"+
             "This might once have been the site of a great mansion. All that is left\n"+
             "now is the foundation. It is strange how well kept the area is. A lane\n"+
             "leads east down the slope. West you can see a garden path and a well kept\n"+
             "lawn. The entrance to the mansion would have been to the south.\n"+
             "");

    add_exit("lawn","west");
    add_exit("lane","east");

    add_item(({"yard" }),
             "The yard is laid with large stone slabs.\n");
    add_item(({"slab","slabs" }),
             "One of the slabs seems to be loose.\n");
    add_item(({"foundation","foundations" }),
             "There is an entrance to what might have been the\n"+
             "basement but it is all blocked by rubble.\n");
    add_item(({"basement","rubble","entrance" }),
             "A large heap of broken masonry and stones, partly overgrown by bracken.\n");
    add_item(({"village" }),
             "Sparkle is indeed very beautiful from up here.\n");
    add_item(({"sea" }),
             "Pensea has a deep blue colour. Maybe you should go for a\n"+
             "trip by boat. It could be a rewarding experience.\n");
    add_item(({"lane"}),
             "The lane is slightly overgrown with grass.\n");
    add_item(({"path",}),
             "The path leads into a garden.\n");
    add_item(({"lawn" }),
             "It's very strange, but the lawn looks newly cut...\n");
    add_item(({"slope" }), "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

