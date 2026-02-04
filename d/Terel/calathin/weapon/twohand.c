/*
 * A two-handed for the guards and arena of Calathin.
 * Coded by Shinto 10-7-98
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include <macros.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name(({"two-handed sword","sword"}));
    set_adj("steel");
    set_short("steel two-handed sword");
    set_pshort("steel two-handed sword");
    set_long("A sturdy steel two-handed sword. The blade is about "+
             "four feet long and just close to two and a half "+
             "inches wide. The hilt is large an unadorned.\n");
    set_default_weapon(30, 30, W_SWORD, W_IMPALE|W_SLASH, W_BOTH, TO);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VALUE, 600);
}

