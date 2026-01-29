/*
 *  /d/Sparkle/guilds/new_merc/obj/wooden_spoon.c
 *
 *  A wooden spoon. One of numerous items that can be found in the kitchen of
 *  the Mercenary guild.
 *
 *  Created September 2009, by Cooper Sherry (Gorboth)
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
    set_name("spoon");
    set_short("wooden spoon");
    add_adj( ({ "wooden", "wood" }) );

    set_long("Spoons like this are a staple of any serious kitchen. It"
      + " looks well used, marked with many years of stirring custards,"
      + " cake mixes, and soups.\n");

    set_default_weapon(10, 2, W_CLUB, W_BLUDGEON, W_ANYH, 0);
    add_prop(OBJ_I_VOLUME, 25);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(10, 2) + random(20));
} /* create weapon */