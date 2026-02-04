/*
 * A polearm for the guards and arena of Calathin.
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
    set_name(({"spear","polearm"}));
    set_adj("steel");
    set_short("steel spear");
    set_pshort("steel spears");
    set_long("A sturdy steel spear. The blade is about a foot long "+
             "and just close to three and a half inches wide. The shaft "+
             "is long an unadorned.\n");
    set_default_weapon(30, 30, W_POLEARM, W_IMPALE|W_SLASH, W_BOTH, TO);
    add_prop(OBJ_I_WEIGHT, 4500);
    add_prop(OBJ_I_VALUE, 800);
}

