/*
  Pax Tharkas, Valley.....

  forest3.c
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

string  *herbs = HERB_MASTER->query_herbs(({"mixedforest" }));

void
reset_pax_room()
{
    set_searched(-2);
}


void
create_pax_room()
{
    reset_pax_room();

    set_short("Light forest");
    set_long("You are standing in a light forest. The trees aren't " +
        "growing very close, but close enough for their crowns " +
        "to effectively obscure the view of, or from, the sky " +
        "above you. To the south the ground slopes somewhat " +
        "upwards. Large boulders lie around and here and there, " +
        "the naked rock of the mountains breaks through the layer " +
        "of soil covering them. North of you the forest gets thinner " +
        "and finally fades away into the open. A small, almost " +
        "dissapearing path, leads south and east.\n");

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

    set_tell_time(60);
    add_tell("You hear the distant sound of trickling water.\n");
    
    add_exit(VALLEY + "valley_road3", "north", 0, 1);
    add_exit(VALLEY + "forest7", "south", 0, 1);
    add_exit(VALLEY + "forest4", "east", 0, 1);

    set_up_herbs( ({ KRHERB + "soapweed", KRHERB + "chicory", KRHERB + "wild_plum", KRHERB +"hellebore" }), 
        ({ "growth", "forest", "herb growth", }), 3);

    reset_pax_room();
}


void
someone_arrives(object who, int from)
{
    tell_room(TO, QCTNAME(who) + " arrives.\n");
}

