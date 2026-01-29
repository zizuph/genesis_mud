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
	     "Snow and ice have hardened on the sides of this ship, and a " +
	     "harsh, bitter wind burns your nostrils.  " +
	     "You can enter the cabin.\n");

    add_exit(SHIP_DIR + "n_cabin", "cabin", 0);
}
