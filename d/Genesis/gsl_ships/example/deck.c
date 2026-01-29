/*
 * Deck for Test Ship
 *
 * Created by Petros, April 2009
 */

#pragma save_binary

#include <stdproperties.h>
#include "../ships.h"

inherit STDSHIPROOM;

public void
create_room()
{
    create_shiproom();

	set_deck_sound("The ship cuts through the waves and "+
		"water splashes the deck.\n");
	set_short("The deck of the test ship");
	set_long("This is the deck of the test ship.\n");

	add_prop(ROOM_I_INSIDE,0);
	add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_NO_TELEPORT,1);
    add_prop(ROOM_I_HIDE, -1);

    set_is_deck(1);	    
}
