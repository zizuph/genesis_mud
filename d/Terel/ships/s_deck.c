/* This comment tells emacs to use c++-mode -*- C++ -*- */

#include "/d/Terel/include/Terel.h"
inherit "/d/Genesis/ship/deck";

/*
 * Function name: create_deck
 * Description  : Create the shipdeck
 */
public void
create_deck()
{
    set_short("On the deck");
    set_long("You are standing on the deck of the small fishing boat. " +
	     "You can enter the cabin.\n");

    add_exit(SHIP_DIR + "s_cabin", "cabin", 0);
}
