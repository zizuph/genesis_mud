
/* Re Albi village. Village's path IV.
 * Coded by Marisol (12/4/97)
 * Modified by Marisol (07/28/98) to be used in the village of
 * Ovejuno in Emerald.
 * Copyright (c) Marisol Ramos 1997 */

#pragma strict_types
#include "defs.h"
inherit OV_VILLAGE;

void
create_ov_room()
{

    set_long("A village path in Ovejuno. Villagers are going "+
        "about their business. To the north, there is a path "+
        "that goes to the communal pastures. To the south, a small "+
        "path goes to a house. You can see lambs frolicking in the "+
        "high pastures. The smokes of chimneys drift lazily "+
        "in the cool wind. From the south, you feel a very faint "+
        "breeze coming from the far sea.\n");

    add_item("sheep",
        "Sheep are the main trade in Ovejuno. The wool is not of "+
        "great quality, but is good enough to weave a nice and "+
        "durable textile that is trade with the roaming caravans that "+
        "visit the village from time to time. In the pastures, playful "+
        "lambs are frolicking under the watchful eyes of the "+
        "older sheep.\n");
                                  
    add_item("pastures",
        "The green pastures rise to the hill that hovers over the "+
        "village. Sheep and lambs roam in these communal lands "+
        "without any concerns.\n");

    add_item("villagers",
        "The villagers of Ovejuno are humans. They pay homage to "+
        "the elven's lord from Telberin. For many years they have "+
        "a decent relationship with their elven masters, until "+
        "the last elven master Morboses. For years they were without "+
        "a lord until recently when a new one move to the 'castle'. "+
        "Rumors abound about curses and haunted souls, and the "+
        "villagers live in terror to work in the lord's castle. But "+
        "besides that, they are honest villagers trying to make a "+
        "living under elven's control.\n");


    add_exit("village_ov15.c", "north");
    add_exit("village_ov14.c", "south");
    add_exit("village_ov05.c", "east");
    add_exit("village_ov03.c", "west");

    reset_room();

}                                                                  
