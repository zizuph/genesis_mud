/*
 *  /d/Sparkle/area/orc_temple/wep/warrior_sword.c
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
    set_name("sword");
    add_name( ({ "longsword" }) );
    add_adj( ({ "notched", "long" }) );

    set_short("notched longsword");
    set_long("Many notches have been carved into the metal on the"
      + " side of the blade that extends from the hilt of this longsword."
      + " Whether the notches are for decoration or to commemorate"
      + " those who have fallen under its slice is a matter of grim"
      + " speculation.\n");

    set_default_weapon(WARRIOR_WEP_STAT,
                       WARRIOR_WEP_STAT,
                       W_SWORD,
                       W_SLASH | W_IMPALE,
                       W_ANYH,
                       0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(WARRIOR_WEP_STAT,
                                                   W_SWORD) + random(25));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WARRIOR_WEP_STAT,
                                         WARRIOR_WEP_STAT) + random(45));
} /* create_weapon */
