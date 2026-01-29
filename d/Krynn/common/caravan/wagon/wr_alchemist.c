/*
 *  Filename:       wr_alchemist.c
 *  Description:    This is the room on top of the alchemistwagon
 *
 *  Copyright (c) Dec. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Change log:
 */

#pragma strict_types
#include "/sys/language.h"
#include "/sys/macros.h"
#include "wagon.h"


inherit WAGON_ROOM_INDOOR;



string
shelves()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "They are constructed from a copper red tree sort and their "+
            "purpose is obvious. To contain the hundreds of potions "+
            "and components of the wagons proprietor. \n";

}

string
components()
{

    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

   return  "Carefully examining the components you realize that "+
            "the art of brewing death and cooking life can be an odd "+
            "one indeed. Among other things you find a lizards tail, "+
            "a draconian wing, some chunks of blue and violet coal, "+
            "live crickets and the nose of a white bat.\n";

}

string
potions()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "Rare to find so many different potions, brews and elixirs "+
            "in once place. They vary in all sorts of colours, shapes "+
            "smells and even noises. No doubt whoever owns this wagon "+
            "has an extended experience and cunning skill of alchemy.\n";


}

string
bed()
{

    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "A strange design indeed. It must be gnomish, a small "+
            "bed of air, contained by dyed leather and cloth.\n";

}

string
desk()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "A crude oakwood desk. Upon you notice different potions of "+
            "various kinds.\n";

}

public string
short_desc(string shortdesc)
{
    string desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";

    desc =  "Inside a wagon";

    return desc;

}

public string
long_desc(string longdesc)
{
    string desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";

    desc =      "You are inside " + LANG_ADDART(myWagon->short()) +
        ".\nThis is obviously the travelling wagon of a craftsman "+
        "of some sort. A small thick desk stands to the left "+
        "side and to the right a small inflatable bed has been "+
        "rolled out. The rest of the wagon is quite crammed with "+
        "several sturdy shelves all filled with potions and "+
        "bottles alike. A disturbing eruption of hisses, pops, "+
        "cracks noisily waver through the room. \n";

    return desc;
}


void
create_wagon_room()
{

    add_item("desk",desk);
    add_item("bed", bed);
    add_item(({"potions","bottles"}), potions);
    add_item("shelves", shelves);
    add_item("components", components);
}


