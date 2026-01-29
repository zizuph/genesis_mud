/* File:          /d/Khalakhor/ship/macdunn/sparkle/box.c
 * Creator:       Teth
 * Date:          December 4, 1997
 * Modifications:
 * Purpose:       This is a box placed on the deck of the ship.
 *                It contains limes.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/sparkle/
 *                /d/Khalakhor/ship/macdunn/sparkle/lime.c
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
        food = clone_object(OBJ_DIR + "lime");
        food->set_heap_size(5 + (random(16)));
        food->move(this_object(), 1);
    }

    this_object()->add_prop(CONT_I_CLOSED, 1);
}

public void
create_receptacle()
{
    set_name("box");
    add_name("receptacle");
    set_pname("boxes");
    set_adj("sturdy");
    add_adj(({"wooden","well-crafted"}));
    set_short("sturdy box");
    set_pshort("sturdy boxes");
    set_long("This sturdy box is apparently a receptacle for food. " +
      "It is fairly well-crafted, using dove-tailed joints on the " +
      "edges of the box.\n");
    add_item("lid","The lid on the box fits exactly, creating " +
      "a near seamless seal.\n");
    add_item(({"joints","dove-tailed joints","edges"}),
      "The joints on the edge of the box are dove-tailed, creating " +
      "a tight fit, and preventing warping of the wood.\n");
    add_item("wood","The wood used for the box seems to be oak.\n");
    add_item("oak","Oak is typical of well-made containers.\n");
    add_cmd_item(({"box","sturdy box","wooden box"}),({"break",
        "destroy","smash"}),"You attempt to destroy the box, but " +
      "find its wood resistant to any method you use.\n");
    add_item(({"mechanism","metal mechanism","clamp","metal clamp"}),
      "The clamp can only be released by a key, which you don't " +
      "have.\n");

    add_prop(CONT_I_WEIGHT, 35350);
    add_prop(CONT_I_MAX_WEIGHT, 78250);
    add_prop(CONT_I_VOLUME, 12000);
    add_prop(CONT_I_MAX_VOLUME, 90025);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_SELL, "If you managed to get this chest to a " +
      "store, please report it as a bug.\n");
    add_prop(OBJ_M_NO_GET, "The box is secured in place by a " +
      "metal mechanism that clamps it to the spot. You are unable " +
      "to remove it from this clamp.\n");
    add_prop(OBJ_I_VALUE, 2520);

    enable_reset(200);
    reset_receptacle();
}
