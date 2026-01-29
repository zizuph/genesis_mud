/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tunnel.c
 *
 * A generic tunnel in the Legion of Darkness.
 * Redhawk 921020
 * modified by Sorgum 941015
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
    set_short("A tunnel that extends from the legions quarters");
    set_long("You are standing in a tunnel that seems to be carved out " +
	     "from solid rock, there is water dripping from the ceiling " +
	     "and the tunnel is lit up by torch in its stand. \n");

       add_item(({"torch"}), "It's an ordinary torch of wood.\n");

    INSIDE;
}
 
