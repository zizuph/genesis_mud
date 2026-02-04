/*
 * A handaxe for the guards and arena of Calathin.
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
    set_name(({"handaxe","axe"}));
    set_adj("steel");
    set_short("steel handaxe");
    set_pshort("steel handaxes");
    set_long("A sturdy steel handaxe. The blade is about six inches wide "+
             "and just close to six inches long. The handle "+
             "is short and wrapped with leather.\n");
    set_default_weapon(30, 30, W_AXE, W_IMPALE|W_SLASH, W_ANYH, TO);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VALUE, 600);
}

