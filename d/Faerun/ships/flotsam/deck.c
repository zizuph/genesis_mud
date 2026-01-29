/*
 * The deck of the ship between Faerie and VK.
 * Based on the Pelargir ship in Gondor.
 * Modified by Finwe, January 2006
 */

#pragma save_binary

#include "defs.h"
#include "/d/Faerun/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Genesis/ship/deck";

void
create_deck()
{
    set_short("On a shipping vessel");
    set_long("You're standing on a shipping vessel. It looks very fast and well cared for. The deck looks like it is regularly cleaned by the crew, and everything neatly stacked in its place. Two tall masts support the sails and a set of stairs leads below deck.\n");
    add_item(({"mast", "masts"}),
        "There are two tall masts secured to the deck. They support two large sails.\n");
    add_item(({"sail", "sails"}), 
        "The sails are made from thick, incredibly strong canvas. The two sails are tall, triangular shaped, and connect to the two masts.\n");
    add_item(({"ship"}), 
        "You are standing on a large sailing ship with a two great masts. A set of stairs lead below deck.\n");
    add_item(({"stairs"}),
        "They are narrow and lead below deck.\n");
    
    add_exit(FLOTSAM_DIR + "cabin", "down");

    add_prop(ROOM_I_HIDE, 50);

}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    return;
}
