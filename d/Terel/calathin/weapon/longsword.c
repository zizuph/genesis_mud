/*
 * A longsword for the guards of Calathin.
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
    set_name(({"longsword","sword"}));
    set_adj("steel");
    set_short("steel longsword");
    set_pshort("steel longswords");
    set_long("A sturdy steel longsword. The blade is about four feet long "+
             "and just close to two and a half inches wide. The hilt "+
             "is large an unadorned.\n");
    set_default_weapon(30, 30, W_SWORD, W_IMPALE|W_SLASH, W_ANYH, TO);
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VALUE, 600);
}

