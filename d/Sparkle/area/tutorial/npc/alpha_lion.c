/*
 *  /d/Sparkle/area/tutorial/npc/alpha_lion.c
 *
 *  This is the toughest monster in the Tutorial Area. He is
 *  intended to force players to team up against him.
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 */

#pragma strict_types
#include "../defs.h"

inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/act/domove";
inherit "/std/combat/unarmed";

#include <filter_funs.h>        /* for FILTER_LIVE              */
#include <ss_types.h>           /* for SS_DEFENCE, etc          */
#include <stdproperties.h>      /* for NPC_I_NO_LOOKS, etc      */
#include <wa_types.h>           /* for W_IMPALE, etc            */

/* Prototypes */
public void     create_creature();


/*
 * Function name:       create_creature
 * Description  :       set up the animal
 */
public void
create_creature()
{
    set_name( ({ "animal" }) );
    add_name( ({ "creature", "beast", "_tutorial_animal", 
                 "lion" }) );
    add_adj( ({ "gigantic", "mountain" }) );

    set_short("gigantic mountain lion");
    set_long("This terrible beast is among the most ferocious"
      + " monsters you have ever laid eyes upon! Taut rippling"
      + " muscles move powerfully beneath an amazing grey coat of"
      + " fur. Teeth over two inches long gleam from the lethal"
      + " jaws of this creature. Surely, this is no fight to attempt"
      + " by oneself.\n");

    set_skill(SS_AWARENESS, 15);
    set_alignment(0);

    add_prop(CONT_I_WEIGHT, 50000);      /* 100 lbs? */
    add_prop(CONT_I_HEIGHT, 100);        /* 50 inches? */
    add_prop(CONT_I_VOLUME, 80330);     /* 5200 cubic inches? */

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is not able to carry anything.\n");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1); /* chasing npcs is not fun! */

    default_config_creature(25);

    set_skill(SS_DEFENCE, 50);
    set_skill(SS_UNARM_COMBAT, 50);

    set_attack_unarmed(0,  20, 20, W_IMPALE,  40, "powerful teeth");
    set_attack_unarmed(1,  20, 20, W_SLASH,   30, "huge claws");

    set_hitloc_unarmed(0, ({ 6,  6,  2 }),  40, "back");
    set_hitloc_unarmed(1, ({ 7,  2,  7 }),  20, "left side");
    set_hitloc_unarmed(2, ({ 7,  2,  7 }),  20, "right side");
    set_hitloc_unarmed(3, ({ 10, 5,  2 }),  10, "head");
    set_hitloc_unarmed(4, ({ 5,  5, 10 }),  10, "paws");

    add_leftover(OBJ_DIR + "claw", "claw", 1, 0, 0, 1);
    add_leftover(OBJ_DIR + "teeth", "tooth", random(5), 0, 0, 0);
    add_leftover(OBJ_DIR + "skull", "skull", 1, 0, 0, 1);

    set_act_time(20);
    add_act("emote stalks back and forth, peering at you.");
    add_act("emote leaps up on some rocks and sits down.");
    add_act("emote lets out a low rumbling growl.");
    add_act("emote crouches suddenly.");
    add_act("emote licks its paws.");
    add_act("emote sits perfectly still, but for its swishing tail.");
    add_act("emote gazes at you, hungrily.");
} /* create_creature */


/*
 * Function name:        arm_me
 * Description  :        give the animal its pelt
 */
public void
arm_me()
{
    //object  pelt = clone_object(OBJ_DIR + "pelt");
    object  pelt = clone_object(ARM_DIR + "gigantic_pelt");

    //pelt->config_pelt("gigantic");
    pelt->move(this_object());
} /* arm_me */


/*
 * Function name:   hit_me
 * Description:     Called to make damage on this object. The actually
 *                  made damage is returned and will be used to change
 *                  the score of the aggressor.
 * Arguments:       wcpen         - The wc-penetration
 *                  dt            - damagetype, use MAGIC_DT if ac will not
 *                                  help against this attack.
 *                  attacker      - Object hurting us
 *                  attack_id     - Special id saying what attack hit us. If 
 *                                  you have made a special attack, let the 
 *                                  id be -1
 *                  target_hitloc - Optional argument specifying a hitloc
 *                                  to damage.  If not specified or an
 *                                  invalid hitloc is given, a random
 *                                  one will be used.
 * Returns:         The hitresult as given by the external combat object
 *
 * I'm redefining this so that the tutorial is extremely easy for the new
 * players in terms of grinding. I'm having each hit on the npcs deal
 * 2x damage.
 */
public mixed
hit_me(int wc_pen, int dt, object attacker, int attack_id, int target_hitloc =
-1)
{
    return ::hit_me(wc_pen * 2, dt, attacker, attack_id, target_hitloc);
} /* hit_me */
