/* /d/Calia/argos/farmstead/mobiles/brigand_britches.c
**   Leather britches worn by the brigands at the farmstead near Argos
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   5/2/20    Brine      Created
**
*/

#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "defs.h"

void
create_armour()
{
    seteuid(getuid());

    set_name(({ "britches", "armour" }));
    set_adj(({ "soft", "leather" }));

    set_short("soft leather britches");
    set_long("They are a pair of britches made from soft leather.\n");

    set_ac(4);
    set_am(({ -1, 0, 1 }));

    set_at(A_LEGS);

    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 1500);
}
