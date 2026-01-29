/*
 *  Filename:       wr_dofficer.c
 *  Description:    This is inside a dragon officers wagon.
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

    return  "The walls are crafted out of wooden planks and blemished in a darker hue.\n";

}

string
tapestry()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "This tapestry is rather magnificent. It depictcs the whole of Ansalon "+
            "with a large spike through the center of Krynn. The exterior is outlined "+
            "by slender and fierce dragons and underneath is written."+
            "Takhisis rule above and - Sky and Ground - below.\n";

}

string
desk()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "This long desk serves as the workspace of whoever uses this wagon. Apart "+
            "from the usual office supplies there is a large map on it.\n";

}

string
alcove()
{

    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "Carved from wood and fastened with silver nails this alcove provides a resting "+
            "place for the officials travelling in this wagon.\n";

}

string
drawers()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "These tall steel drawers are cold to the touch and you suppose they are used "+
            "for various personal and important items.\n";

}

/*
 * Add a key to the officer that will open the drawers and reveal some interesting item
 */


string
itemmap()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "A simple map of Krynn, where some of the latest deployments and movements of "+
            "troops are outlined.\n";

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
        ".\nThis wagon despite the spartan furnishing gives you "+
        "the impression that it was meant for a passenger of some "+
        "significance. You see dark wooden walls to the left and right "+
        "and a large tapestry on the back wall. In the middle of the wagon "+
        "there is a long desk with a grand chair behind it. "+
        "Compared to most wagons this one also provides more comfort, "+
        "such as a large sleeping alcove and a tall set of drawers.\n";

    return desc;
}


void
create_wagon_room()
{

    add_item("walls", walls);
    add_item("tapestry", tapestry);
    add_item("desk", desk);
    add_item("alcove", alcove);
    add_item("drawers", drawers);
    add_item("map", itemmap);

}


