/*
 *  /d/Sparkle/guilds/new_merc/event/colossus_axe.c
 *
 *  Elite weapon for the for the orc raid event to open the Merc Guild.
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
    add_name( ({ "gore-axe" }) );
    add_adj( ({ "gore", "monstrous" }) );

    set_short("monstrous gore-axe");
    set_long("This weapon is utterly terrifying! Its twin blades, each"
      + " nearly as massive as a barrel lid, are scalloped with razor-"
      + "sharp hooks along the edge. Beyond a tool of death, to use"
      + " it is to wield a positive nightmare in your hands!\n");

    set_default_weapon(60, 60, W_AXE, W_SLASH, W_BOTH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(50, W_AXE) + random(100));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(60, 60) + random(45));

    add_prop(MAGIC_AM_MAGIC, ({ 100, "enchantment" }) );
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);

    add_prop(MAGIC_AM_ID_INFO, ({ 
        "The blades of this weapon have been magically enchanted"
      + " with the powers of the goblin God Kalach. It does"
      + " hideous amounts of damage, and is lighter than it would"
      + " normally be.\n", 30 }) );

    add_prop(OBJ_S_WIZINFO,
        "Special note: This weapon is only available from a special event"
      + " in which Sparkle is beseiged by attacking goblins. It is a very"
      + " powerful two-handed weapon, and therefore not to be given out"
      + " under normal circumstances. But for such a rare event as this,"
      + " we need a few fun things!\n");
} /* create_weapon */
