/*
 * A shortsword for the guards of Calathin.
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
  set_name(({"shortsword","sword"}));
    set_adj("steel");
    set_short("steel shortsword");
    set_pshort("steel shortswords");
    set_long("A sturdy steel shortsword. The blade is about two feet long "+
             "and just close to two and a half inches wide. The hilt "+
             "is small an unadorned.\n");
    set_default_weapon(23, 23, W_SWORD, W_IMPALE|W_SLASH, W_ANYH, TO);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VALUE, 300);
}

