/*
 *  /d/Sparkle/guilds/new_merc/event/goblin_shaman.c
 *
 *  The healing goblin attacker for the raid on Sparkle that will
 *  lead to the opening of the Free Mercenary Guild.
 *
 *  Created August 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/monster";
inherit "/d/Emerald/lib/aid_npc";

#include <filepath.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>
#include "../merc_defs.h"

/* Prototypes */
public void        create_monster();
public void        arm_me();
public int         special_attack(object enemy);
public void        notify_death(object killer);

/* Global Variables */
public string      Goblin_Type = "shaman";


/*
 * Function name:        create_monster
 * Description  :        The constructor for the monster
 */
public void
create_monster()
{
    set_name("goblin");
    set_race_name("goblin");
    add_name( ({ "shaman", EVENT_GOBLIN }) );
    add_adj( ({ "goblin" }) );

    set_short("goblin shaman");
    set_long("Unlike most of its kind, this goblin looks actually rather"
      + " sage in his attire. His eyes communicate both wisdom and"
      + " cunning.\n");

    set_stats( ({ 50 + (random(30)),
                  50 + (random(25)),
                  120 + (random(30)),
                  150 + (random(20)),
                  150 + (random(20)),
                  100 + (random(40)) }) );
                  
    set_skill(SS_WEP_CLUB,     80);
    set_skill(SS_AWARENESS,    80);
    set_skill(SS_DEFENCE,      80);
    set_skill(SS_ELEMENT_LIFE, 100);
    set_skill(SS_SPELLCRAFT,   100);

    add_act("peer slow");
    add_act("say Concentrate! We must not spoil this opportunity!");
    add_act("say Worthless runts! I can only heal one of you at once!");
    add_act("say Stay close to me, runts. We shall prevail.");

    add_cact("emote closes his eyes in concentration.");
    add_cact("emote spreads his hands outward, and begins to glow.");
    add_cact("shout Remain calm, runts!");

    /* We assist other goblins who get attacked. */
    set_give_aid(1);

    set_aggressive(1, 70);
} /* create_monster */


/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{
    object  arm;

    arm = clone_object(EVENT_DIR + "shaman_staff");
    arm->move(this_object());
    arm = clone_object(EVENT_DIR + "shaman_robe");
    arm->move(this_object());

    command("wear all");
    command("wield all");
} /* arm_me */


/*
 * Function name:        special_attack
 * Description  :        every so often we'll do a special attack
 * Arguments    :        object enemy - the person we're attacking
 * Returns      :        int 0 - don't do the special
 *                           1 - do the special attack
 */
public int
special_attack(object enemy)
{
    int     attack_type = random(5); /* 20% chance to do special */
    mixed  *targets = filter(all_inventory(environment(
                       this_object())), &->id(EVENT_GOBLIN));
    string  bite_loc;
    int     bite_damage;
    object  target = one_of_list(targets);

    /* We'll only let the runts try this once per 10 combat rounds. */
    if (attack_type)
    {
        return 0;
    }

    tell_room(environment(enemy),
        "The goblin shaman chants a prayer, and raises his hands"
      + " in a swift gesture and shouts: KALACH, SHRIMPEK!\n"
      + "The " + target->short()
      + " is surrounded by a brief blinding glow, and fully healed!\n");

    target->heal_hp(target->query_max_hp());

    return 1;
} /* special_attack */


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
        "shout You are not alone, brother!",
        "emote turns to assist his fellow goblin.",
        "shout Do not panic, brother. I am here!",
        "shout You have me to contend with now, fool!" }) ) );
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
        "emote shouts for assistance!",
        "shout To me, brothers, to me!",
        "emote gestures for assistance from any nearby goblins.",
        "shout Kill this fool, brothers!" }) ) );
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