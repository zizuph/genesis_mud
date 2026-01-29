/*
 *  /d/Sparkle/area/orc_temple/wep/crude_spear.c
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
    set_name("polearm");
    add_name( ({ "spear" }) );
    add_adj( ({ "filthy" }) );

    set_short("filthy spear");
    set_long("No one has bothered to care for this weapon much at"
      + " all. Dried filth of unknown origin covers the flint-chipped"
      + " stone tip and runs in streaks down the long shaft of the"
      + " weapon. Nonetheless, it looks quite sharp and dangerous.\n");

    set_default_weapon(RUNT_WEP_STAT,
                       RUNT_WEP_STAT,
                       W_POLEARM,
                       W_SLASH | W_IMPALE,
                       W_BOTH,
                       0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(RUNT_WEP_STAT,
                                                   W_POLEARM) + random(15));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(RUNT_WEP_STAT,
                                         RUNT_WEP_STAT) + random(45));
} /* create_weapon */
