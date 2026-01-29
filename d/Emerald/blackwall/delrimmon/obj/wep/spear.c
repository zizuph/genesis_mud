/*
 *  /d/Emerald/blackwall/delrimmon/obj/wep/spear.c
 *
 *  This spear is standard issue for troops in the Army of Darkness.
 *
 *  Copyright (c) ?? 1996, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/weapon.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

public void
create_weapon()
{
    set_name("spear");
    add_adj( ({ "black-tipped", "iron" }) );
    set_short("black-tipped spear");
    set_pshort("black-tipped spears");
    set_long(BSN("This spear is long and deadly looking. Tightly woven"
        + " black cords have been wound around the midsection of the"
        + " lengthy shaft to support a solid grip. The blade of the"
        + " spear seems to be made of iron which has been"
        + " blackened by some foul process."));
    set_default_weapon(33, 40, W_POLEARM, W_IMPALE, W_BOTH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(17, W_POLEARM));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(17, 34) + random(75));
}
