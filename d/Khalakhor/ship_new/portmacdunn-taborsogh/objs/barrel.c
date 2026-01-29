/* File:          /d/Khalakhor/ship/macdunn/ansalon/barrel.c
 * Creator:       Teth
 * Date:          April 20, 1997
 * Modifications: Cotillion - 2005-07-19
 *                - Fixed reset of too many pickles
 *
 * Purpose:       This is a barrel placed on the deck of the ship.
 *                It contains pickles.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/ansalon/
 *                /d/Khalakhor/ship/macdunn/ansalon/pickle.c
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:      A little something for free.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/receptacle";
#include <stdproperties.h>
#include "../ship.h"

public void
reset_receptacle()
{
    object food;
    
    setuid();
    seteuid(getuid());

    /* This is a heap requires a different kind of reset */
    food = present("gherkin", this_object());
    if (!food)
    {
        food = clone_object(SHIPLINE_DIR + "objs/pickle");
        food->move(this_object(), 1);
    }

    food->set_heap_size(5 + (random(16)));    
    this_object()->add_prop(CONT_I_CLOSED, 1);
}

public void
create_receptacle()
{
    set_name("barrel");
    add_name("receptacle");
    set_pname("barrels");
    set_adj("oak");
    add_adj("wooden");
    add_adj("prominent");
    set_short("oak barrel");
    set_pshort("oak barrels");
    set_long("This oak barrel is constructed of slats. It " +
      "appears to be used to transport food.\n");
    add_item("lid","The lid on the barrel is thick and heavy, " +
      "to create a better seal.\n");
    add_item(({"slats","barrel slats","wooden slats"}),"The wooden " +
      "slats of the barrel are made of cured oak.\n");
    add_cmd_item(({"barrel","oak barrel","wooden barrel"}),({"break",
        "destroy","smash"}),"You attempt to destroy the barrel, but " +
      "find its wood resistant to any method you use.\n");
    add_item(({"mechanism","metal mechanism","clamp","metal clamp"}),
      "The clamp can only be released by a key.\n");

    add_prop(CONT_I_WEIGHT, 35350);
    add_prop(CONT_I_MAX_WEIGHT, 78250);
    add_prop(CONT_I_VOLUME, 12000);
    add_prop(CONT_I_MAX_VOLUME, 90025);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_SELL, "If you managed to get this chest to a " +
      "store, please report it as a bug.\n");
    add_prop(OBJ_M_NO_GET, "The barrel is secured in place by a " +
      "metal mechanism that clamps it to the spot. You are unable " +
      "to remove it from this clamp.\n");
    add_prop(OBJ_I_VALUE, 2520);

    enable_reset(200);
    reset_receptacle();
}
