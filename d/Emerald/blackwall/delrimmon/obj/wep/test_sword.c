/*
 *  /d/Emerald/blackwall/delrimmon/obj/wep/longsword.c
 *
 *  This is one of the standard issue weapons crafted for the Army of
 *  Darkness by the Darklings.
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
    set_name("two-handed sword");
    add_name( ({ "sword" }) );
    add_adj( ({ "black", "iron" }) );
    set_short("black two-handed sword");
    set_pshort("black two-handed swords");
    set_long(BSN("Though made of iron, this weapon has been stained by some"
        + " foul process to leave the metal a deep black shade. Its long blade"
        + " widens slightly towards the crosspiece of this weapon, where"
        + " the symbol of a black skull gleams from within a circlet"
        + " just above the hilt. This weapon looks most deadly indeed."));
    set_default_weapon(38,33, W_SWORD, W_SLASH | W_IMPALE, W_BOTH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(31, W_SWORD) + random(100));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(38, 33) + random(45));
    add_prop(OBJ_M_NO_SELL, 1);
}
