/*
 * A battleaxe the body-guard
 * Coded by Tomas  --  April 2000
 *
 */

#include "/d/Terel/include/Terel.h"
inherit STDWEAPON;
#include <macros.h>
#include <wa_types.h>

void
create_weapon()
{



    set_name("battleaxe");
    set_pname("battleaxes");
    add_name("axe");
    set_adj("long-handled");
    set_adj("steel");
    set_short("long-handled steel battleaxe");
    set_pshort("long-handled steel battleaxes");
    set_long("A sturdy steel battleaxe. The handle "+
             "is long and wrapped with leather.\n");
    set_default_weapon(35, 40, W_AXE, W_IMPALE|W_SLASH, W_BOTH, TO);
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VALUE, 600);
}

