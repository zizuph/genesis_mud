/* 
 *  /d/Emerald/telberin/obj/wep/dagger.c
 *
 *  This weapon is sold by the Arms Dealer in Telberin.
 *
 *  Copyright (c) August 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>


/* prototypes *
public void        create_weapon();


/*
 * Function name:        create_weapon
 * Description  :        set up the weapon
 */
public void
create_weapon()
{
    set_name("dagger");
    add_adj( ({ "long-bladed", "bladed" }) );

    set_short("long-bladed dagger");
    set_long("The blade of this dagger is only slightly shorter"
      + " than a standard issue shortsword. This has been created"
      + " by the smiths of Telberin, and looks like it could"
      + " create a nasty wound.\n");

    set_default_weapon(16, 17, W_KNIFE, W_SLASH|W_IMPALE, W_ANYH, 0);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(16,17)+random(80)-20);
    add_prop(OBJ_I_WEIGHT, 3200);
} /* create_weapon */

