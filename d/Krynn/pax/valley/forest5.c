/*
  Pax Tharkas, Valley.....

  forest5.c
  ---------

  Coded ........: 95/04/09
  By ...........: Jeremiah

  Latest update : 95/05/16
  By ...........: Jeremiah

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
    set_long("You are standing in a light forest. The trees aren't " +
        "growing very close, but close enough for their crowns " +
        "to form a blanket of leaves above you. The ground slopes " +
        "somewhat, upwards, southwards. Large rocks lie around " +
        "and here and there, the naked rock of the mountains, " +
        "breaks through the layer of soil covering them. A small, " +
        "almost invisible path, leads northwest, south and west.\n");

    OUTSIDE;

    add_item("path", "A small path, almost invisible, leading " +
        "through the forest. It looks like it has been left almost " +
        "unused for a very long time. Something or someone must " +
        "have moved along it, otherwise it would probably " +
        "have disappeared totally.\n");

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

    set_up_herbs( ({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
                        ONE_OF(herbs) }), ({"soil","ground","rocks",}), 4);

    
    set_tell_time(60);
    add_tell("You hear the distant sound of trickling water.\n");
    add_tell("A bird chirps somewhere.\n");
    add_tell("You hear birds twittering from the tree tops.\n");

    add_exit(VALLEY + "forest1", "northwest", 0, 1);
    add_exit(VALLEY + "forest9", "south", 0, 1);
    add_exit(VALLEY + "forest4", "west", 0, 1);
}
