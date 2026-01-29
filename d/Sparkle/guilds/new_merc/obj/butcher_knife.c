/*
 *  /d/Sparkle/guilds/new_merc/obj/butcher_knife.c
 *
 *  A butcher knife. One of numerous items that can be found in the kitchen of
 *  the Mercenary guild.
 *
 *  The pen on this weapon is pretty high, but the hit sucks. I figure
 *  it is fun to put at least one decent item in here since it isn't
 *  easy to elude the cook.
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
    set_name("knife");
    set_short("butcher knife");
    add_adj( ({ "butcher" }) );

    set_long("Yikes! A butcher knife like this is the worst nightmare"
      + " of clumsy fingers, blind-mice tails, and ... well ... anything"
      + " you might care to swing it at. A very heavy squared metal"
      + " blade has been sharpened with a razor's edge for"
      + " effective chopping.\n");

    set_default_weapon(10, 40, W_AXE, W_SLASH, W_ANYH, 0);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(10, 40) + random(100));
} /* create weapon */