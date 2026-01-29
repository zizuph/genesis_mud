/*
 *  Filename:       wr_weaponry.c
 *  Description:    This is the room on top of the weaponwagon
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
stands()
{

    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "The stands are expertly crafted from ashen and oakwood "+
        "and all of which are painted in a golden brown colour. "+
        "There are a broad variety of weaponry located on the "+
        "long stands. Mainly you notice slender halberds, jagged "+
        "bastardswords, some thin rapiers as well as a few knives.\n";

}

string
chest()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "This is a large massive steel chest. It is constructed "+
        "from thick plates of blackened steel and re-infcorced with "+
        "mithril strappings and golden cramps on each corner.\n";

}

string
desk()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "It is a small birchwood desk. The only appearant funtion "+
        "of its presence is the little book on top of it.\n";

}

string
small_book()
{
    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    return  "It is a thin book with a black smooth leather cover.\n";

}


public int
read_book(string str)
{

    if (myWagon->query_burnstep())
        return STANDARD_EXA_ITEM_BURNING;

    if (str == "book")
    {

    write("As you read the book it becomes evident it is an "+
        "inventory list of the weapons transport.\n");
        say(QCTNAME(TP) + " reads the small book.\n", TP);
    }

}



public string
short_desc(string shortdesc)
{
    string desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";

    desc =  "Inside the weapon wagon";

    return desc;

}

public string
long_desc(string longdesc)
{
    string desc;

    if (!objectp(myWagon))
        return "I don't have a wagon, so I'm buggy.\n";

    desc =      "You are inside " + LANG_ADDART(myWagon->short()) +
        ". This wagon appears to be a weapon transport. The wagon " +
        "is stocked with long weapon stands as well as a large "+
        "chest at the back end of the wagon. A small desk stands "+
        "to your left.\n";

    return desc;
}


void
create_wagon_room()
{

    add_item("desk",desk);
    add_item(({"weapon","weapons","stand","stands"}), stands);
    add_item("chest", chest);
    add_item("book", small_book);

}

void
init()
{
    ::init();

    add_action(read_book, "read");
}

