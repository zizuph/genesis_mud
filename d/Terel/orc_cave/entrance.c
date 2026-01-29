/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * entrance.c
 *
 * Entance to the orc cave.  Since the cave is dark inside, we put
 * two torches here so players without a light source can find their
 * way.
 */
 
#include "/d/Terel/include/Terel.h"
inherit ORC_CAVE_DIR + "cave_room";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Cave entrance");
    set_long(query_long() +
	     "Behind you, to the west, you can see the bright opening " +
	     "leading out.\n");

    add_exit(ORC_CAVE_DIR + "cave02", "east",      0);
    add_exit(ORC_CAVE_DIR + "cave04", "southeast", 0);
    add_exit(SILVER_DIR + "forest15", "west",      0);
    
    reset_room();
}

/*
 * Function name: reset_room
 * Description:   put two torches here at each reset
 */
public void
reset_room()
{
    object torch;
    
    ::reset_room();
    if (present("torch"))
	return;
    
    FIX_EUID;    
    torch = clone_object("/std/torch");
    torch->set_long("It's a standard torch.\n");
    torch->move(TO);

    torch = clone_object("/std/torch");
    torch->set_long("It's a standard torch.\n");
    torch->move(TO);    

    tell_room(TO, "There are two torches here.\n");
}

/*
 * Function name: smell_desc
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */ 
public string
smell_desc()
{
    return "There is a smell of foul creatures in the air.\n";
}

