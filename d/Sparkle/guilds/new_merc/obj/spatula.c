/*
 *  /d/Sparkle/guilds/new_merc/obj/spatula.c
 *
 *  A spatula. One of numerous items that can be found in the kitchen of
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
    set_name("spatula");
    set_short("spatula");
    add_adj( ({ "sturdy" }) );

    set_long("This spatula consists of a flat wooden square with supple"
      + " leather extensions on either end mounted on a wooden handle."
      + " It is useful for scraping the last bits of any thick"
      + " substance from a stubborn container.\n");

    set_default_weapon(10, 2, W_CLUB, W_BLUDGEON, W_ANYH, 0);
    add_prop(OBJ_I_VOLUME, 25);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(10, 2) + random(20));
} /* create weapon */