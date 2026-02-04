/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * sh_office.c
 *
 * Vader
 * Recoded by Sorgum 950712
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDROOM;

#include "/d/Terel/include/quest_bits.h"

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({CASTLE_DIR + "monster/sherrif"});		 
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Sherrifs office");
    set_long("This is the office of the Sherrif of Ribos.  He oversees " +
	     "law and order in the town of Ribos.  The office is rather " +
	     "plain and spartan.  There is only his desk in the middle, " +
	     "a few momentos on the desk, and a small staircase that must " +
	     "lead down to the dungeons.\n");
    
    add_item(({"staircase", "small staircase"}), 
	     "This is a dark, narrow staircase that leads down into the " +
	     "bowels of the castle.  Many castles keep their dungeons " +
	     "there, not that you would want to find out, personally.\n");

    add_item(({"desk", "sherrifs desk", "momentos"}), 
	     "Atop this plain wooden desk are a few scant possesions, most " +
	     "likely to remind the man of some glorious achievement of his " +
	     "past.\n");

    INSIDE;

    add_exit(CASTLE_DIR + "m_hall1_2.c", "south", 0);
    add_exit(CASTLE_DIR + "d_foyer",    "down",  "@@closed");
    
    reset_room();
}

/*
 * Function name: closed
 * Description:   VBFC to handle closed exit
 * Returns: 1
 */
public int
closed()
{
    write ("You are blocked by a powerful magical force.\n");    
    return 1;
}


