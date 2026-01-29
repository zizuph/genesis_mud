#pragma save_binary

inherit "/d/Genesis/ship/deck";

#include <stdproperties.h>
#include "ship.h"

void
create_deck()
{
    set_deck_sound("You hear a loud CRASH as the waves hit the hull "+
        "of the ship.\n");
        set_short("On the deck of a ship");
    set_long("You are standing on the deck of a brand new ship. "+
        "Someone has obviously gone to great lengths to customize "+
        "this ship to their own tastes. The rails are made of "+
        "bronze, the sails made from the finest silk around. There "+
        "are coils of ropes secured neatly to the deck and there "+
        "is a hatch in the deck that leads down a ladder.\n");
    add_item((({"bronze","rail","rails","bronze rails","bronze rail"})), "The rail is "+
        "made from bronze and goes all around the ship.\n");
    add_item((({"hatch","ladder"})),"The hatch is open and there is "+
        "a ladder that leads down to an area below.\n");
    add_item((({"ropes","coils"})),"Standard ship's equipment, "+
        "neatly arranged to prevent slippage in case of rough "+
        "weather.\n");
    add_item((({"sail","sails","mailsails","mainsail"})),"The large, triangular-shaped "+
        "sail contains the figure of a green dolphin on it.\n");

    add_prop(ROOM_I_NO_TELEPORT,1);
	add_prop(ROOM_I_INSIDE,0);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_HIDE,-1);

	add_exit(SHIPS+"cabin.c", "down", 0,0);
}
