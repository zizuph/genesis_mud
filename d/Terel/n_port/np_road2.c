/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * np_road2.c
 *
 *  Northern Terel Port 
 *  This is a road leading from the port to the northeast gates of Terel 
 *
 *  Coded by Vader on 9/25/93   
 *  Updated by Sorgum 12/4/94
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <ss_types.h>

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    set_short("A snow patched road");
    set_long("@@my_long");

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
	     "the village from predators that live in the forest.  They " +
	     "also, unwillingly, protect those predators from you.\n");

    add_item("water", "A large body of water, extending eastward for as far " +
	     "as the eye can see.  There are a few small icebergs " +
	     "spotted around.\n");

    add_item("path", "You see nothing special about this path.\n");
   
    add_item(({"arch", "gate"}), "You see nothing special here.\n");


    add_prop(ROOM_S_MAP_FILE, "town_last.txt");
	add_exit(NPORT_DIR + "np_road1", "west", 0);
    add_exit(LAST_DIR + "lroad1", "east", 0);
}

/*
*/

/*
 * Function name: my_long
 * Description:   Return the long description of the room.
 * Returns:       string
 */ 
public string
my_long()
{
    string desc = 
	 "As you gaze eastward, you can see a few people milling about in " +
	 "the small port village.  The ocean beyond is dotted with small " +
	 "icebergs, and the sky is blue and sunny, yet cold.  West, you " +
	 "can see a silver arch, with a silver gate.  Forests are seen to " +
	 "the south, but rocks and ice make the forest unreachable from " +
	 "here.\n";



    return desc;
}





