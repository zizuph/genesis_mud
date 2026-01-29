/*
 *  /d/Emerald/common/guild/aod/arm/ogre_cloak.c
 *
 *  This is a cloak that ogres can buy in their shop. Why would Ogres
 *  want to wear a cloak? Good question, but at least this gives them
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
    set_name("cloak");
    add_adj( ({ "elephant", "skin", "elephant-skin" }) );

    set_short("elephant-skin cloak");
    set_long("It looks as if someone has skinned an entire elephant and"
      + " made the massive hide into something like a cloak. Whoever did"
      + " it had no real skill, though, so it looks more like a deflated"
      + " elephant balloon than any sort of real clothing.\n");

    add_prop(OBJ_M_NO_SELL,
        "This would only be worth something to an Ogre. You can't sell"
      + " it here!\n");

    set_at(A_ROBE);
    set_ac(2);
    set_af(this_object());

    /* This armour is wearable by ogres, and only ogres. It is    */
    /* also the _only_ type of armour ogres may wear.             */
    add_prop(AOD_WEAR_PROP, 1);

    add_prop(OBJ_I_WEIGHT, 1000);

    /* calculate volume from weight */
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);

    add_prop(OBJ_I_VALUE, 3000);

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
        return 0;
    }

    return "Wear it? You'd be more likely to pitch it up as a tent!\n";

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

    return 0;
} /* remove */
