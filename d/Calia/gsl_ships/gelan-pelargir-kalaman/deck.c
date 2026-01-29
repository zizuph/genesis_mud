/* Deck on the ship from Calia to Krynn */

#pragma save_binary

inherit "/d/Genesis/ship/deck";

#include <stdproperties.h>
#include "ship.h"

void
create_deck()
{
	set_deck_sound("The ship sways back and forth in the breeze.\n");
	set_short("The deck of a floating walnut ship");
	set_long("You are standing on the deck of a ship " +
              "(and the term is used loosely here) that has an " +
              "unusual shape. Half as wide as it is long, and with a " +
              "shallow keel, the boat is made of knotted wood that has " +
              "been painted beige. The net result is a vessel that looks " +
              "like a gigantic upturned walnut half-shell. " +
              "Lunacy, yes, and this is not surprising - it was " +
              "designed by Master Lagrippe of Gelan, the first " +
              "man to marry the disciplines of modern art and ship " +
              "building (also the only man to have been blacklisted by " +  
              "both the shipwrights' guild and the guild of high level " +
              "artists). Below is a cabin.\n"); 

	add_prop(ROOM_I_INSIDE,0);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_LIGHT, 1);
        add_prop(ROOM_I_NO_TELEPORT,1);
        add_prop(ROOM_I_HIDE,-1);
	add_exit(SHIPS+"cabin.c", "down", 0,0);
}
