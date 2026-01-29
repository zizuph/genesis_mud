/*
 *  /d/Sparkle/area/orc_temple/wep/priest_staff.c
 *
 *  Staff for the shaman for the orc raid event to open the Merc Guild.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
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
    set_name("staff");
    add_name( ({ "club" }) );
    add_adj( ({ "twisted", "wood", "wooden" }) );

    set_short("twisted wooden staff");
    set_long("A few feathers have been tied to the top of this staff"
      + " with twine. Though simplistic, it has a look of the arcane"
      + " about it.\n");

    set_default_weapon(WARRIOR_WEP_STAT,
                       WARRIOR_WEP_STAT, W_CLUB, W_BLUDGEON, W_BOTH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(WARRIOR_WEP_STAT,
                                                   W_CLUB) + random(25));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WARRIOR_WEP_STAT,
                                         WARRIOR_WEP_STAT) + random(45));
} /* create_weapon */