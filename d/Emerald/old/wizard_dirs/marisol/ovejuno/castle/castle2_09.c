/* Castle rooms second floor-The Majordomo room
 * Coded by Marisol (11/20/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types
#include "defs.h"
inherit CASTLE_OV2;

void
create_castle_room()
{

    set_short("Majordomo's room");
    set_long("This is the chamber of the castle's majordomo. "+
        "Here the decoration of the room is definitely human. Coarse "+
        "sheep hides serve as rugs. A simple bureau is set besides a "+
        "humble bed. A closet stands on one of the walls. A pair of "+
        "pointed shoes rest under the bed. A small window faces south. "+
        "Torches are set strategically to provide light to the small "+
        "room.\n");

    add_item("room",
        "A very simple room. There is no one using it right now.\n"); 

    add_item(({"sheep hides", "rugs"}),
        "These rugs are made of sheep hide, possibly from the sheep "+
        "rise in the village. The wool is a yellowed white, coarse and "+
        "bumpy.\n");

    add_item("bureau",
        "A small chest with three drawers. The wood is dark oak "+
        "without polish. Some personal articles are set neatly on top "+
        "of the chest, a comb, a small basin, a jar and a shaving set.\n");

    add_item("drawers",
        "The outside of the drawers are rectangular and the borders "+
        "are carved with simple designs of leaves and acorns.\n");

    add_item("comb",
        "An elegant tortoise shell comb rests on top of the bureau.\n");

    add_item(({"small basin", "basin", "jar"}),
        "A small porcelain basin rest on top of the bureau together "+
        "with a handsome porcelain jar full of water.\n");

    add_item("shaving set",
        "A handy shaving set rests on top of the bureau with all the "+
        "necessary tools for the right shave. A shaving knife sits near "+
        "a little mug, with a soap inside its bottom. A brush of soft "+
        "hair and ivory handle stands besides the mug.\n");

    add_item("closet",
        "An oakwood closet stands tall on the wall. One of its door "+
        "is open, reveling a couple of dark suits and white shirts.\n");

    add_item(({"dark suits", "suits", "white shirts", "shirts"}),
        "Very elegant black suits hang together with cotton white "+
        "shirts.\n");

    add_item(({"pointed shoes", "shoes"}),
        "A pair of black, pointed shoes are under the majordomo's "+
        "bed.\n");

    add_item(({"humble bed", "bed"}),
        "A humble wooden bed stands near the window. Its can only holds "+
        "person on it. A thin mattress is the only comfortable part "+
        "of the bed. White clean sheets cover it and one big pillow "+
        "rests at the top of the bed.\n");

    add_item("pillow",
        "A nice, fluffy pillow.\n");

    add_item("window",
        "A small window faces south. But it is hard to see outside "+
        "the window with all the debris and dead leaves plaster on "+
        "the glass.\n");

    add_exit("castle2_13.c", "north");

    reset_room();

}                                     
