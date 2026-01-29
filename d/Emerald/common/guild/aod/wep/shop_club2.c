/*
 *  /d/Emerald/common/guild/aod/wep/shop_club1.c
 *
 *  A fairly pathetic club weapon sold in the AoD shop.
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
    set_name("pipe");
    set_short("dented stove pipe");
    add_adj( ({ "dented", "stove" }) );
    set_long("This stove pipe still bears the clasps that once held"
      + " it to a wall somewhere. Evidently someone (an ogre, likely)"
      + " decided it would be better used as a smashing tool, and"
      + " claimed it for exactly that purpose!\n");

    set_default_weapon(20, 20, W_CLUB, W_BLUDGEON, W_BOTH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(20, W_CLUB));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20, 20));
} /* create_weapon */
