/* /d/Calia/argos/farmstead/mobiles/brigand_sword.c
**   A sword wielded by the brigands at the farmstead near Argos
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

    set_name(({ "gladius", "sword", "weapon", "short-sword" }));
    set_adj(({ "steel", "short" }));

    set_short("steel gladius");
    set_long(
        "It is a double-bladed short steel sword. It could make some nasty "
        + "cuts when swung by a competent arm.\n"
    );

    set_default_weapon(23, 18, W_SWORD, W_SLASH, W_ANYH);

    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 900);
}
