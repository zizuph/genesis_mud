/* File:          /d/Khalakhor/ship/macdunn/faerie/crate.c
 * Creator:       Teth
 * Date:          November 16, 1997
 * Modifications:
 * Purpose:       This is a crate placed on the deck of the ship.
 *                It contains crab apples.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/faerie/
 *                /d/Khalakhor/ship/macdunn/faerie/apple.c
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:      A little something for free.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/receptacle";
#include <stdproperties.h>
#include "local.h"

object food;

public void
reset_receptacle()
{
    seteuid(getuid());

    if (!food || !present(food))
    {
        food = clone_object(OBJ_DIR + "apple");
        food->set_heap_size(10 + (random(32)));
        food->move(this_object(), 1);
    }

    this_object()->add_prop(CONT_I_CLOSED, 1);
}

public void
create_receptacle()
{
    set_name("crate");
    add_name("receptacle");
    set_pname("crates");
    set_adj("sturdy");
    add_adj(({"wood","wooden","cherry","purple"}));
    set_short("sturdy cherry crate");
    set_pshort("sturdy cherry crates");
    set_long("This sturdy cherry crate is coloured a deep purple. " +
      "The lid on the crate can be opened and closed, and it " +
      "is certainly used to transport fresh food.\n");
    add_item("lid","The lid on the crate is thick and heavy, " +
      "to create a better seal.\n");
    add_item(({"sides","walls","wooden sides"}),"The wooden sides " +
      "of the crate are made of sanded cherry slats, and are " +
      "quite durable.\n");
    add_item(({"slats","cherry slats","sanded slats",
        "sanded cherry slats"}),"The slats are well-crafted.\n");
    add_cmd_item(({"crate","cherry crate","sturdy crate",
        "sturdy cherry crate","wood crate"}),({"break",
        "destroy","smash"}),"You attempt to destroy the crate, but " +
      "find its wood resistant to any method you use.\n");
    add_item(({"mechanism","metal mechanism","clamp","metal clamp"}),
      "The clamp can only be released by a key, which you don't " +
      "have.\n");

    add_prop(CONT_I_WEIGHT, 35350);
    add_prop(CONT_I_MAX_WEIGHT, 78250);
    add_prop(CONT_I_VOLUME, 12000);
    add_prop(CONT_I_MAX_VOLUME, 90025);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_SELL, "If you managed to get this crate to a " +
      "store, please report it as a bug.\n");
    add_prop(OBJ_M_NO_GET, "The crate is secured in place by a " +
      "metal mechanism that clamps it to the spot. You are unable " +
      "to remove it from this clamp.\n");
    add_prop(OBJ_I_VALUE, 2000);

    enable_reset(200);
    reset_receptacle();
}
