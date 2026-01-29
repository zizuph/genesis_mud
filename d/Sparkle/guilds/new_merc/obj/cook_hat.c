/*
 *  /d/Sparkle/guilds/new_merc/obj/cook_hat.c
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
    set_name("hat");
    add_adj( ({ "cook", "cooking", "cooks", "cook's" }) );

    set_short("cooking hat");
    set_long("Here we have the standard cooking headgear - tall, white,"
      + " cylindrical with a little puff on the top. Wear this thing and"
      + " you'll be ready for action in any kitchen!\n");

    set_default_armour(1,A_HEAD,({0,0,0}),0);

    /* We'll make it slightly more valuable than default for this AC
     * since it is a speciality item.
     */
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(10)+random(100)-30);

    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(1, A_HEAD) + random(5));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 2);
} /* create_armour */