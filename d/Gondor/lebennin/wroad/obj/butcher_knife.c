#pragma strict_types

inherit "/std/weapon.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

void
create_weapon()
{
    set_name("knife");
    set_adj("steel");
    set_short("butcher's knife");
    set_pshort("butchers knives");
    set_long("A well crafted butcher's knife made of steel.");

    set_default_weapon(10, 10, W_KNIFE, W_SLASH, W_ANYH, 0);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(10,10));
    add_prop(OBJ_I_WEIGHT,500);
    add_prop(OBJ_I_VOLUME,250);
}
