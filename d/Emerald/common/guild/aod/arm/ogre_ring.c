/*
 *  /d/Emerald/common/guild/aod/arm/ogre_ring.c
 *
 *  This is a ring that ogres can buy in their shop. Why would Ogres want
 *  to wear a ring? Hmmm ... good question, but at least this gives them
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
    set_name("ring");
    add_name("skull");
    add_adj( ({ "hollow", }) );

    set_short("hollow skull");
    set_long("This skull has had a large hole poked through the top,"
      + " making it something like an Ogre fashion accessory. It looks"
      + " like it could be worn on a VERY large finger.\n");

    add_prop(OBJ_M_NO_SELL,
        "This would only be worth something to an Ogre. You can't sell"
      + " it here!\n");

    set_at(A_ANY_FINGER);
    set_ac(1);
    set_af(this_object());

    /* This armour is wearable by ogres, and only ogres. It is    */
    /* also the _only_ type of armour ogres may wear.             */
    add_prop(AOD_WEAR_PROP, 1);

    add_prop(OBJ_I_WEIGHT, 100);

    /* calculate volume from weight */
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);

    add_prop(OBJ_I_VALUE, 2000);

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
        write("You stick your massive finger through the hole in the"
          + " top of the skull. So pretty!\n");
        tell_room(environment(tp), QCTNAME(tp) + " shoves the"
          + " hollow skull onto one of " + tp->query_possessive()
          + " massive fingers.\n", tp);
        return 0;
    }

    return "Your finger is about eighteen sizes too small.\n";

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

    write("You pull the hollow skull off your finger.\n");
    tell_room(environment(tp), QCTNAME(tp) + " pulls the hollow skull"
      + " off of " + tp->query_possessive() + " finger.\n", tp);
    return 0;
} /* remove */
