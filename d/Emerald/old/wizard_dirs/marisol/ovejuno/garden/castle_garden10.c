/*Manor's Garden X
* The fountain
* Coded by Marisol (9/5/97)
 * Modified by Marisol (07/27/98) to be used in the village of Ovejuno
 * in Emerald.
* Copyright (c) Marisol Ramos 1997
*/

#include "defs.h"
#include <macros.h>
#include "/d/Emerald/sys/macros.h";
inherit CASTLE_GARDEN;


void
create_emerald_garden()

{
    set_short("A fountain");
    set_long("This is the center of the garden. Here, a "+
        "dirty and cracked fountain still spouts water "+
        "from a bronze vase. A mysterious bronze nymph holds the "+
        "spouting vase. This area of the garden is bereft of any "+
        "ornamental flowers, only the yellow flowers of "+
        "weeds strive here in the emerald green. The hedge "+
        "enclosed the fountain, in a rectangle of green "+
        "rhododendrons, so the rest of the garden cannot be "+
        "seen from here. The sound of water falling is "+
        "soothing, mingling with the chirp of birds and the "+
        "chatter of insects somewhere in the tall grass.\n");


    add_item(({"fountain", "statue", "bronze statue"}),
        "The statue is old, covered with a green "+
        "patina characteristic of bronze. The base of "+
        "the fountain is marble, and it has been "+
        "cracked by the passing of time. Inside the "+
        "basin, dirt and old leaves sit in the botton. "+
        "Still, the water is cold and fresh. It looks "+
        "really good to quench any thirst.\n");


    add_exit("castle_garden06.c", "west");
    add_exit("castle_garden07.c", "east");
}

int
drink_it(string str)
{
    if ((str == "water") || (str == "water from basin"))
    {
        if (!this_player()->drink_soft(100))
	{
            write("You are too full to drink any more water.\n");
            return 1;
	}

        write("You take a drink of the earthy-tasting "+
            "water. You feel refreshed.\n");

        say(QCTNAME(TP) + " drinks some water from the basin.\n");

        return 1;
    }

    notify_fail("Drink what?\n");
    return 0;
}   

void
init()
{

    ::init();
    add_action(drink_it, "drink");

}
                                                             
