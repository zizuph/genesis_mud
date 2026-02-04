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
    add_adj("leather-handled");
    set_short("leather-handled steel dagger");
    set_pshort("leather-handled steel daggers");
    set_long("A sturdy steel dagger. The blade is about 6 inches long "+
             "and just close to an inch wide. The hilt "+
             "is small an unadorned. The handle is wrapped and bound "+
             "with a soft comfortable leather.\n");
    set_default_weapon(25, 27, W_KNIFE, W_IMPALE|W_SLASH, W_ANYH, TO);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_VOLUME, 750);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({"enchantment", 25}));
    add_prop(OBJ_S_WIZINFO, "This is a dagger enchanted to have a "+
             "little better hit and pen. 25 27. Nothing special about it.\n");
    add_prop(MAGIC_AM_ID_INFO, ({"The "+short()+" is enchanted to be a more "+
             "effective weapon in combat.\n", 25}));

}

