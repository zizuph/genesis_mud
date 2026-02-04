/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * landing_room.c
 *
 * A generic landing the Ribos castle.
 *
 * Vader
 * Recoded by Sorgum 950708
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

create_room()
{
    ::create_room();

    set_short("A terrace");
    set_long("You are on a wooden terrace above the courtyard.  The " +
	     "wood here is carved in a very intricate pattern.\n");
    
    add_item(({"wood", "carvings"}), 
	     "Carvings of great gods, goddesses, creatures, weapons, " +
	     "mountains, a few early kings, and knights decorate the " +
	     "terrace.\n");

    INSIDE;
}
