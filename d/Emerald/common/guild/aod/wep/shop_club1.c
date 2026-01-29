/*
 *  /d/Emerald/common/guild/aod/wep/shop_club1.c
 *
 *  A very pathetic club weapon sold in the AoD shop.
 *
 *  Sold at: /d/Emerald/common/guild/aod/rooms/aod_shop.c
 *
 *  Created December 2006, by Cooper Sherry (Gorboth)
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
    set_name("log");
    set_short("old rotten log");
    add_adj( ({ "old", "rotten" }) );
    set_long("This rotten old thing is probably better for sitting"
      + " on than anything. I suppose if you were an ogre and really"
      + " lacking for options it would do in a pinch, but you'd"
      + " almost be better off with bare fists.\n");

    set_default_weapon(15, 15, W_CLUB, W_BLUDGEON, W_BOTH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(15, W_CLUB));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(15, 15));
} /* create_weapon */
