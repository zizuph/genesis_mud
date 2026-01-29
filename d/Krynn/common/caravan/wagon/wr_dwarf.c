/*
 *  Filename:       wr_dwarf.c
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
string name = "Rolf" ;

public string
short_desc(string shortdesc)
{
    string desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";

    desc =  "Inside the dwarven wagon";

    return desc;

}

public string
long_desc(string longdesc)
{
    string desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";

    desc =      "This is inside " + LANG_ADDART(myWagon->short()) +
        ".\nThis is a simple wagon to carry the dwarven engineer " + name +
        " and his crew across the realms on their various assignments. "+
        "To ensure light and fast travel all the walls and interiors are "+
        "from wood instead of the typical metal transports of many dwarven "+
        "craftsmen and laborers. Two small windows and a lantern provide "+
        "a dim light. To the left there is a very large and low desk and the "+
        "right side is dominated by the shelves which holds "+
        "numerous tools and gadgets belonging to " + name + ". Near the back end "+
        "there are a few barrels as well.\n";

    return desc;
}

string
walls()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;
    return  "Simple and sturdy walls, floor and ceiling of typical dwarven construct.\n";

}

string
windows()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;
    return  "A pair of small windows with frames of oakwood.\n";

}

string
lantern()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;
    return  "Its a brass lantern hanging from the ceiling providing a dim light.\n";

}

string
desk()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;
    return  "This dirty desk serves both as workbench and dining place "+
            "for the dwarven travellers. \n";

}

string
shelves()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;
    return  "The low system of wooden shelves contain various tools of the "+
            "engineering and carpenter trade.\n";

}

string
tools()
{

    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;
    return  "Hundreds of tools, some so specific that only the most skilled "+
            "of the dwarven craftsmen would know their exact purpose and "+
            "significance.\n";

}

string
barrels()
{

    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "They contain different dwarven spirits of to comfort the "+
            "travellers from the discomfort of a bumpy and long ride.\n";

}

/*
 * Make the barrels searchable somehow.. if you search em twice the dwarves
 * attack you. If theyre killed you might find something?
 */


void
create_wagon_room()
{

    add_item("barrels",barrels);
    add_item(({"tools","gadgets"}), tools);
    add_item("desk", desk);
    add_item("shelves", shelves);
    add_item("lantern", lantern);
    add_item("windows", windows);
    add_item(({"walls","floor","ceiling","sides"}), walls);
}


