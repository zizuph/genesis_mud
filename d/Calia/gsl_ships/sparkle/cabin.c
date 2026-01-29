/*
 * Cabin for the Ship between Sparkle and Gelan in Calia
 *
 * Created by Petros, April 2009
 */
#pragma save_binary

#include <stdproperties.h>
#include "ship.h"

inherit STDSHIPROOM;

void
create_room()
{
    create_shiproom();

	set_cabin_sound("As the ship moves, the hammock sways "+
		"back and forth.\n");
		
    set_short("The captain's cabin");
    set_long("This room is small and neat, with everything in "+
        "place. The walls conform to the inside of the "+
        "ship's hull with its gracefully curved planks. "+
        "On the far side is a hammock, which sways with the "+
        "movement of the ship. You see a small wooden table "+
        "and wooden shelves, which are secured to the walls "+
        "and floor. On the side opposite from the hammock is a "+
        "very compact kitchen area. Everywhere you look you "+
        "see the gleam of polished teak and brass fixtures. "+
        "Clearly the captain keeps things ship-shape. "+
        "There is a small narrow ladder that leads up to "+
        "the deck.\n");

    add_item((({"shelf", "shelves", "wooden shelves"})),
        ("The shelves are enclosed behind locked glass "+
        "doors. They contain scrolls that look like "+
        "maps and other nautical books.\n"));

    add_item((({"table", "wooden table"})),
        ("There's nothing on the table, and everything "+
        "appears to be put away. The surface of the table "+
        "is polished and gleams.\n"));
    add_item((({"kitchen", "kitchen area", "stove"})),
        ("The kitchen area contains a basin and a small "+
        "stove that's mounted on a swivel, so that it won't "+
        "spill when the ship moves.\n"));
    add_item("ladder", "The ladder is narrow, but well-built. "+
        "It is secured to the hatch and floor, and has a "+
        "safety rail.\n");

    add_item("hammock", "The hammock actually looks "+
        "quite comfortable. Maybe you could lie down in it.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_IS,1);
    add_prop(ROOM_I_HIDE, -1);
    add_prop(ROOM_I_NO_TELEPORT,1);

    add_exit("deck", "up");
}

