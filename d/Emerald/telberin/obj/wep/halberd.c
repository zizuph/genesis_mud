/*
 *  /d/Emerald/telberin/obj/wep/halberd.c
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
    set_name("halberd");
    set_short("gleaming elvish halberd");
    add_adj( ({ "gleaming", "elvish" }) );
    set_long("This finely-constructed weapon looks deadly indeed. A long"
      + " shaft is wrapped with leather strips along the grip which"
      + " counterbalances the long and lethal blad which is affixed to"
      + " its front. This is a product of the fine craftmanship of"
      + " the Telberin smithies.\n");

    set_default_weapon(25,39, W_POLEARM, W_SLASH | W_IMPALE, W_BOTH, 0);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(32, W_POLEARM)
      +random(100));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(25, 39) + random(45));
} /* create_weapon */
