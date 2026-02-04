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
    set_name(({"knife"}));
    set_adj("large");
    set_short("large knife");
    set_pshort("large knives");
    set_long("A large knife. The edge looks pretty sharp.\n");
    set_default_weapon(10, 10, W_KNIFE, W_IMPALE|W_SLASH, W_ANYH, TO);
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VALUE, 500);
}
