/* Castle rooms second floor-The Head Chambermaid room
 * Coded by Marisol (11/20/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types

#include "../defs.h"

inherit CASTLE_OV2;

void
create_castle_room()
{
    set_short("Head Chambermaid's room");
    set_em_long("This is the private room of the Head Chambermaid of "+
        "the castle. Here the decoration of the room are not only "+
        "definitely human but feminine. Nice sheep hides serve as rugs. "+
        "A charming bureau is set besides a small bed. A closet stands "+
        "on one of the walls. A small window faces west. Torches and "+
        "candle-holders are arranged craftily to provide light to the "+
        "small room.\n");

    add_item("room",
        "A very simple room. There is no one using it right now.\n"); 

    add_item(({"sheep hides", "rugs"}),
        "These rugs are made of sheep hide, possibly from the sheep "+
        "rise in the village. The wool is a pristine white, soft and "+
        "free of bump.\n");

    add_item("bureau",
        "A small chest with three drawers. The wood is dark oak "+
        "without polish. Some personal articles are set neatly on top "+
        "of the chest, a brush, a mirror, a small basin, a jar, "+
        "several glass bottles and some books.\n");

    add_item("drawers",
        "The outside of the drawers are rectangular and the borders "+
        "are carved with simple designs of leaves and acorns.\n");

    add_item("brush",
        "An elegant ivory brush rests on top of the bureau.\n");

    add_item(({"small basin", "basin", "jar"}),
        "A small porcelain basin rest on top of the bureau together "+
        "with a handsome porcelain jar full of water.\n");

    add_item(({"glass bottles", "bottles"}),
        "Several glass bottles decorate the bureau. All of them look "+
        "very feminine. Airy flame-blow glass in green, blue and red "+
        "bottles fill with what it seems is oils and perfumes.\n");

    add_item("closet",
        "An oakwood closet stands tall on the wall. One of its door "+
        "is open, reveling several dresses.\n");

    add_item("dresses",
        "Some black and white house maiden dresses, together with some "+
        "lively red and green color dresses, hang inside the closet.\n");

    add_item(({"small bed", "bed"}),
        "A small wooden bed stands near the window. Its can only holds "+
        "person on it. A soft mattress stands on top of wooden bed. "+
        "White clean sheets cover it and one big pillow rests at the "+
        "top of the mattress.\n");

    add_item("pillow",
        "A nice, fluffy pillow.\n");

    add_item("window",
        "A small window faces west. But it is hard to see outside "+
        "the window with all the debris and dead leaves plaster on "+
        "the glass.\n");

    add_door_exit(CASTLE_OBJ_DIR + "cdoor2_06", "castle2_14", "north");
}                                     
