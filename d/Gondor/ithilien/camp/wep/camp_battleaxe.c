/* battleaxe  */
#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

public void
create_weapon()
{
    set_name(({"battleaxe","axe","weapon"}));
    set_pname("battleaxes");
    add_pname("axes");
    set_short("camouflaged battleaxe");
    set_pshort("camouflaged battleaxes");
    set_long("This heavy battleaxe resembles the weaponry of soldiers of "
        + "Gondor. It has been painted in such a way to make it less obvious "
        + "in a forest setting.\n");
    set_adj( ({ "camouflaged", "heavy", "large", "gondorian", }) );
    set_default_weapon(35,40,W_AXE,W_SLASH,W_BOTH,0);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(35, 40)+random(400)-200);
    add_prop(OBJ_I_WEIGHT,
     (F_WEIGHT_DEFAULT_WEAPON(35, W_AXE) + random(500) + 1000));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);

    add_prop(GONDOR_M_RANGERS_NO_SELL,1);
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
}
