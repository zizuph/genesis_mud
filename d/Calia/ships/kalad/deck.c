#pragma save_binary

inherit "/d/Genesis/ship/deck";

#include <stdproperties.h>
#include "ship.h"

void
create_deck()
{
    set_deck_sound("The black sails ruffle as they catch the wind.\n");
        set_short("On the deck of a ship");
    set_long("You are standing on the deck of a black ship. Everything "+
        "you see around you is the same colour of black making it "+
        "difficult to discern one thing from another. After careful "+
        "examination you discover a small hatch on the deck leading "+
        "down into the darkness below.\n");
    add_item((({"bronze","rail","rails","bronze rails","bronze rail"})), "The rail is "+
        "made from bronze and goes all around the ship.\n");
    add_item((({"hatch","ladder"})),"The hatch is open and there is "+
        "a ladder that leads down to an area below.\n");
    add_item((({"sail","sails","mailsails","mainsail"})),"The large, triangular-shaped "+
        "sails are dark black in colour and stretch far up into the "+
        "sky above you.\n");

    add_prop(ROOM_I_NO_TELEPORT,1);
	add_prop(ROOM_I_INSIDE,0);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_HIDE,-1);

	add_exit(SHIPS+"cabin.c", "down", 0,0);
}
