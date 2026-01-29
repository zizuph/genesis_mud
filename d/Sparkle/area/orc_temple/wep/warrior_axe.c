/*
 *  /d/Sparkle/area/orc_temple/wep/warrior_axe.c
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
    set_name("axe");
    add_name( ({ "cleaver" }) );
    add_adj( ({ "large", "deadly", }) );

    set_short("large deadly cleaver");
    set_long("This is a most unlovely weapon. A large and flat wedge"
      + " of sharpened iron has been fixed to a hefty shaft with"
      + " tar and gutstring. It looks like it could hack through a"
      + " lot of meat with a single stroke.\n");

    set_default_weapon(WARRIOR_WEP_STAT,
                       WARRIOR_WEP_STAT,
                       W_AXE,
                       W_SLASH,
                       W_ANYH,
                       0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(WARRIOR_WEP_STAT,
                                                   W_AXE) + random(20));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WARRIOR_WEP_STAT,
                                         WARRIOR_WEP_STAT) + random(45));
} /* create_weapon */
