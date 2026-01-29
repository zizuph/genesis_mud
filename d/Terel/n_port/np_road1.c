/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * np_road1.c
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
    set_long("Light patches of snow spot this road and the sparse grass " +
	     "and rocks around it.  A cool wet breeze blows into your " +
	     "nostrils from the east, and it smells of fresh fish.  As " +
	     "you look to the southwest, you can see a large forest in " +
	     "the distance.  Westward, you look upon the caps of high, " +
	     "snowy mountains.  Further east, you can see water.  " +
	     "To the northwest, you can see a moor, and beyond that a " +
	     "large, green valley that is well below the snow line, " +
	     "and thus much warmer.  A small path leads from east " +
	     "to west here.\n");

    add_item(({"snow"}), "It is wet and slightly dirty.\n");

    add_item(({"mountains", "snowy mountains"}),
	     "These mountains, which appear much closer than they " +
	     "actually are, reach high up into the sky, and go on " +
	     "westward for quite a ways.\n");

   add_item(({"forest", "large forest"}), 
	    "A large and thick forest, extending for miles.  One could " +
	    "easily get lost in this forest.\n");

    add_item("moor", "Nothing special about this moor.\n");

    add_item("water", "A large body of water, extending eastward for as far " +
	     "as the\neye can see.  There are a few small icebergs " +
	     "spotted around.\n");

    add_item("valley", "Lush and green, it extends northward for as far as " +
	     "they eye can see.\n");

    add_item("path", "You see nothing special about this path.\n");

    add_prop(ROOM_S_MAP_FILE, "town_last.txt");
	add_exit("/d/Terel/common/road/entrance", "west", 0);
    add_exit(NPORT_DIR + "np_road2",          "east", 0);

}


