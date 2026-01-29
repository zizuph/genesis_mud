/*
 *  Filename:       wr_kofficer.c
 *  Description:    A knight officer wagon.
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
walls()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "Light and bright white these walls give the room a comfortable finish. "+
            "You notice a few carvings on them as well. On the back wall you find a "+
            "a pair of ornamental lances hanging crossed with the words 'My Honour is My life "+
            "painted beneath'.\n";

}

string
tapestry()
{

    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "There are several blue and white tapestries, a few of them very detailed "+
            "and embroided with the symbol of the Knighthood.\n";

}

string
carvings()
{

    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "Among the carvings you find parts of a poem 'Trust in the Gods' -"+
            "'Trust in your Heart'.\n";

}

string
furniture()
{

    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "There is a table, a chair and a bed.\n";

}

string
table()
{

    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "A large table from solid oak. There are a few formal papers and documents "+
            "on it, but nothing that strikes you as important.\n";

}

string
chair()
{

    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "A tall and comfortable chair, to endure the strain of paperwork "+
            "during hazardous travels.\n";

}

string
bed()
{

    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "This is a small and simple bed that provides some comfort for the weary "+
            "user of this wagon.\n";

}


public string
short_desc(string shortdesc)
{
    string desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";

    desc =  "Inside the officer wagon";

    return desc;

}

public string
long_desc(string longdesc)
{
    string desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";

    desc =      "You are inside " + LANG_ADDART(myWagon->short()) +
        ".\nThis wagon is ornately decorated befitting a traveller of some status. "+
        "On the white wooden walls there are small tapestries and even carvings "+
        "of various kinds. The furniture is sparse yet grand and looking more closely "+
        "it appears whoever uses this carriage is involved with important affairs of "+
        "warfare as well.\n";

    return desc;
}


void
create_wagon_room()
{

    add_item("walls", walls);
    add_item("tapestries", tapestry);
    add_item("carvings", carvings);
    add_item("furniture", furniture);
    add_item("chair", chair);
    add_item("table", table);
    add_item("bed", bed);
}


