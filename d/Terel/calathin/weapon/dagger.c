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
    set_name(({"dagger","knife"}));
    set_adj("steel");
    set_short("steel dagger");
    set_pshort("steel daggers");
    set_long("A sturdy steel dagger. The blade is about 6 inches long "+
             "and just close to an inch wide. The hilt "+
             "is small and unadorned.\n");
    set_default_weapon(20, 20, W_KNIFE, W_IMPALE|W_SLASH, W_ANYH, TO);
    add_prop(OBJ_I_WEIGHT, 850);
    add_prop(OBJ_I_VALUE, 200);
}

