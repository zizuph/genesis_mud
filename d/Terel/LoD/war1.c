/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * war1.c
 *
 * A war room for the legion Redhawk 921103
 * Modified by Sorgum 941029
 *
 * Modified by Lilith 5 July 2008
 *  -added exit for war2.c to re-implement Mergula.
 *   He was taken out about 10 years ago pending implementation
 *   of Maskyr Keep. Maskyr Keep is unrealized, and people miss
 *   the thrill of fighting Mergula, so he's back.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "legion_room";

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({LOD_DIR + "monster/devil_knight"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("A giant war room in the legion quarters");
    set_long("You are standing in a war room where the legion's " +
	     "officers direct and follow the battles that this division " +
	     "of the legion fight.  There is a table in the middle of the " +
	     "room with some maps on it.  On the walls there are " +
	     "paintings of old battles that the legion have fought.\n"+
             "A door, once closed for nearly a decade, now lies open "+
             "to the south.\n");

    add_item(({"table"}), "It's a very big table whith lots of maps on it.\n");

    add_item(({"map", "maps"}), 
	     "These maps are filled with marks and symbols in different " +
	     "colours, and you realize that they must be very " +
	     "important papers for the legion command.  It is rather " +
	     "strange that these papers aren't more guarded.\n");

    add_item(({"painting", "paintings"}), 
	     "The paintings look well made and each painting is a " +
	     "portrait of a man that looks very old. But even though " +
	     "they look old you sense an evil aura emanate from each " +
	     "painting, you realize that these men probably are the "+
	     "most evil men in the world, and that they have " +
	     "walked the earth since time began.\n");

    add_exit(LOD_DIR + "hall.c",  "north", 0);
    add_exit(LOD_DIR + "war1e.c", "east",  0);
    add_exit(LOD_DIR + "war1w.c", "west",  0);
    add_exit(LOD_DIR + "war2.c",  "south",  0, 0, 1);    
    reset_room();
}
