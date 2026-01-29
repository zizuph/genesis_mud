/*
 *  /d/Sparkle/area/orc_temple/arm/crude_shield.c
 *
 *  This is a low-level shield used by the goblins beneath the orc
 *  temple in Sparkle
 *
 *  Copyright (c) August 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types;
inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_armour()
{
    set_name("shield");
    set_adj( ({ "rough", "metal" }) );

    set_short("rough metal shield");
    set_long("Some dark type of metal has been beaten with very poor"
      + " craftsmanship into a roughly square plate and then fitted"
      + " with an iron strap through which one might slide their"
      + " forearm. It isn't pretty, but it would protect someone"
      + " from a basic attack.\n");
    set_default_armour(12, A_SHIELD, ({ 3, -2, -1 }), 0);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(12) + random(50));
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(12, A_SHIELD) + random(20));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 7);
}
