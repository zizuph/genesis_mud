/*
 * A battleaxe for the guards on Stronhold.
 * Tomas  -- Jan 2000.
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include <macros.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name(({"battleaxe","axe"}));
    set_adj(({"dwarven","steel"}));
    set_short("dwarven steel battleaxe");
    set_pshort("dwarven steel battleaxes");
    set_long("A sturdy steel battleaxe created by dwarven hands. " +
       "The axe feels well balanced and looks quite durable. " +
       "The handle is solid oak, wrapped in leather forming a weaved " +
       "pattern about the length of the handle to the blade. The " +
       "blade has been sharpened and honed forming a fine serrated " +
       "edge.\n");
    set_default_weapon(30, 40, W_AXE, W_IMPALE|W_SLASH, W_ANYH, TO);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VALUE, 600);
}

