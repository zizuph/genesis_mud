/*
 *  Filename:       wr_armours.c
 *  Description:    This is the room on top of an armoury wagon
 *
 *  Copyright (c) Dec. 2003 by Peter Bech Lund, aka. Vencar of Krynn
 *
 *  Change log:
 */

#pragma strict_types
#include "/sys/language.h"
#include "wagon.h"


inherit WAGON_ROOM_INDOOR;


string
sides()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "The sides are formed by the canvas bonnet. You can see " +
        "several filled racks standing at the sides.\n";
}

string
racks()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "Each rack is constructed from a pair of massive oaktree "+
        "beams bolted into the floor. The beams are supported "+
        "by thick boards vertically. Several iron bars and hooks, "+
        "which are hammered and crafted into the boards, can sustain "+
        "large quantities of heavy armour.\n";

}

string
armours()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "There are numerous of different armours on the rack. "+
        "They vary from full platemails, half-mails, chainmails, "+
        "several padded leather and metal studded armours, "+
        "helmets and also thick, thin, large and small shields. "+
        "It seems whoever owns these armours also acknowledge "+
        "their obvious value as they all secured with spiked "+
        "chains.\n";

}

string
parts()
{

    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "These large heaps are neatly stacked and contain "+
        " many parts for different kinds of armours, such "+
        " bracers for platemails, sleeves for banded mails "+
        " greaves, wrist bands, attachable gauntlets, "+
        " leather strappings, different skins and alike.\n";

}

string
accessories()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "Among other things you notice cleaning oil, pieces "+
        "cloth for cleaning, and a few smith tools as well.\n ";

}




public string
long_desc(string longdesc)
{
    string desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";
    desc =  "You are inside " + LANG_ADDART(myWagon->short()) +
            ". This wagon appears to be a moveable armoury of " +
            "sorts. The sides of the wagon are lined by massive " +
            "wooden racks filled with numerous armours of many " +
            "different kinds. Also in the corners you notice "+
            "heaps of spare parts as well as accessories for " +
            "maintainance.\n";

    return desc;
}

public string
short_desc(string shortdesc)
{
    string desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";

    desc =  "Inside the armoury wagon";

    return desc;

}

void
init()
{
    ::init();
}


void
create_wagon_room()
{

    add_item("sides", sides);
    add_item(({"rack","racks"}), racks);
    add_item(({"armour","armours"}), armours);
    add_item(({"heap","heaps","parts","spare parts"}), parts);
    add_item("accessories", accessories);


}


