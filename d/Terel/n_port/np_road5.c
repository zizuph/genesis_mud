/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * np_road4.c
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
    ::create_room();
    set_short("A snow patched road");
    set_long("You are standing on a small snow patched road that ends " +
	     "eastward in a wooden pier that leads out onto the ocean.  " +
	     "To the west is the village.  The town shop and inn can be " +
	     "seen from here.  Taking in the air, you smell the salt on " +
	     "the water, and the cold burning your nostrils.  There are " +
	     "small blocks of ice on the water around here, the remains " +
	     "of icebergs that drifted south, then back here.  A small " +
	     "path leads north into a small igloo that has a sign " +
	     "over it.\n");

    add_item("igloo", "It's a small igloo with a sign on it.\n");
    add_item("sign", "The sign says: 'Bone doctor'\n");
   
    add_item(({"snow"}), "It is wet and slightly dirty.\n");

    add_item(({"mountains", "snowy mountains"}), 
	     "These mountains, which appear much closer than they " +
	     "actually are, reach high up into the sky, and go on " +
	     "westward for quite a ways.\n");

    add_item(({"forest", "large forest"}), 
	     "A large and thick forest, extending for miles.  One could " +
	     "easily get lost in this forest.\n");
    
    add_item(({"rocks", "ice"}),
	     "These rocks and large chunks of ice were made to protect " +
	     "the village from predators that live in the forest.  " +
	     "They also, unwillingly, keep you out.\n");
    
    add_item("water", "A large body of water, extending eastward for as far " +
	     "as the eye can see.  There are a few small icebergs " +
	     "spotted around.\n");

    add_item("path", "You see nothing special about this path.\n");
   
    add_item(({"arch", "gate"}), "You see nothing special here.\n");

    add_exit(NPORT_DIR + "np_road4","west",  0);
    add_exit(NPORT_DIR + "pier1.c", "east",  0);
    add_exit(NPORT_DIR + "igloo",   "north", 0);


}


