/*
 *  /d/Sparkle/area/orc_temple/wep/warrior_mace.c
 *
 *  Mid-level weapon for the warriors in training in the orc temple
 *  dungeons in Sparkle.
 *
 *  Created October 2010, by Cooper Sherry (Gorboth)
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
    set_name("club");
    add_name( ({ "hammer" }) );
    add_adj( ({ "heavy", "beating", }) );

    set_short("heavy beating hammer");
    set_long("This weapon is very ungainly, but certainly means"
      + " business for any poor soul who finds themselves on the"
      + " receiving end of its heavy square hammer head. It is"
      + " a great deal heavier and deadlier than the typical crude"
      + " clubs orcs tend to use.\n");

    set_default_weapon(WARRIOR_WEP_STAT,
                       WARRIOR_WEP_STAT,
                       W_CLUB,
                       W_BLUDGEON,
                       W_ANYH,
                       0);

    add_prop(OBJ_I_WEIGHT,
        F_WEIGHT_DEFAULT_WEAPON(WARRIOR_WEP_STAT, W_CLUB) + random(100));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WARRIOR_WEP_STAT,
                                         WARRIOR_WEP_STAT) + random(45));
} /* create_weapon */
