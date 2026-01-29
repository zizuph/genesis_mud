/*
 *  Filename:       wr_trooptransport.c
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

int rndtext;

string
bench()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "Uncomfortable and simple, these benches serves as a place for the troops "+
            "to sit, during transport. \n";

}

string
plate()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "This tall iron plate serves as both a protective backside and shield "+
            "when raised and as a sturdy walking plank for the troops to board "+
            "and disembark the transport. \n";

}

string
tabard()
{
    string txt;

     if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

   switch (rndtext)
    {
        case 1:
            txt = "Glory to the + colour + dragonarmy";
            break;
        case 2:
            txt = "For Takhisis!";
            break;
        case 3:
            txt = "Praise the Dragonqueen!";
            break;
        case 4:
            txt = "Dragons aloft, corpses beneath!";
            break;
        case 5:
            txt = "Howling Horns Of War - Dragonarmy March!";
            break;
        case 6:
            txt = "Bloody swords harvesting souls, Dragons take their feasts.";
            break;
        default:
            txt = "";
    }

    return  "The texture of this cloth is rough and simple, yet the "+
            "pattern sewn into it is more detailed. With large "+
            "exceptional letters it reads '" + txt + "'.\n";


}

string
sides()
{

    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "+ colour + beams form the sides of the troop transport.\n";

}

string
floor()
{

    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "The floor is obviously made for heavy usage in peace and wartimes, "+
            "as you notice marks of metal footwear, weaponry and even dark "+
            "red stains of blood.\n";

}

public string
short_desc(string shortdesc)
{
    string desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";

    desc =  "On the deck of the troop transport";

    return desc;

}

public string
long_desc(string longdesc)
{
    string desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";

    desc =      "You are standing on" + LANG_ADDART(myWagon->short()) +
        "The floor of this wagon is constructed from thick wooden planks "+
        "with steel strappings and nails, The sides are made from massive "+
        "beams dyed + colour + and a large cloth tabard outline the "+
        "front side whereas a tall slender iron plate forms the back. "+
        "On either side of the wagon there is a long simple wooden bench.\n";

    return desc;
}


void
create_wagon_room()
{

    add_item(({"floor","planks","strappings","nails"}), floor);
    add_item(({"beams","sides"}), sides);
    add_item(({"tabard","pattern"}), tabard);
    add_item("plate", plate);
    add_item(({"bench","benches"}), bench);

    rndtext = random(6);
}


