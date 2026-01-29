/*
 *  /d/Sparkle/area/orc_temple/npc/goblin_priest.c
 *
 *  This is one of the priests from the orc dungeons beneath the
 *  temple in Sparkle.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit NPC_DIR + "temple_npc";

#include <filepath.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>

/* Prototypes */
public void        create_temple_npc  ();
public void        arm_me();
public int         special_attack(object enemy);
public string      default_answer();
public void        intro_responses(object tp);
public int         not_here_func();


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
    add_name( ({ "goblin", "priest", ORC_TEMPLE_NPC }) );
    add_adj( ({ "orcish" }) );

    set_short("orcish priest");
    set_long("Unlike most of its kind, this orc looks actually rather"
      + " sage in his attire. His eyes communicate both wisdom and"
      + " cunning.\n");

    set_stats( ({ NPC_PRIEST_STR,
                  NPC_PRIEST_DEX,
                  NPC_PRIEST_CON,
                  NPC_PRIEST_INT,
                  NPC_PRIEST_WIS,
                  NPC_PRIEST_DIS,
               }) );
                  
    set_skill(SS_WEP_CLUB,     20);
    set_skill(SS_AWARENESS,    50);
    set_skill(SS_DEFENCE,      20);
    set_skill(SS_ELEMENT_LIFE, 100);
    set_skill(SS_SPELLCRAFT,   100);

    set_act_time(10 + random(7));
    add_act("peer slow");
    add_act("say Big demon hungers ... will need more souls soon!");
    add_act("say Where that worthless jailer?");
    add_act("say Why so few new prisoners this week?");
    add_act("say You not feel it? Big demon hungry ...");
    add_act("say Warriors okay, but runts"
      + " almost worth feeding to demon!");
    add_act("emote softly mutters an incantation.");

    add_cact("emote closes his eyes in concentration.");
    add_cact("emote spreads his hands outward, and begins to glow.");
    add_cact("shout Brothers keep calm!");

    set_job_response("I help High Priest. Big important stuff.");
    set_dungeon_response( ({
        "Dungeons hold power bigger than you can imagine!",
        "You not be here! Go now!",
        "Orcs do important work in dungeons." }) );
    set_demon_response( ({
        "Silence! Not speak of it!",
        "You not speak of things you not understand, fool!",
        "Speak of such things, get thrown into pit!" }) );
    set_prisoner_response( ({
        "Prisoners too few. Need more work from runts!",
        "Jailer too slow. Tired of waiting for him!",
        "Prisoners feed demon!" }) );
    set_runt_response( ({ "Runts annoying, but important work." }) );
    set_warrior_response( ({ "Warriors grumpy, but they do good"
      + " job." }) );
    set_priest_response(
        ({ "That us." }) );
    set_jailer_response("Jailer getting lazy!");
    set_hp_response("You not disturb High Priest!");
    set_give_response("I not need this! I too busy!");
    add_dungeon_asks();

    add_ask( ({ "pit" }), "say You not go near pit!", 1);
    add_ask( ({ "haunted", "ghost", "ghosts" }),
        "say Ghosts? What you talk about?", 1);

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

    arm = clone_object(WEP_DIR + "priest_staff");
    arm->move(this_object());
    arm = clone_object(ARM_DIR + "priest_robe");
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
    int     attack_type = random(13); /* 7% chance to do special */
    mixed  *targets = filter(all_inventory(environment(
                       this_object())), &->id(ORC_TEMPLE_NPC));
    string  bite_loc;
    int     bite_damage;
    object  target = one_of_list(targets);

    if (attack_type)
    {
        return 0;
    }

    tell_room(environment(enemy),
        "The orc priest chants a prayer, and raises his hands"
      + " in a swift gesture and shouts: KALACH, SHRIMPEK!\n"
      + "The " + target->short()
      + " is surrounded by a brief blinding glow, and fully healed!\n");

    target->heal_hp(target->query_max_hp());

    return 1;
} /* special_attack */


/*
 * Function name:        assist
 * Description  :        When assisting other orcs that get attacked,
 *                       we display what is happening.
 */
public void
assist()
{
    command(one_of_list( ({
        "shout You not alone, brother!",
        "emote turns to assist his fellow orc.",
        "shout Not panic, brother. I here!",
        "shout You contend with me now, fool!" }) ) );
} /* assist */


/*
 * Function name:        ask_for_assistance
 * Description  :        When we need assistance from other orcs,
 *                       this happens.
 */
public void
ask_for_assistance()
{
    command(one_of_list( ({
        "emote shouts for assistance!",
        "shout To me, brothers, to me!",
        "emote gestures for assistance from any nearby orcs.",
        "shout Kill fool, brothers!" }) ) );
} /* ask_for_assistance */


/*
 * Function name:       attacked_by
 * Description:         This routine is called when we are attacked.
 * Arguments:           ob: The attacker
 *
 * Mask to allow for assistance from other orcs.
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
        "Not disturb me with meaningless chatter.",
        "I not know this.",
        "Go bother jailer with questions.",
        }) );

    command("emote frown impatient");
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
        command("glare "+tp->query_real_name());
        break;
    case 1:
        command("say Your name of no importance to us.");
        break;
    case 2:
        command("say We not care about you or your name!");
        break;
    case 3:
        command("say Unimpressive name, that for sure.");
        break;
    case 4: 
        command("say You not know us!");
        break;
    case 5:
        command("say Not have time for pleasantries, fool!");
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
     command("shout What fool distrub priest and then run?");
     return 0;
} /* not_here_func */


/*
 * Function name:        not_ask_for_assistance
 * Description  :        When we don't want assistance from other orcs,
 *                       this happens.
 */
public void
not_ask_for_assistance()
{
    command(one_of_list( ({
        "emote closes on you, clearly wanting to take you on alone!",
        "shout This one all mine!",
        "shout Watch, brothers! Feed this one to pit all alone!",
        "shout Stand aside, brothers! Me show how it done!" }) ) );
} /* not_ask_for_assistance */


/*
 * Function name:        not_assist
 * Description  :        What orcs do when the refuse to assist
 */
public void
not_assist()
{
    command(one_of_list( ({
        "shout Quick, brother! You kill it! Show us how it done!",
        "emote backs up, clearly too afraid to help.",
        "shout Yog-Sothoth help you, brother! You do it!",
        "shout Me not want tear robe. You do it, brother!" }) ) );
} /* not_assist */
