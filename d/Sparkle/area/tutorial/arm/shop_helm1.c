/*
 *  /d/Sparkle/area/tutorial/arm/shop_helm1.c
 *
 *  This is the upper-level chest armour sold in the Armour Shop
 *  for the Genesis Tutorial.
 *
 *  Sold at: /d/Sparkle/area/tutorial/town/armour_shop.c
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 *
 *  Updated June 2015 by Cherek
 *  To make the tutorial easier for newbies this armour is now magical
 *  in order to make it lighter than what is otherwise allowed. 
 *
 */
#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>


/*
 * Function name:        create_armour
 * Description  :        set up the armour
 */
public void
create_armour() 
{
    set_name("helm");
    add_adj( ({ "leather" }) );
    add_name( ({ "helmet", "armour" }) );

    set_short("leather helm");
    set_long("This armour can be worn on the head to protect from"
      + " enemy attacks. Use the command <wear> to put it on, and"
      + " <remove> to take it off of your body.\n");

    set_default_armour(4, A_HEAD, ({ 0, 1, -1}), 0);
	add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
	add_prop(MAGIC_AM_MAGIC, ({0, "enchantment"}));
	add_prop(MAGIC_AM_ID_INFO, ({"To ease the struggle of new players"
	                           + "Lars has made this armour extra light.\n", 1}));
    add_prop(OBJ_I_WEIGHT, (F_WEIGHT_DEFAULT_ARMOUR(4, A_HEAD) / 4));
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(4) + random(12));
} /* create_armour */
