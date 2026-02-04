/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * m_hall1_2.c
 *
 * Vader
 * Recoded by Sorgum 950708
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit CASTLE_DIR + "hall_room";

public int do_move(string str);

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({CASTLE_DIR + "monster/stronguard"});		 
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_long(query_long() + "It continues " +
	     "east, west, and south.  There is a statue here, and " +
	     "the Sherrifs office is north.\n");
    
     add_item(({"statue"}), "It is a statue of Vader.  Vader is to King " +
      "Bor-El like Merlin\nwas to King Arthur.  It is only fitting that " +
      "there would be a statue\nof him made.  You notice that the arm " +
      "of the statue looks a little worn.\n");

    add_item(({"arm"}), "It looks like it is moveable.\n");

    INSIDE;

    add_exit(CASTLE_DIR + "r_hall1_6", "east",  0);
    add_exit(CASTLE_DIR + "l_hall1_6", "west",  0);
    add_exit(CASTLE_DIR + "m_hall1_1", "south", 0);
    add_exit(CASTLE_DIR + "sh_office", "north", 0);

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
   add_action(do_move, "pull");
   add_action(do_move, "move");
}

/*
 * Function name: do_move
 * Description:   Handle the enter/pull action
 * Returns:       1/0
 */
public int
do_move(string str)
{
    if(!strlen(str) || (str != "arm")) {
	NF("What?\n");
	return 0;
    }
    
    write("As you pull the arm, you hear a mechanism.\n" +
	  "You hear several noises coming from underneath you.\n" +
	  "The ground opens up beneath you!\n");
    say(QCTNAME(TP) + " pulls the arm of the statue. and falls into a " +
	"hole in the ground.\n");
    TP->move_living("M", CASTLE_DIR + "vader_ent");
    tell_room(CASTLE_DIR + "vader_ent", QCTNAME(TP) + " falls from a hole " +
	      "in the ceiling.\n", TP);
    return 1;
} 
