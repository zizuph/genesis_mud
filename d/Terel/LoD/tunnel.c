/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tunnel.c
 *
 * A generic tunnel in the Legion of Darkness.
 * Redhawk 921020
 * modified by Sorgum 941015
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "legion_room";

/*
 * Function name: wall_desc
 * Description:   Returns description of walls.
 */
public string
wall_desc()
{
    return "earth and mud";
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("A tunnel that extends from the legions quarters");
    set_long("This is a tunnel with walls that seems to be of earth and mud " +
	     "there are big logs of wood that support the walls and the " +
	     "ceiling so they don't fall in, the tunnel is lit by a torch " + 
	     "in its stand.\n");

    add_item(({"torch"}), "It's an ordinary torch of wood.\n");
}
 
