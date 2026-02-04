/*
 *  Dwarven shortsword for use with the Stonehold warriors
 *  Tomas  -- Jan. 2000
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
    set_default_weapon(30, 30, W_SWORD, W_IMPALE|W_SLASH, W_ANYH, TO);
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VALUE, 300);
}

