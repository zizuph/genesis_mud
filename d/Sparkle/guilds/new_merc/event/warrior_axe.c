/*
 *  /d/Sparkle/guilds/new_merc/event/warrior_axe.c
 *
 *  Warrior Axe for the for the orc raid event to open the Merc Guild.
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
    set_name("axe");
    add_name( ({ "waraxe" }) );
    add_adj( ({ "powerful", "war" }) );

    set_short("powerful waraxe");
    set_long("Though by no means a beautifully made weapon, this is"
      + " clearly a powerful tool of death.\n");
    set_default_weapon(40, 40, W_AXE, W_SLASH, W_ANYH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(40, W_AXE) + random(100));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40,40) + random(45));
    add_prop(OBJ_S_WIZINFO,
        "Special note: This weapon is only available from a special event"
      + " in which Sparkle is beseiged by attacking goblins. It is a very"
      + " powerful one-handed weapon, and therefore not to be given out"
      + " under normal circumstances. But for such a rare event as this,"
      + " we need a few fun things!\n");
} /* create_weapon */
