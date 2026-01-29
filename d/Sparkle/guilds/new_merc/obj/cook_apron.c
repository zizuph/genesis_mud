/*
 *  /d/Sparkle/guilds/new_merc/obj/cook_apron.c
 *
 *  The cook in the Mercenary Guild wears this thing.
 *
 *  Created September 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types;
inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

/* Prototypes */
public void        create_armour();


/*
 * Function name:        create_armour
 * Description  :        set up the armour
 */
public void
create_armour()
{
    set_name("apron");
    add_adj( ({ "frilly", "white", "cooking", "cooks", "cook's" }) );

    set_short("frilly white cooking apron");
    set_long("Wearing armour of this sort might not protect you from"
      + " your enemy's sword, but by the Gods, you shall fear no"
      + " tomato!\n");

    set_default_armour(1, A_ROBE, ({ 0, 0, 0 }), 0);

    /* We'll make it slightly more valuable than default for this AC
     * since it is a speciality item.
     */
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(5) + random(100) - 30);

    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(1, A_ROBE) + random(5));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 6);
} /* create_armour */