/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * np_road3.c
 *
 *  Northern Terel Port 
 *  This is a road leading from the port to the northeast gates of Terel 
 *
 *  Coded by Vader on 9/25/93   
 *  Updated by Sorgum 12/4/94
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    set_short("A snow patched road");
    set_long("Standing in the middle of this small portside village, " +
	     "you take in a breath of cold, salty air.  You are on a " +
	     "small east to west road that ends eastward at a boat " +
	     "pier, and westward over a small, snow-covered hill.  The " +
	     "village store can be seen to the northeast " +
	     "while the village inn lies to the southeast.  " +
	     "Both look like a great place to get " +
	     "a feel for the culture of the area.\n");

    add_item(({"snow"}), "It is wet and slightly dirty.\n");

    add_item(({"hill", "small hill"}), 
	     "This snow covered hill goes up on a gradual incline for about " +
	     "300 yards, and completely obscures your vision of everything " +
	     "beyond.\n");

    add_item(({"forest", "large forest"}), 
	     "A large and thick forest, extending for miles.  One could " +
	     "easily get lost in this forest.\n");

   add_item(({"rocks", "ice"}), 
	    "These rocks and large chunks of ice were made to protect " +
	    "the village from predators that live in the forest.  They " +
	    "also, unwillingly, protect those predators from you.\n");

    add_item("water", "A large body of water, extending eastward for as far " +
	     "as the eye can see.  There are a few small icebergs " +
	     "spotted around.\n");

    add_item("path", "You see nothing special about this path.\n");
   
    add_item(({"pier", "boat pier"}), "You see nothing special here.\n");
   
    add_item(({"store"}), "This is 'The Grimacing Eskimo's Igloo'.  Here, " +
	     "you can supply yourself with all kinds of gear.\n");

    add_item(({"inn"}),
	     "This is Snooky's Seafood House.  He serves up the finest " +
	     "seafood on the entire continent.  The reason is because " +
	     "of the freshness.  Fish that is caught at sea stays " +
	     "fresh in this cold weather longer.\n");


    add_exit(NPORT_DIR + "np_road2", "west", 0);
    add_exit(NPORT_DIR + "np_road4", "east", 0);
}


