/*
 *  /d/Sparkle/guilds/new_merc/obj/broom.c
 *
 *  A broom ... for sweeping! (Kept in the broom closet of the Merc
 *  Guild, but possible for sale in town too.)
 *
 *  Created June 2009, by Cooper Sherry (Gorboth)
 *
 *  Revised by Shanoga, 2021 Apr 25:
 *   Removed value from broom since it is limitless and characters
 *    could repeatedly sell it for unlimited money.
 */
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

/* prototypes */
public void        create_weapon();


/*
 * Function name:        create_weapon
 * Description  :        set up the broom
 */
public void
create_weapon()
{
    set_name("broom");
    set_short("sturdy broom");
    add_adj( ({ "sturdy", "wooden" }) );

    set_long("Ahh ... a sturdy wooden broom. This is just the sort of"
      + " thing one might use to tidy up around your typical living"
      + " quarters.\n");

    set_default_weapon(15, 10, W_POLEARM, W_BLUDGEON, W_BOTH, 0);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_WEIGHT, 2500);
    // add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(15, 10) + 150 - random(50));
    add_prop(OBJ_I_VALUE,0);
} /* create weapon */