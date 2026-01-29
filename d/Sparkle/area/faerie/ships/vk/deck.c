/*
 * The deck of the ship between Faerie and VK.
 * Based on the Pelargir ship in Gondor.
 * Modified by Finwe, January 2006
 */

#pragma save_binary

#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/ship/deck";

void
create_deck()
{
    set_short("On a large ship");
    set_long("You're standing on a large ship. It looks seaworthy and " +
        "is used for travel to faraway lands. The deck is uncluttered " +
        "and probably cleaned regularly by sailors. There are two " +
        "tall masts supporting sails. A set of stairs leads down from " +
        "the deck to a cabin below.\n");
    add_item(({"mast", "masts"}),
        "There are two tall masts secured to the deck. They support three large sails and several smaller sails. A bowsprit extends out from front of the ship.\n");
    add_item(({"bowsprit"}),
        "This is a long pole that extends out from the front of the ship. It points upwards slightly and is used to secure sails to it.\n");
    add_item(({"sail", "sails"}), 
        "The sails are made from thick, incredibly strong canvas. The three main sails are tall, triangular shaped, and connect to the main masts and bowsprit.\n");
    add_item(({"ship"}), 
        "You are standing on a large sailing ship with a two great masts. A set of stairs lead down from the deck to the cabin below.\n");
    add_item(({"stairs"}),
        "They are narrow and lead down to a cabin.\n");
    
    add_exit(VK_SHIP_DIR + "cabin", "down");

    add_prop(ROOM_I_HIDE, 50);

}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    return;
}
