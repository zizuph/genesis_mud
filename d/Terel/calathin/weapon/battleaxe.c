/*
 * A battleaxe for the guards of Calathin.
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
    set_name(({"battleaxe","axe"}));
    set_adj("steel");
    set_short("steel battleaxe");
    set_pshort("steel battleaxes");
    set_long("A sturdy steel battleaxe. The blade is about one feet wide "+
             "and just close to one foot wide. The handle "+
             "is long and wrapped with leather.\n");
    set_default_weapon(35, 35, W_AXE, W_IMPALE|W_SLASH, W_ANYH, TO);
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VALUE, 600);
}

