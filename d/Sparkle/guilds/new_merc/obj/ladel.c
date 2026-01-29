/*
 *  /d/Sparkle/guilds/new_merc/obj/ladel.c
 *
 *  A ladel. One of numerous items that can be found in the kitchen of
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
    set_name("ladel");
    set_short("soup ladel");
    add_adj( ({ "soup" }) );

    set_long("This type of ladel can come in handy when the occasion calls"
      + " for the scoupage of soup (or any other liquid from a"
      + " container.)\n");

    set_default_weapon(10, 2, W_CLUB, W_BLUDGEON, W_ANYH, 0);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, 75);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(10, 2) + random(20));
} /* create weapon */