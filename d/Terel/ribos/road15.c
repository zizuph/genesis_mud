/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * road15.c
 *
 * A road in Ribos
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

int opened;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Smooth road");
    set_long("This road leads south to a large cave opening.  " +
	     "The way into the cave is blocked by a huge, impenetrable " +
	     "iron door.\n");

    add_item(({"door", "iron door", "doors", "iron doors"}), 
	     "These doors have been welded shut.  There is no way in.\n");
    
    opened = 0;
    
    add_exit(RIBOS_DIR + "intsec3", "north", 0);
}

/*
 * Function name: do_open
 * Description:   Open the entrance to the dragon cave
 */
public void
do_open()
{
    if(opened == 1)
	return;
    
    set_long("This road leads south to a large cave opening.  " +
	     "There is a huge gaping hole in the iron doors to your south.\n");
    
    opened = 1;
    
    say("With a sonic boom of outstanding decibels, the huge iron door is " +
	"no more.\n");
    
    add_item(({"door", "iron door", "doors", "iron doors"}), 
	     "All that is left is a twisted mass of iron.\n");
    
    add_exit(RIBOS_DIR + "dragon_cave", "south", 0); 
}
