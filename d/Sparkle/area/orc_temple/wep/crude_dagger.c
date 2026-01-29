/*
 *  /d/Sparkle/area/orc_temple/wep/crude_dagger.c
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
    /* NOTE: We intentionally do not add the name "dagger" to this
     *       weapon to avoid messy conflicts with the nullstone
     *       dagger which is part of the quests here.
     */

    set_name("knife");
    add_adj( ({ "dirty", "little", }) );

    set_short("dirty little knife");
    set_long("This weapon looks positively unkind. Not only is it"
      + " a deadly-sharp iron blade inserted into a crude wooden"
      + " handle, but it is crusted along its edges with dried"
      + " blood.\n");

    set_default_weapon(RUNT_WEP_STAT,
                       RUNT_WEP_STAT,
                       W_KNIFE,
                       W_SLASH | W_IMPALE,
                       W_ANYH,
                       0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(RUNT_WEP_STAT,
                                                   W_KNIFE) + random(5));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(RUNT_WEP_STAT,
                                         RUNT_WEP_STAT) + random(45));
} /* create_weapon */
