#pragma save_binary

inherit "/d/Genesis/ship/deck";

#include <stdproperties.h>
#include "/d/Gondor/common/lib/time.h"
#include "/d/Gondor/defs.h"

void
create_deck()
{
    set_short("aboard the large ship");

    set_long("The deck of the river boat is narrow. Near the bow, the deck " +
        "gives way to a large open cargo hold. The sails on the masts " +
        "are up and billow in the wind. The oars are  used to navigate " +
        "rivers and close quarters. A set of stairs leads down a hatch " +
        "to the captain's cabin.");
    add_item(({"mast", "masts"}),
        "There are three masts that support three great sails. The masts " +
        "are made of strong wood. The great mast rises above the other " +
        "two. You see people high up in the masts, climbing about.");
    add_item("people",
        "These people climb about in the rigging, tying ropes and securing " +
        "the sails. They look quite busy.\n");
    add_item("oars", 
        "You notice oars sticking out from each side of the boat. They " +
        "are powered by the rowers on the decks below.");
    add_item(({"sail", "sails"}), 
        "The sails are made out of thick white canvas. They are square " +
        "shaped and billow in the wind.");

    add_exit(SHIP_DIR + "cabin8", "down", 0);

    add_prop(ROOM_I_HIDE, 50);
}