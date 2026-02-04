/*
 * Polearm for use with the Stronghold warriors
 * Tomas  -- Jan 2000.
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include <macros.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name(({"arbir","polearm","staff"}));
    set_adj("steel");
    set_short("steel arbir");
    set_pshort("arbirs");
    set_long("A pointed wooden staff to which a wide, curved " +
                      "blade is attached to the shaft which is long an unadorned.\n");

    set_default_weapon(30, 30, W_POLEARM, W_IMPALE|W_SLASH, W_BOTH, TO);
    add_prop(OBJ_I_WEIGHT, 4500);
    add_prop(OBJ_I_VALUE, 800);
}
