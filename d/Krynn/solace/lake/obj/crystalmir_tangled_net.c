/*
 *  Net spawned through fishing at Crystalmir lake outside
 *  Solace that generates a unique robe.
 *
 *  inherits /d/Krynn/common/fishing/tangled_net.c
 *
 *  Arman Kharas, October 2021 
 */

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

inherit "/d/Krynn/common/fishing/tangled_net";

#define ROBE             "/d/Krynn/solace/lake/obj/vwrobe"

public void
create_net()
{
    // Mask this function to customize the object description, 
    // set the net reward, set the custom verb to 'open' the
    // object, and the object destruct message.

    set_name("net");
    set_adj("tangled");
    set_short("tangled net");
    set_long("An old abandoned net that has tangled itself " +
        "around something. You could probably try and " +
        "untangle the net to see what that object is.\n");
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500);

    set_net_reward(ROBE);
    set_custom_verb("untangle");
    set_destruct_msg("falls to pieces in your hands");

}
