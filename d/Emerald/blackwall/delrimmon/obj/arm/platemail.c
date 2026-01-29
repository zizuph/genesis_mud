/*
 *  /d/Emerald/blackwall/delrimmon/obj/arm/platemail.c
 *
 *  This platemail is intended to serve as an alternative to the
 *  midnight version that is so sought after in the case that a
 *  clone_unique roll does not bring forth the good version.
 *
 *  Created November 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "std/armour";
inherit "/lib/keep";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

/* prototypes */
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
    set_name("platemail");
    add_name( ({ "plate", "mail" }) );
    add_adj( ({ "thick", "rugged", "plate" }) );

    set_short("thick rugged platemail");
    set_long("This huge set of armour has been built to fit the"
      + " largest and most formidable of warriors. A large chestplate"
      + " is connected to leg and arm pieces by finely-woven strips"
      + " of chainmail so that there are no gaps in the protection"
      + " it offers.\n");

    set_ac(40);
    set_am( ({-2,-1,3}) );
    set_at(A_TORSO|A_L_ARM|A_R_ARM|A_LEGS);
    set_wf(this_object());

    add_prop(OBJ_I_WEIGHT, 26000); /* pretty heavy */
    add_prop(OBJ_I_VOLUME, 3000);  /* not to mention massive */
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(40)
                        + random(1000) + 500);

    add_prop(OBJ_S_WIZINFO,
        "The platemail worn by the orc captain at Del Rimmon:\n"
      + "    /d/Emerald/blackwall/delrimmon/npc/captain.c\n"
      + "This is the non-unique option that is cloned in the case"
      + " that the roll to clone_unique does not produce the midnight"
      + " black platemail.\n");
} /* create_armour */


/*
 * Function name:        wear
 * Description  :        only allow players with > 100
 *                       strength to wear this armour.
 * Arguments    :        object obj - this_object
 * Returns      :        0 - allow to wear
 *                       string - too weak
 */
public mixed
wear(object obj)
{
    object  tp = environment(this_object());

    if (!living(tp))
    {
        return 0;
    }

    if (tp->query_stat(0) < 100)
    {
        tell_room(environment(tp),
            QCTNAME(tp) + " strains with all of " + tp->query_possessive()
          + " might, pulling the " + short() + " on over "
          + tp->query_possessive() + " body. "
          + capitalize(tp->query_pronoun()) + " nearly collapses under"
          + " its weight, and a sheepish look comes over "
          + tp->query_possessive() + " face as " + tp->query_pronoun()
          + " comically stumbles around in an attempt to move with the"
          + " armour on. Trying not to look overly humiliated, "
          + QTNAME(tp) + " pulls the " + short() + " off.\n", tp);
        return "You strain with all your might, and pull the " + short()
          + " on over your body. You nearly collapse under its weight,"
          + " and as you try to move around, you realize that you are"
          + " simply not strong enough to wear this armour. You slip"
          + " back out of the " + short() + ".\n";
    }

    tp->catch_msg("Gritting your teeth, you hoist the " + short()
      + " on over your body and secure the various pieces to your"
      + " arms and legs. Once worn, it isn't quite as heavy feeling"
      + " as when you were carrying it.\n");
    tell_room(environment(tp), QCTNAME(tp) + " grunts as "
      + tp->query_pronoun() + " hoists the " + short() + " on over "
      + tp->query_possessive() + " body.\n", tp);

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

public string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + query_keep_recover();
}

public void
init_recover(string arg)
{
    init_arm_recover(arg);
    init_keep_recover(arg);
}
