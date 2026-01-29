/*
 *  /d/Sparkle/area/orc_temple/wep/warrior_dagger.c
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
    /* NOTE: We intentionally do not add the name "dagger" to this
     *       weapon to avoid messy conflicts with the nullstone
     *       dagger which is part of the quests here.
     */

    set_name("knife");
    add_name( ({ "carver", }) );
    add_adj( ({ "wicked-tipped", "wicked", "tipped", }) );

    set_short("wicked-tipped carver");
    set_long("The short and twisty blade of this knife-like weapon is"
      + " tipped with a needle point that looks like it would dearly"
      + " love to skewer the nearest eyeball. Terrifying!\n");

    set_default_weapon(WARRIOR_WEP_STAT,
                       WARRIOR_WEP_STAT,
                       W_KNIFE,
                       W_SLASH | W_IMPALE,
                       W_ANYH,
                       0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(WARRIOR_WEP_STAT,
                                                   W_KNIFE) + random(10));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WARRIOR_WEP_STAT,
                                         WARRIOR_WEP_STAT) + random(45));
} /* create_weapon */
