/*
 * A sword for the std_goblin_grd.c
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
    set_adj("iron");
    set_short("iron sword");
    set_pshort("iron swords");
    set_long("An iron sword. It looks like it could do some damage.\n");
    set_default_weapon(30, 30, W_SWORD, W_IMPALE|W_SLASH, W_ANYH, TO);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VALUE, 500);
}
