/*
 *  /d/Sparkle/area/orc_temple/wep/crude_axe.c
 *
 *  Low-level weapon for the guards in training in the orc temple
 *  dungeons in Sparkle.
 *
 *  Created August 2009, by Cooper Sherry (Gorboth)
 */

#pragma strict_types
inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "../defs.h"

public void
create_weapon()
{
    set_name("axe");
    add_name( ({ "hatchet" }) );
    add_adj( ({ "crude", "stone", }) );

    set_short("crude stone hatchet");
    set_long("There is nothing remarkable about this weapon other than"
      +  " the fact that it hasn't fallen apart yet. A flint-chipped"
      + " wedge of stone has been crudely fastened with gutstring and"
      + " tar to a wooden handle. It does look dangerous, though.\n");

    set_default_weapon(RUNT_WEP_STAT,
                       RUNT_WEP_STAT,
                       W_AXE,
                       W_SLASH | W_IMPALE,
                       W_ANYH,
                       0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(RUNT_WEP_STAT,
                                                   W_AXE) + random(20));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(RUNT_WEP_STAT,
                                         RUNT_WEP_STAT) + random(45));
} /* create_weapon */
