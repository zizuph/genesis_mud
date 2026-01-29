/* /d/Calia/argos/farmstead/weapons/scythe.c
**   A flimsy old scythe, not much good outside of using for
**   the farmstead quest
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   2/23/20    Brine      Created
**
*/

#pragma strict_types

inherit "/std/weapon";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "defs.h"

void
create_weapon()
{
    seteuid(getuid());

    set_name("scythe");
    set_pname("scythes");

    set_adj("rusty");

    set_short("rusty scythe");

    set_long(
        "A rusted farmer's tool, for mowing grass and reaping crops. It "
        + "consists of a steel blade attached to a snath, the snath being "
        + "roughly the length of a man and slightly bent. Grips are fitted "
        + "on the lower end and at the bend, making it easy to generate "
        + "force when swinging it properly. The blade is around 2 feet long "
        + "and curved inwards toward the user. While it is an excellent "
        + "tool for farming, it probably wouldn't do much good in a fight.\n"
    );

    set_default_weapon(20, 10, W_POLEARM, W_SLASH, W_BOTH);

    add_prop(OBJ_I_VOLUME, 1000); // ?
    add_prop(OBJ_I_WEIGHT, 1800); // Scythes are surprisingly light-weight
    add_prop(OBJ_I_VALUE, 40);

    // These variables are declared in /std/weapon. Normally they would be
    // updated through set_dull and set_corroded, but doing it this way
    // carries a high chance of the weapon breaking when cloned.
    dull = 1;
    corroded = 2;
    set_likely_break(12);
}
