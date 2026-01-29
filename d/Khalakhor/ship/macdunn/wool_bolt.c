/* File:          /d/Khalakhor/ship/macdunn/wool_bolt.c
 * Creator:       Teth
 * Date:          November 29, 1997
 * Modifications:
 * Purpose:       The bolt of wool found in the crate.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/crate.c
 *                /d/Khalakhor/ship/macdunn/pier11.c
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
#include "local.h"
#include <stdproperties.h>

public void
create_object()
{
    set_name("bolt");
    add_name(({"wool","material"}));
    set_adj("woolen");
    add_adj(({"bolt of","tattered","soiled"}));
    set_short("bolt of wool");
    set_pshort("bolts of wool");
    set_long("This bolt of wool is in poor shape, tattered and " +
        "soiled. It is of no use to any weaver.\n");
    add_prop(OBJ_I_VALUE, 20);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 800);
}
