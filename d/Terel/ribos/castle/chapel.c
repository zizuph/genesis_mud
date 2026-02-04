/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * chapel.c
 *
 * Vader
 * Recoded by Sorgum 950712
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDROOM;

public int pray(string str);

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({RIBOS_DIR + "castle/monster/priest"});		 
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("The Castle Chapel");
    set_long("This is where the king and his family worship the gods.  " +
	     "Sometimes, on special occasions, they attend services at " +
	     "the church across from the castle, but people are so excited " +
	     "over his presence that it disrupts the service.  There is an " +
	     "altar here.  Also, a large stained glass window stands upon " +
	     "the south wall.  It is one of the only windows in the entire " +
	     "castle.\n");
 
    add_item("altar",
	     "It is made of a strange, white stone.  You can 'pray'.\n");
 
    add_item(({"window", "stained glass window"}),
	     "This window depicts the sun, with beams of light shining " +
	     "down upon a massive donut shaped object, which you know to " +
	     "be Genesis.  It also depicts the castle of ribos, standing " +
	     "upon the donut, much larger than it actually is.\n");
 
    INSIDE;
 
    add_exit(TOWER_DIR + "sw_tower2",  "southwest", 0);
    add_exit(CASTLE_DIR + "land2_1",   "east",      0);
 
    reset_room();
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
   ::init();
   add_action(pray, "pray");
}

/*
 * Function name: pray
 * Description:   Handle the pray action
 * Returns:       1/0
 */
public int
pray(string str)
{
    write("You kneel before the altar and concentrate your energies " +
	  "to praising the gods.\n");
    say(QCTNAME(TP) + " kneels before the altar and prays.\n");
    return 1;
}
