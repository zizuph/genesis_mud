/* File:          /d/Khalakhor/ship/macdunn/faerie/box.c
 * Creator:       Teth
 * Date:          November 16, 1997
 * Modifications:
 * Purpose:       This is a box placed on the deck of the ship.
 *                It is used for charity.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/faerie/
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:      A charity box based on the ones found elsewhere.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>

void
create_container()
{
    set_name("box");
    add_name("container");
    set_adj("charity");
    add_adj("oak");
    add_adj("wooden");
    set_short("oak charity box");
    set_pshort("oak charity boxes");
    set_long("This oak charity box is used as a container for " +
      "charitable items.\n");
    add_cmd_item(({"box","oak box","wooden box","oak charity box",
        "charity box"}),({"break","destroy","smash"}),"You attempt " +
      "to destroy the box, but find its wood resistant to " +
      "any method you use.\n");
    add_item("oak","The oak of the box is a durable sturdy wood.\n");
    add_item(({"mechanism","metal mechanism","clamp","metal clamp"}),
      "The clamp can only be released by a key, which you don't " +
      "have.\n");
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 800000);
    add_prop(CONT_I_MAX_WEIGHT, 1000000);
    add_prop(CONT_I_MAX_VOLUME, 920000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(OBJ_M_NO_SELL, "If you managed to get this chest to a " +
      "store, please report it as a bug.\n");
    add_prop(OBJ_M_NO_GET, "The box is secured in place by a " +
      "metal mechanism that clamps it to the spot. You are unable " +
      "to remove it from this clamp.\n");
    add_prop(OBJ_I_VALUE, 150);
}
