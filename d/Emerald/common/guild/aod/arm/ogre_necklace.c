/*
 *  /d/Emerald/common/guild/aod/arm/ogre_necklace.c
 *
 *  This is a necklace that ogres can buy in their shop. Why would Ogres
 *  want to wear a necklace? Good question, but at least this gives them
 *  the option.
 *
 *  Created May 2011, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>


/* Prototypes */
public void        create_armour();
public mixed       wear(object obj);
public mixed       remove(object obj);


/*
 * Function name:        create_armour
 * Description  :        set up the armour
 */
public void
create_armour()
{
    set_name("necklace");
    add_name("skeleton");
    add_adj( ({ "twisted", "elf" }) );

    set_short("twisted elf skeleton");
    set_long("Someone has tied the hands and feet of this skeleton"
      + " together, forming something like a necklace to be worn"
      + " around the neck of ... well, something really big.\n");

    add_prop(OBJ_M_NO_SELL,
        "This would only be worth something to an Ogre. You can't sell"
      + " it here!\n");

    set_at(A_NECK);
    set_ac(3);
    set_af(this_object());

    /* This armour is wearable by ogres, and only ogres. It is    */
    /* also the _only_ type of armour ogres may wear.             */
    add_prop(AOD_WEAR_PROP, 1);

    add_prop(OBJ_I_WEIGHT, 300);

    /* calculate volume from weight */
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);

    add_prop(OBJ_I_VALUE, 1500);

} /* create_armour */


/*
 * Function name:        wear
 * Description  :        only allow ogres to wear this massive armour
 * Arguments    :        object obj - this_object
 * Returns      :        0 -- allow to wear
 *                       1 -- not an ogre, fail
 */
public mixed
wear(object obj)
{
    object  tp = environment(this_object());

    if (!living(tp))
    {
        return 0;
    }

    if (tp->query_guild_name_occ() == GUILD_NAME)
    {
        write("You slip the skeleton over your head. It feels just"
          + " perfect around your neck! Ahhh ... fashion.\n");
        tell_room(environment(tp), QCTNAME(tp) + " slips the"
          + " twisted elf skeleton over " + tp->query_possessive()
          + " head to wear as a necklace.\n", tp);
        return 0;
    }

    return "Wear a skeleton? Only an ogre would do such a thing, or even"
      + " have the right neck-size to do it!\n";

    return 1;
} /* wear */


/*
 * Function name:        remove
 * Description  :        called when the player removes
 *                       the armour
 * Arguments    :        object obj - this_object()
 * Returns      :        0
 */
public mixed
remove(object obj)
{
    object  tp = this_object()->query_worn();

    if (!living(tp))
    {
        return 0;
    }

    write("You pull the twisted elf skeleton off over your head.\n");
    tell_room(environment(tp), QCTNAME(tp) + " pulls the twisted elf"
      + " skeleton off over " + tp->query_possessive() + " head.\n", tp);
    return 0;
} /* remove */
