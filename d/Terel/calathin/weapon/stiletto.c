/*
 * A dagger for the guards and arena of Calathin.
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
    set_name(({"stiletto","dagger","knife"}));
    set_adj("steel");
    set_short("steel stiletto");
    set_pshort("steel stilettos");
    set_long("A sturdy steel stiletto. The blade is about a foot long "+
             "and just close to an inch wide. The hilt "+
             "is small an unadorned.\n");
    set_default_weapon(30, 30, W_KNIFE, W_IMPALE|W_SLASH, W_ANYH, TO);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VALUE, 200);
}

