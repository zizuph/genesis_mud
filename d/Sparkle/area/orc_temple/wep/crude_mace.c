/*
 *  /d/Sparkle/area/orc_temple/wep/crude_mace.c
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
    set_name("mace");
    add_name( ({ "club" }) );
    add_adj( ({ "ugly", "stone", }) );

    set_short("ugly stone mace");
    set_long("This weapon is an example of extremely primitive weapon-"
      + "craft. A large roundish stone has been fastened with gutstring"
      + " and tar to a mid-length shaft to create a very crude yet"
      + " reliable club.\n");

    set_default_weapon(RUNT_WEP_STAT,
                       RUNT_WEP_STAT,
                       W_CLUB,
                       W_BLUDGEON,
                       W_ANYH,
                       0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(RUNT_WEP_STAT,
                                                   W_CLUB) + random(30));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(RUNT_WEP_STAT,
                                         RUNT_WEP_STAT) + random(45));
} /* create_weapon */
