/*
 *  /d/Sparkle/area/orc_temple/npc/goblin_warrior.c
 *
 *  These are slightly tougher foes located in the Orc Temple newbie
 *  grinder and quest area in Sparkle.
 *
 *  Created October 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit NPC_DIR + "temple_npc";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_temple_npc  ();
public void        arm_me();
public string      default_answer();
public void        intro_responses(object tp);
public int         not_here_func();

/* Global Variables */
public string      Goblin_Type = "warrior";

/*
 * Function name:        create_temple_npc  
 * Description  :        The constructor for the monster
 */
public void
create_temple_npc  ()
{
    set_name("orc");
    add_name("guard");
    set_race_name("orc");
    add_name( ({ "goblin", "warrior", ORC_TEMPLE_NPC }) );
    add_adj( ({ "orcish" }) );

    set_short("orcish warrior");
    set_long("This orc is very large for its kind. Muscles buldge"
      + " from its powerful torso, and hideous teeth protrude from"
      + " its ugly lips.\n");

    set_stats( ({ NPC_WARRIOR_STR,
                  NPC_WARRIOR_DEX,
                  NPC_WARRIOR_CON,
                  NPC_WARRIOR_INT,
                  NPC_WARRIOR_WIS,
                  NPC_WARRIOR_DIS,
               }) );
                  
    set_skill(SS_WEP_SWORD,    15);
    set_skill(SS_WEP_AXE,      15);
    set_skill(SS_WEP_CLUB,     15);
    set_skill(SS_WEP_POLEARM,  15);
    set_skill(SS_WEP_KNIFE,    15);
    set_skill(SS_AWARENESS,    60);
    set_skill(SS_DEFENCE,      15);
    set_skill(SS_PARRY,        15);
    set_skill(SS_2H_COMBAT,    15);

    set_act_time(10 + random(7));
    add_act("grin");
    add_act("say If one more runt ask about eating the prisoners ...");
    add_act("say Priests going to have to find someone else to"
      + " feed pet!");
    add_act("say So sick of babysitting stupid runts!");
    add_act("say Bah! Blasted thing kill us all before"
      + " priest learn to control it!");
    add_act("say But if plan works, Sparkle be in ashes and"
      + " we get to sift for babies. Har!");
    add_act("say Jail cells give me creeps.");
    add_act("say Wouldn't kill jailer to give decent food, though!");
    add_act("say Me swear ... something touched me other day when me"
      + " was in jail cell. Ghosts, me say!");
    add_act("say Sure - Priests just laugh, but prison is"
      + " haunted!");
    add_act("close door");

    add_cact("emote moves with confidence and powerful speed.");
    add_cact("emote laughs harshly.");
    add_cact("shout Runts, get over here!");

    set_job_response("Job? Keep scum like you out of way!");
    set_dungeon_response( ({
        "Dungeons none of your business. Get out now!",
        "You aren't careful, we make this your new home!",
        "This where orc like us lock up scum like you." }) );
    set_demon_response( ({
        "Not talk about that! You crazy?",
        "If priest hear you talking about that, you dead!",
        "Shut up about demon! Bad enough it even here ..." }) );
    set_prisoner_response( ({
        "Runts bring new ones every day. Heh ...",
        "Me love prisoners. So much fun to play with.",
        "You look like YOU make good one!" }) );
    set_runt_response( ({ "Runts just plain annoying." }) );
    set_warrior_response( ({ "That me, idiot." }) );
    set_priest_response(
        ({ "Hope priests know what they doing." }) );
    set_jailer_response("Jailer a total idiot.");
    set_hp_response("You not want to mess with High Priest."
      + " He toss idiot like you in pit faster than you can"
      + " blink!");
    set_give_response("You keep own stuff, idiot!");
    add_dungeon_asks();

    add_ask( ({ "food", "eat" }), "say Should feed us better"
      + " for all work we do!", 1);
    add_ask( ({ "pit" }), "say Me not go near that thing!", 1);
    add_ask( ({ "haunted", "ghost", "ghosts" }),
        "say Priest not listen to me, but me swear place is"
      + " full of ghosts!", 1);

    set_default_answer(VBFC_ME("default_answer"));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    setuid();
    seteuid(getuid());
} /* create_temple_npc   */


