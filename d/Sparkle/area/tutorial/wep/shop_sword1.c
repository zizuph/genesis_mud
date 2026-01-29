/*
 *  /d/Sparkle/area/tutorial/wep/shop_sword1.c
 *
 *  This is the lower-level sword sold in the Weapons Shop
 *  for the Genesis Tutorial.
 *
 *  Sold at: /d/Sparkle/area/tutorial/town/weapon_shop.c
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 *
 *  Updated June 2015 by Cherek
 *  To make the tutorial easier for newbies this weapon is now magical
 *  in order to make it lighter than what is otherwise allowed. 
 *
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
    set_name("shortsword");
    add_adj( ({ "iron", "short" }) );
    add_name( ({ "sword", "short-sword" }) );

    set_short("iron shortsword");
    set_long("This is a basic sword weapon which will do"
      + " slashing damage to anyone you fight. You can"
      + " <wield> it to equip the weapon, or <unwield> it if you no"
      + " longer wish to have it equipped.\n");

    set_default_weapon(9, 9, W_SWORD, W_SLASH, W_ANYH, 0);
	add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
	add_prop(MAGIC_AM_MAGIC, ({0, "enchantment"}));
	add_prop(MAGIC_AM_ID_INFO, ({"To ease the struggle of new players"
	                           + "Lars has made this weapon extra light.\n", 1}));
    add_prop(OBJ_I_WEIGHT, (F_WEIGHT_DEFAULT_WEAPON(9, W_SWORD) / 3));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(9, 9));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
} /* create_weapon */
