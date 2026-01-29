/*
 *  /d/Sparkle/guilds/new_merc/event/goblin_giant.c
 *
 *  The toughest goblin attacker for the raid on Sparkle that will
 *  lead to the opening of the Free Mercenary Guild. This guy is meant
 *  to be a real nightmare. Only taken out by the toughest players or
 *  big teams.
 *
 *  Created August 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/monster";
inherit "/d/Emerald/lib/aid_npc";

#include <filepath.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>
#include "../merc_defs.h"

/* Prototypes */
public void        create_monster();
public void        arm_me();
public void        notify_death(object killer);

/* Global Variables */
public string      Goblin_Type = "colossus";


/*
 * Function name:        create_monster
 * Description  :        The constructor for the monster
 */
public void
create_monster()
{
    set_name("goblin");
    set_race_name("goblin");
    add_name( ({ "colossus", EVENT_GOBLIN, "giant" }) );
    add_adj( ({ "goblin", "colossal" }) );

    set_short("goblin colossus");
    set_long("By the Gods! This is perhaps the biggest goblin you have"
      + " ever laid eyes upon! Nearly the size of an Ogre, this hideous"
      + " creature towers over the area, peering balefully around.\n");

    set_stats( ({ 300 + (random(100)),
                  300 + (random(100)),
                  300 + (random(100)),
                  50 + (random(20)),
                  50 + (random(20)),
                  100 + (random(100)) }) );
                  
    set_skill(SS_WEP_AXE,      100);
    set_skill(SS_AWARENESS,    80);
    set_skill(SS_DEFENCE,      100);
    set_skill(SS_PARRY,        100);

    add_act("roar");
    add_act("emote booms: Who will challenge me?!");
    add_act("emote booms: Death to all who oppose Kalach!");
    add_act("emote booms: Destroy! Destroy!");

    add_cact("emote stomps, shaking the ground!");
    add_cact("emote slowly turns, fighting off the attack.");
    add_cact("shout ALL WILL DIE!!");

    /* We assist other goblins who get attacked. */
    set_give_aid(1);

    set_aggressive(1, 100);
} /* create_monster */


/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{
    object  arm;

    arm = clone_object(EVENT_DIR + "colossus_axe");
    arm->move(this_object());
    arm = clone_object(EVENT_DIR + "colossus_fullplate");
    arm->move(this_object());

    command("wear all");
    command("wield all");
} /* arm_me */


/*
 * Function name:        assist
 * Description  :        When assisting other goblins that get attacked,
 *                       we display what is happening.
 */
public void
assist()
{
    /* Too spammy otherwise */
    if (random(7))
    {
        return;
    }

    command(one_of_list( ({
        "shout DEATH!!",
        "emote turns his baleful gaze upon the attacker of his brothers.",
        "shout Touch my little brothers and DIE!",
        "shout Colossus CRUSH!" }) ) );
} /* assist */


/*
 * Function name:        ask_for_assistance
 * Description  :        When we need assistance from other goblins,
 *                       this happens.
 */
public void
ask_for_assistance()
{
    /* Too spammy otherwise */
    if (random(7))
    {
        return;
    }

    command(one_of_list( ({
        "emote shouts: All brothers! Time to KILL!",
        "shout Another meal for you, little brothers!",
        "emote roars, summoning help from his brothers.",
        "shout You will be eaten!!" }) ) );
} /* ask_for_assistance */


/*
 * Function name:       attacked_by
 * Description:         This routine is called when we are attacked.
 * Arguments:           ob: The attacker
 *
 * Mask to allow for assistance from other goblins.
 */
public void
attacked_by(object ob)
{
    ::attacked_by(ob);
    get_assistance(ob);
} /* attacked_by */


/*
 * Function name:        special_attack
 * Description  :        every so often we'll do a special attack
 * Arguments    :        object enemy - the person we're attacking
 * Returns      :        int 0 - don't do the special
 *                           1 - do the special attack
 */
public int
special_attack(object victim)
{
    object *enemies = FILTER_PRESENT_LIVE(query_enemy(-1));
    mixed  *bres;

    if (random(100) > 15)
    {
        return 0;
    }

    if (!objectp(victim) && !sizeof(enemies))
    {
        return 1;
    }

    if (!objectp(victim))
    {
        victim = enemies[random(sizeof(enemies))];
    }

    if (environment(victim) != environment(this_object()))
    {
        return 1;
    }

    bres = victim->hit_me(F_PENMOD(70, 70), W_BLUDGEON, this_object(), -1);

    if (bres[0] < 0)
    {
        victim->catch_msg("The goblin colossus swings his mighty fist"
          + " in an arcing backhand, which you narrowly duck!\n");
        say("The goblin colossus swings his mighty fist in an arcing"
          + " backhand at " + QTNAME(victim) + ", who manages to"
          + " narrowly duck the blow!\n", victim);
    }
    else if (bres[0] < 5)
    {
        victim->catch_msg("The goblin colossus swings his mighty fist"
          + " in an arcing backhand, just barely glancing you as"
          + " you twitch to duck it! Oof ... you feel a bit dizzy.\n");
        say("The goblin colossus swings his mighty fist in an arcing"
          + " backhand at " + QTNAME(victim) + ", who twitches to duck"
          + " just slightly too late, resulting in a glancing blow!\n",
            victim);
        victim->add_attack_delay(11 + random(20));
    }
    else if (bres[0] < 100) 
    {
        victim->catch_msg("The goblin colossus swings his mighty fist"
          + " in an arcing backhand which catches you squarely in the"
          + " side of the face! Tumbling onto your back, you struggle"
          + " to regain your footing, holding your head which is"
          + " swimming in pain!\n");
        say("The goblin colossus swings his mighty fist in an arcing"
          + " backhand which catches " + QTNAME(victim) + " squarely"
          + " in the side of the face! Tumbling onto "
          + victim->query_possessive() + " back, "
          + victim->query_pronoun() + " struggles to regain "
          + victim->query_possessive() + " footing, looking utterly"
          + " dazed.\n", victim);
        victim->add_attack_delay(21 + random(bres[0]));
    }
    else
    {
        victim->catch_msg("The goblin colossus swings his mighty fist"
           + " in an arcing backhand which slams into your head with"
           + " perfect aim! The sound of your own neck snapping is"
           + " the last thing you hear.\n");
        say("The goblin colossus swings his mighty fist in an arcing"
           + " backhand, slamming with sickening precision into "
           + QTNAME(victim) + "'s head. With a terrible snap, the neck"
           + " breaks and " + victim->query_posssessive() + " body"
           + " falls slack to the ground in a miserable lifeless"
           + " clump.\n", victim);
     }

     return 1;
} /* special_attack */


/*
 * Function name:        notify_death
 * Description  :        Notify onlookers of my death
 * Arguments    :        object killer - the object that killed me
 *
 * We redefine this so that Gorboth can get notifications of who is
 * dying where and by whom.
 */
public void
notify_death(object killer)
{
    ::notify_death(killer);

    TELL_G(" -*-*-*-* A " + Goblin_Type + " was killed by "
      + capitalize(killer->query_real_name()) + " at "
      + FILE_NAME(MASTER_OB(environment(this_object()))) + "!");
} /* notify_death */
