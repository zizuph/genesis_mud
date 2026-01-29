/*
 *  /d/Emerald/blackwall/delrimmon/obj/wep/dagger.c
 *
 *  This weapon is standard issue by the Army of Darkness.
 *
 *  Copyright (c) ?? 1996, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Genesis/imbuement/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

public void
create_weapon()
{
    set_name("dagger");
    add_name( ({"knife"}) );
    add_adj( ({ "black", "jagged-edged", "iron" }) );
    set_short("jagged-edged dagger");
    set_pshort("jagged-edged daggers");
    set_long(BSN("Thicker and longer than most knife blades, this weapon"
        + " is fashioned from what appears to be iron, blackened from"
        + " some foul staining agent. The metal of the blade is notched"
        + " and jagged, as if it were meant to function for sawing as"
        + " well as stabbing."));
    set_default_weapon(14, 18, W_KNIFE, W_SLASH | W_IMPALE, W_NONE, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(16, W_KNIFE) + random(20));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(14, 18) + random(12));
}