/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{
    object  arm;
    string  wep = one_of_list( ({ "sword",
                                  "mace",
                                  "axe",
                                  "dagger",
                                  "polearm" }) );

    arm = clone_object(WEP_DIR + "warrior_" + wep);
    arm->move(this_object());

    if (random(2)) /* 50% chance of having a helm */
    {
        arm = clone_object(ARM_DIR + "warrior_helm");
        arm->move(this_object());
    }

    if (random(4) && wep != "polearm") /* 25% chance to get shield */
    {
        arm = clone_object(ARM_DIR + "crude_shield");
        arm->move(this_object());
    }
    else if (random(4)) /* or, 25% chance to get two weapons */
    {
        wep = one_of_list( ({ "sword",
                              "mace",
                              "axe",
                              "dagger" }) );

        arm = clone_object(WEP_DIR + "warrior_" + wep);
        arm->move(this_object());
    }

    arm = clone_object(ARM_DIR + "warrior_plate");
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
    command(one_of_list( ({
        "shout Get away from him!",
        "emote bellows in rage!",
        "shout Now you die!!",
        "shout Ho ho! New victim!" }) ) );
} /* assist */


/*
 * Function name:        ask_for_assistance
 * Description  :        When we need assistance from other goblins,
 *                       this happens.
 */
public void
ask_for_assistance()
{
    command(one_of_list( ({
        "emote shouts: Do this, brothers!",
        "shout Goblins! Now bring the pain!",
        "emote calls out a command for aid.",
        "shout Join in, brothers! We eat this one!" }) ) );
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
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    string  answer = one_of_list( ({
        "You not got better things to do than ask me"
      + " stupid questions?",
        "I look like I know?",
        "Go bother priest with questions.",
        }) );

    command("emote narrows his eyes in annoyance.");
    command("say " + answer);
    return "";
} /* default_answer */


/*
 * Function name:        intro_responses
 * Description  :        provide responses to an introduction
 * Arguments    :        object tp - this_player()
 *
 * This should be redefined in inheriting npcs for flavor variation.
 */
public void
intro_responses(object tp)
{
    switch(random(6))
    {
    case 0:
        command("sneer amus "+tp->query_real_name());
        break;
    case 1:
        command("say Heh ... one of the stupidest names"
          + " me hear.");
        break;
    case 2:
        command("say Good job. You got name. Now scram!");
        break;
    case 3:
        command("say You expect me be impressed?");
        break;
    case 4: 
        command("say Me not give name to you, idiot.");
        break;
    case 5:
        command("say You want name? Ha!");
        break;
    }
} /* intro_responses */


/*
 * Function name:       not_here_func
 * Description  :       called when player asks question & leaves
 * Returns      :       0 -> don't answer the question
 */
public int
not_here_func()
{
     command("peer");
     command("shout What idiot ask me question take off?");
     return 0;
} /* not_here_func */


/*
 * Function name:        not_ask_for_assistance
 * Description  :        When we don't want assistance from other goblins,
 *                       this happens.
 */
public void
not_ask_for_assistance()
{
    command(one_of_list( ({
        "emote closes on you, clearly wanting to take you on alone!",
        "shout This one all mine!",
        "shout You not scare me! Me take you blindfolded!",
        "shout Brothers not help! This one look too easy!" }) ) );
} /* not_ask_for_assistance */


/*
 * Function name:        not_assist
 * Description  :        What goblins do when the refuse to assist
 */
public void
not_assist()
{
    command(one_of_list( ({
        "shout Maybe I not help this time, brother.",
        "emote backs up, clearly too afraid to help.",
        "shout Ha! You can take that one, brother!",
        "shout Brother, you handle own problem!" }) ) );
} /* not_assist */
