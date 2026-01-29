/*
 *  /d/Sparkle/guilds/new_merc/event/crude_sword.c
 *
 *  Low-level weapon for the orc raid event to open the Merc Guild.
 *
 *  Created August 2009, by Cooper Sherry (Gorboth)
 */

#pragma strict_types
inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

public void
create_weapon()
{
    set_name("sword");
    add_name( ({ "blade", "short-blade" }) );
    add_adj( ({ "crude", "iron", "short" }) );

    set_short("crude short-blade");
    set_long("This is far from what could be considered quality weapon-"
      + "craft. A piece of iron has been hammered into a very crude"
      + " blade to service as a sword.\n");
    set_default_weapon(20, 15, W_SWORD, W_SLASH | W_IMPALE, W_ANYH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(17, W_SWORD) + random(100));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20,15) + random(45));
} /* create_weapon */