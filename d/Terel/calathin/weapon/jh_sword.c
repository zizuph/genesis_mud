/*
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include <macros.h>
#include <wa_types.h>

void
create_weapon()
{
  set_name(({"sword"}));
    set_adj("steel");
    set_short("steel sword");
    set_pshort("steel swords");
    set_long("A sturdy steel sword.\n");
    set_default_weapon(35, 35, W_SWORD, W_IMPALE|W_SLASH, W_ANYH, TO);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VALUE, 300);
}

