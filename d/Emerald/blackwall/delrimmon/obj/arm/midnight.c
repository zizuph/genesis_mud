/*
 *  /d/Emerald/blackwall/delrimmon/obj/arm/midnight.c
 *
 *  This platemail was created by the Darklings, who have
 *  created through magical means new alloys similar in
 *  strength to those of mithril, which does not exist in
 *  Emerald. This armour has been imbued with their powers,
 *  and radiates a small amount of darkness, though not enough
 *  to darken a room. The Darklings have bestowed these
 *  armours on their finest warriors, like the ones they
 *  have sent to captain expeditions to the Del Rimmon area
 *  to see what can be found in the deserted outposts of
 *  the Elves.
 *
 *  Copyright (c) September 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "std/armour.c";
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
    add_adj( ({"midnight", "black", "massive", "plate" }) );

    set_short("midnight black platemail");
    set_long("This massive set of platemail was obviously created"
      + " to be used by only the very strongest of warriors. It is"
      + " extremely thick and dense, weighing perhaps double what"
      + " the normal armour of this type might. A huge chestplate"
      + " is connected by finely interwoven mail to arm and leg"
      + " pieces, all of which are made of a supremely hard metal"
      + " which is almost certainly alloyed from mithril or"
      + " perhaps some even more exotic material. The surface of"
      + " the armour is black upon black, and radiates its"
      + " darkness outward, reflecting upon anything in its"
      + " close proximity.\n");

    set_ac(55);
    set_am( ({-2,-1,3}) );
    set_at(A_TORSO|A_L_ARM|A_R_ARM|A_LEGS);
    set_wf(this_object());


    add_prop(OBJ_I_WEIGHT, 30000); /* this sucker is heavy */
    add_prop(OBJ_I_VOLUME, 3000);  /* not to mention massive */
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(55)
                        + random(1000) + 500);
    add_prop(MAGIC_AM_MAGIC, ({ 75, "abjuration" }) );
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

    add_prop(MAGIC_AM_ID_INFO, ({
        "This armour is enhanced by dark magic!\n", 10,
        "It has been magically crafted by the Darklings"
      + " to be as strong as mithril - a metal which is not found"
      + " in Emerald.\n", 75, }) );

    add_prop(OBJ_S_WIZINFO,
        "The platemail worn by the orc captain at Del Rimmon:\n"
      + "    /d/Emerald/blackwall/delrimmon/npc/captain.c\n"
      + "Greater ac due to magical enchantment, offset by"
      + " extreme weight and volume. Cannot be worn but by"
      + " players with > 150 strength.\n");

} /* create_armour */


/*
 * Function name:        wear
 * Description  :        only allow players with > 149
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

    if (tp->query_stat(0) < 150)
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
      + " arms and legs. You strain slightly as you move around,"
      + " getting used to the immense weight that this armour has"
      + " added to your frame.\n");
    tell_room(environment(tp), QCTNAME(tp) + " grunts as "
      + tp->query_pronoun() + " hoists the " + short() + " on over "
      + tp->query_possessive() + " body. It appears as if the weight"
      + " of the armour is enough to tax even " + tp->query_possessive()
      + " mighty strength.\n", tp);

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
