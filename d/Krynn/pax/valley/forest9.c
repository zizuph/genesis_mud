/*
   Pax Tharkas, Valley.....

   forest9.c
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

string *herbs = HERB_MASTER->query_herbs( ({"mixedforest","hills",}));


void
reset_pax_room()
{
   set_searched(4);
}


void
create_pax_room()
{
   reset_pax_room();

   set_short("Light forest at mountain side");
   set_long("You are standing in a light forest. The trees aren't " +
            "growing very close, but close enough for their crowns " +
            "to almost cover the view of the sky. The slopes begins " +
            "to go very steep upwards, ending in an almost vertical " +
            "cliff, making any sort of progress southwards, upwards, " +
            "impossible. Here and there the naked rock of the mountains " +
            "breaks through the layer of soil covering them. A small, " +
            "almost invisible path, leads north.\n");

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

   add_item("rock", "The naked stone of the mountain visible " +
            "through the sparse soil.\n");

    set_up_herbs( ({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({ "soil","ground","rocks", }), 7);

   add_exit(VALLEY + "forest5", "north", 0, 1);
}
