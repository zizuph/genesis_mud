/* /d/Calia/argos/farmstead/mobiles/brigand_spear.c
**   A spear wielded by the brigands at the farmstead near Argos
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   5/2/20    Brine      Created
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

    set_name(({ "spear", "weapon", "thrusting-spear" }));
    set_adj(({ "crude", "thrusting" }));

    set_short("crude spear");
    set_long(
        "It is a somewhat crudely made thrusting-spear, made from affixing a "
        + "slender steel head to a straight wooden stick.\n"
    );

    set_default_weapon(20, 15, W_POLEARM, W_IMPALE, W_ANYH);

    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 800);
}
