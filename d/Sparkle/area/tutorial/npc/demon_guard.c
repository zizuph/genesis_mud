/*
 *  /d/Sparkle/area/tutorial/npc/demon_guard.c
 *
 *  This is the file for the guards in Krolocks Castle in the
 *  Tutorial Area.
 *
 *  Created September 2005, by Cooper Sherry (Gondor)
 */

#pragma strict_types
#include "../defs.h"

inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/domove";

#include <filter_funs.h>        /* for FILTER_LIVE              */
#include <macros.h>             /* for VBFC_ME                  */
#include <ss_types.h>           /* for SS_DEFENCE, etc          */
#include <stdproperties.h>      /* for NPC_I_NO_LOOKS, etc      */
#include <wa_types.h>           /* for W_IMPALE, etc            */

/* Definitions */
#define  DEMON_SKILL        10  /* combat skill levels          */

/* Prototypes */
public void     create_monster();
public void     arm_me();


/*
 * Function name:       create_monster
 * Description  :       set up the guard
 */
public void
create_monster()
{
    set_name( ({ "demon" }) );
    add_name( ({ "guard", "_tutorial_demon_guard", "soldier" }) );
    add_adj( ({ "black", "demonic" }) );
    set_race_name("demon");

    set_short("demonic guard");
    set_long("Though shaped much like a man, this guard is clearly a"
      + " demon of some kind. His skin is pitch black and his eyes glow"
      + " with a sinister red hue.\n");

    set_skill(SS_WEP_SWORD, DEMON_SKILL);
    set_skill(SS_WEP_AXE,   DEMON_SKILL);
    set_skill(SS_WEP_KNIFE, DEMON_SKILL);
    set_skill(SS_WEP_CLUB,  DEMON_SKILL);

    set_skill(SS_AWARENESS, 15);
    set_skill(SS_DEFENCE, DEMON_SKILL);

    default_config_npc(13);
    set_alignment(0);

    add_prop(CONT_I_WEIGHT, 81600);      /* 180 lbs */
    /* 15" tall by 10" long by 8" wide */
    add_prop(CONT_I_HEIGHT, 125);        /* 70 inches */
    add_prop(CONT_I_VOLUME, 140000);     /* 8000 cubic inches */

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is not able to carry anything.\n");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1); /* chasing npcs is not fun! */

    set_act_time(20);
    add_act("emote emits a long, wraith-like hiss.");
    add_act("emote peers at you with his souless demon eyes.");
    add_act("emote grips his weapon and looks at you with a grin.");
    add_act("emote bends low, and scratches some demonic figures in the"
      + " floor, muttering words you do not understand.");
    add_act("emote peers at the sky and grins evilly.");
    add_act("emote spits some blood on the ground, near your feet.");
    add_act("emote licks his weapon with his tongue.");
} /* create_monster */


/*
 * Function name:        arm_me
 * Description  :        give the guard his armament
 */
public void
arm_me()
{
    object    armour = clone_object(ARM_DIR + "demon_"
                + one_of_list( ({ "helm", "mail", "greaves", "bracers",
                                  "shield" }) ) );
    object    weapon = clone_object(WEP_DIR + "demon_"
                + one_of_list( ({ "sword", "axe", "knife", "club" }) ));

    weapon->move(this_object());
    armour->move(this_object());

    command("wear all");
    command("wield all");
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
hit_me(int wc_pen, int dt, object attacker, int attack_id, int target_hitloc = -1)
{
    return ::hit_me(wc_pen * 2, dt, attacker, attack_id, target_hitloc);
} /* hit_me */