/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * k_bed.c
 *
 * Vader
 * Recoded by Sorgum 950708
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDROOM;

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Royal Bedchamber");
    set_long("This is where the King sleeps.  It is a king size bed, with " +
	     "King size mattresses, pillows, etc.  Included in this " +
	     "room are the other furnishings you would expect in a luxury " +
	     "bedroom.  Off in the shadow in one corner, you can barely " +
	     "make out a spiral staircase....leading up.\n");

    INSIDE;

    add_exit(CASTLE_DIR + "m_hall1_1", "west", 0);
    add_exit(CASTLE_DIR + "harem",     "up",   0);
}
