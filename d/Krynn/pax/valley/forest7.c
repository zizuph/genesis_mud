/*
  Pax Tharkas, Valley.....

  forest7.c
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

string *herbs = HERB_MASTER->query_herbs( ({"mixedforest","hills", }));


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
        "growing very close here, close enough though for their " +
        "crowns to form a fine net of leaves, obscuring the view " +
        "to, or from, above. Southwards the grounds starts to " +
        "slope very steep upwards forming an almost vertical " +
        "cliff and making any progress upwards impossible. A " +
        "small canyon scars the cliff side to the south. A small " + 
        "trickling stream flows from there, and down " +
        "northwards. An almost disappearing path leads north, " +
        "east, west and south, into the small canyon.\n"); 

    OUTSIDE;

    add_item("path", "A small path, almost invisible, leading " +
        "through the forest. It looks like it has been left almost " +
        "unused for a very long time. Something or someone must " +
        "have moved along it, otherwise it would probably " +
        "have disappeared totally.\n");

    add_item(({"stream", "ditch"}),"A small stream trickling through " +
        "the forest. Through the clear water you can see the granite " +
        "of the mountains forming an irregular, but solid, ditch.\n");

    add_item("canyon", "A small canyon cutting into the mountain side. " +
        "Trees and bushes seem to grow in there. A small path " +
        "leads into the canyon.\n");

    add_item(({"tree", "trees"}), "The largest part of the trees are " +
        "hardwood trees, like birch or aspen. None of them are " +
        "specially tall, probably due to the sparse soil here on " +
        "the mountain slopes.\n");

    add_item("soil", "It looks like fertile mould. It is very sparse " +
        "here on the mountain slopes.\n");

    add_item("rock", "The naked stone of the mountain visible " +
        "through the sparse soil.\n");

    set_up_herbs( ({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
                        ONE_OF(herbs) }), ({"soil","ground",}), 4);

    add_prop(OBJ_I_CONTAIN_WATER, -1);
    
    set_tell_time(60);
    add_tell("Water trickles gently down the stream.\n");
      
    add_exit(VALLEY + "forest3", "north", 0, 1);
    add_exit(PSLA + "o_entrance", "south", 0, 1);
    add_exit(VALLEY + "forest8", "east", 0, 1);
    add_exit(VALLEY + "forest6", "west", 0, 1);
}

void
init()
{
    ::init();
    add_action("drink_water", "drink");
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
