/*
 *  /d/Emerald/telberin/obj/wep/mace.c
 *
 *  This is a standard issue weapon for the Telberin Arms Shop
 *
 *  Copyright (c) August 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

/* prototypes */
public void        create_weapon();

/*
 * Function name:        create_weapon
 * Description  :        set up the weapon
 */
public void
create_weapon()
{
    set_name("mace");
    set_short("sturdy elvish mace");
    add_adj( ({ "sturdy", "elvish" }) );
    set_long("A flanged head along the top of this mace looks"
      + " as if it could deal out serious punishment in"
      + " combat. The smiths of Telberin have put great care"
      + " into its balance as well.\n");

    set_default_weapon(29,25, W_CLUB, W_BLUDGEON, W_ANYH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(29, W_CLUB)
      +random(100));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(29, 25) + random(45));
} /* create_weapon */
