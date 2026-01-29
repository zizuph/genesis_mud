/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road_s12.c
 *
 * This is a standard south road. Mortricia 920723
 * Modified by Sorgum 941226
 *    Lilith, Mar 2022: updated room with desc of the Minstrels location.
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
#define DAB_ROAD DABAAY_DIR + "road/"

#include "enchanted.h"

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("The southern road, close to great forest");
   
    set_long("You are now standing just south of the great forest. " +
	     "There are trees scattered around the road. " +
	     "The road goes in the north-south direction, and " +
	     "a small path opens up to the east. The forest "+
         "clears to the southwest, with a road leading to a "+
         "large gothic building that rises above the canopy, its "+
         "spiral minarets shining silver-white in the light.\n");
		 
    add_item(({"building", "gothic building", "shining building",
	    "minarets", "southwest", "southwest road"}),
        "A large gothic building with spiral minarets rises up in "+
        "the southwest. It must be the famed home of the Minstrels.\n");		
    add_item(({"tree", "trees", "conifers", "conifer"}),
	     "Some of the conifers look very old, " +
	     "but there are a few saplings as well. The trees grow thicker " +
	     "here.\n");
    add_item(({"east", "trail"}), "That way leads through the enchanted "+
        "forest toward the enchanted garden.\n");
    add_item(({"snow"}), "The snow never disappears in this part of " +
    "the world. Here it's damn cold unless you have warm clothes.\n"); 
    add_item(({"forest"}), "The forest looks dark, perhaps even a bit " +
    "enchanted. The forest consists mostly of conifers.\n");
   
    add_prop(OBJ_S_WIZINFO, "South heads towards the port!");

    add_exit(ENCHANT_DIR + "forest17", "north", 0);
    add_exit(ENCHANT_DIR + "path_a6",  "east",  0);
    add_exit("/d/Terel/cedric/guild/entrance","southwest",0);
    add_exit(DAB_ROAD +    "n17",    "south", 0);
}

later()
{
    write("A tree has fallen over the road, and\n" +
        "effectively blocks any attempt to go south.\n" +
        "A fresh breeze carries the smell of the sea air.\n");
    return 1;
}
