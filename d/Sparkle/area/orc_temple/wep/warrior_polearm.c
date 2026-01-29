/*
 *  /d/Sparkle/area/orc_temple/wep/warrior_polearm.c
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
    set_name("polearm");
    add_name( ({ "glaive" }) );
    add_adj( ({ "long", "black" }) );

    set_short("long black glaive");
    set_long("Everything from the long shaft to the wide sharpened blade"
      + " of this deadly weapon have been tinted a dingy black colour."
      + " The metal along the cutting end gleams with a pale polish.\n");

    set_default_weapon(WARRIOR_WEP_STAT,
                       WARRIOR_WEP_STAT,
                       W_POLEARM,
                       W_SLASH | W_IMPALE,
                       W_BOTH,
                       0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(WARRIOR_WEP_STAT,
                                                   W_POLEARM) + random(25));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WARRIOR_WEP_STAT,
                                         WARRIOR_WEP_STAT) + random(45));
} /* create_weapon */
