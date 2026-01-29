/*
  Pax Tharkas, Valley.....

  forest4.c
  ---------

  Coded ........: 95/04/09
  By ...........: Jeremiah

  Latest update : 04/07/01
  By ...........: Cotillion

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXOUTROOM;
inherit HERBSEARCHNEW

int drink_water(string what);

string *herbs = HERB_MASTER->query_herbs( ({"hills","mixedforest",}));


void
reset_pax_room()
{
    set_searched(4);
}


void
create_pax_room()
{
    reset_pax_room();

    set_short("Light forest");
    set_long("You are standing in a light forest. The trees do not " +
        "grow very close here, but close enough for their crowns " +
        "to form an opaque cover above you. Southwards, the " +
        "ground slopes somewhat upwards. Large rocks lie around " +
        "and here and there, the naked rock of the mountains, " +
        "breaks through the layer of soil covering them. A small " +
        "stream, trickling with clear water, has cut its way " +
        "into the forest soil and the rock beneath it, and runs " +
        "through the forest here. North of you the forest gets " +
        "thinner and finally fades away into the open. A small, " +
        "almost invisible path, leads east, west and north from " +
        "here.\n");

    OUTSIDE;

    add_item("path", "A small path, almost invisible, leading " +
        "through the forest. It looks like it has been left almost " +
        "unused for a very long time. Something or someone must " +
        "have moved along it, otherwise it would probably " +
        "have disappeared totally.\n");

    add_item(({"stream", "ditch"}), "A small stream trickling through " +
        "the forest. Through the clear water you can see the granite " +
        "of the mountains forming an irregular, but solid, ditch.\n"); 

    add_item(({"tree", "trees"}), "The largest part of the trees are " +
        "hardwood trees, like birch or aspen. None of them are " +
        "specially tall, probably due to the sparse soil here on " +
        "the mountain slopes.\n");

    add_item("soil", "It looks like fertile mould. It is very sparse " +
        "here on the mountain slopes.\n");

    add_item(({"rocks", "boulders"}), "Large rocks settled into the " +
        "sparse soil.\n");

    add_item("rock", "The naked stone of the mountain visible " +
        "through the sparse soil.\n");

    set_up_herbs( ({ONE_OF(herbs),ONE_OF(herbs),ONE_OF(herbs),
                        ONE_OF(herbs) }), ({"soil","ground","rocks",}), 5);

    set_tell_time(60);
    add_tell("The water trickles gently down the stream.\n");
    add_tell("A bird chirps somewhere among the trees.\n");    

    add_exit(VALLEY + "forest1", "north", 0, 1);
    add_exit(VALLEY + "forest5", "east", 0, 1);
    add_exit(VALLEY + "forest3", "west", 0, 1);

    add_prop(OBJ_I_CONTAIN_WATER, -1);
}


init()
{
    ::init();
    add_action(drink_water, "drink");
}

int
drink_water(string what)
{
    NF("Drink what ?\n");

    if ((what == "water") || (what == "from stream") ||
        (what == "from ditch") || (what == "water from stream") ||
        (what == "water from ditch"))
    {
        if (TP->drink_soft(TP->drink_max() / 16,0))
        {
            write("You drink some water from the small stream, and " +
                "feel refreshed.\n");
            say(QCTNAME(TP) + " drinks some water from the small stream.\n");
        }
        else
            write("Hmm, you don't feel thirsty at all at the moment.\n");
        return 1;
    }
    return 0;
}

