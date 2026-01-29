/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * hotel_priv.c
 *
 * Private room for the hotel staff.
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
    set_short("Private room");
    set_long("This is a private room for the staff of this lodging house. " +
	     "What are you doing here?\n");
   
    add_exit(PORT_DIR + "hotel",  "west", 0);
}
