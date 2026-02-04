/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * m_hall1_1.c
 *
 * Vader
 * Recoded by Sorgum 950708
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit CASTLE_DIR + "hall_room";

public int enter(string str);

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
	     "to the north, and ends at a curtain to the south.  " +
	     "There are rooms to the west and east as well.\n");
    
    set_dircmd("curtain");
    
    add_item(({"statue"}),
	     "It is a statue of Vader.  Vader is to King " +
	     "Bor-El like Merlin\nwas to King Arthur.  It is only " +
	     "fitting that there would be a statue\nof him made.  You " +
	     "notice that the arm of the statue looks a little worn.\n");
    INSIDE;

    add_exit(CASTLE_DIR + "k_trophy",  "west",  0);
    add_exit(CASTLE_DIR + "k_bed",     "east",  "@@guarded");
    add_exit(CASTLE_DIR + "m_hall1_2", "north", 0);
    set_dircmd("curtain");
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
   add_action(enter, "enter");
   add_action(enter, "move");   
}

/*
 * Function name: enter
 * Description:   Handle the enter action
 * Returns:       1/0
 */
public int
enter(string str)
{
    if(!strlen(str) || (str != "curtain")) {
	NF("Enter what?\n");
	return 0;
    }
    
    write("You enter the curtain.  There is a hallway behind it.\n");
    TP->move_living("through the curtain", CASTLE_DIR + "throne_room");
    
    return 1;
}

/*
 * Function name: guarded
 * Description:   Don't let player pass if guards are present
 * Returns:       1
 */
public int
guarded()
{
    if(!present("knight"))
	return 0;
    
    write("As you attempt to enter the bedroom, the Knight halts " +
	  "your progress.\n");
    return 1;
}

