/*
 *  /d/Sparkle/guilds/new_merc/event/goblin_warrior.c
 *
 *  The tougher goblin attacker for the raid on Sparkle that will
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
public void        notify_death(object killer);

/* Global Variables */
public string      Goblin_Type = "warrior";

/*
 * Function name:        create_monster
 * Description  :        The constructor for the monster
 */
public void
create_monster()
{
    set_name("goblin");
    set_race_name("goblin");
    add_name( ({ "warrior", EVENT_GOBLIN }) );
    add_adj( ({ "goblin" }) );

    set_short("goblin warrior");
    set_long("This goblin is very large for its kind. Muscles buldge"
      + " from its powerful torso, and hideous teeth protrude from"
      + " its ugly lips.\n");

    set_stats( ({ 150 + (random(30)),
                  150 + (random(25)),
                  150 + (random(30)),
                  50 + (random(20)),
                  50 + (random(20)),
                  150 + (random(40)) }) );
                  
    set_skill(SS_WEP_AXE,      100);
    set_skill(SS_AWARENESS,    80);
    set_skill(SS_DEFENCE,      100);
    set_skill(SS_PARRY,        100);
    set_skill(SS_2H_COMBAT,    100);

    add_act("grin");
    add_act("say Shut up! Leave the fighting to me.");
    add_act("say If you runts get in my way, I'll kill you!");
    add_act("say This is what we've been waiting for!");

    add_cact("emote moves with confidence and powerful speed.");
    add_cact("emote laughs harshly.");
    add_cact("shout Runts, get over here!");

    /* We assist other goblins who get attacked. */
    set_give_aid(1);

    set_aggressive(1, 80);
} /* create_monster */


/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{
    object  arm;

    arm = clone_object(EVENT_DIR + "warrior_axe");
    arm->move(this_object());
    arm = clone_object(EVENT_DIR + "warrior_axe");
    arm->move(this_object());
    arm = clone_object(EVENT_DIR + "warrior_plate");
    arm->move(this_object());
    arm = clone_object(EVENT_DIR + "warrior_helm");
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
        "shout Get away from him!",
        "emote bellows in rage!",
        "shout Now you die!!",
        "shout Ho ho! Another victim!" }) ) );
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
        "emote shouts: Lets do this, brothers!",
        "shout Goblins! Lets bring the pain!",
        "emote calls out a command for aid.",
        "shout Join in, brothers! We'll eat this one!" }) ) );
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