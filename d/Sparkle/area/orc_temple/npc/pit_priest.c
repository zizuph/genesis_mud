/*
 *  /d/Sparkle/area/orc_temple/npc/pit_priest.c
 *
 *  This is one of the priests from the orc dungeons beneath the
 *  temple in Sparkle. These ones protect the High Priest.
 *
 *  Created November 2010, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit NPC_DIR + "temple_npc";
inherit "/d/Emerald/lib/aid_npc";

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

/* Global Variablas */
public string        *Busy_Msgs = ({
        "The stooping orcish priest ignores you and continues to"
      + " chant.",
        "The stooping orcish priest pays you no heed.",
        "The stooping orcish priest seems not to hear you.",
        "The stooping orcish priest continues his ceremonial"
      + " incantation as if he didn't hear you.",
        "The stooping orcish priest appears too involved in his"
      + " rituals to notice you." });



/*
 * Function name:        create_temple_npc  
 * Description  :        The constructor for the monster
 */
public void
create_temple_npc  ()
{
    set_name("orc");
    set_race_name("orc");
    add_name( ({ "goblin", "priest", ORC_TEMPLE_NPC }) );
    add_adj( ({ "stooping", "orcish" }) );

    set_short("stooping orcish priest");
    set_long("Hunched over and seemingly in a kind of trance, this"
      + " particular priest appears to be dedicated to some ongoing"
      + " ceremonial worship.\n");

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
    add_act("emote offers a harsh whisper: ... Yog ...");
    add_act("emote offers a harsh whisper: ... So ...");
    add_act("emote offers a harsh whisper: ... Thoth ...");

    add_cact("emote closes his eyes in concentration.");
    add_cact("emote spreads his hands outward, and begins to glow.");
    add_cact("shout This one shall not disturb the pit!");

    set_give_response("No.");
    set_default_answer(VBFC_ME("default_answer"));

    add_prop(LIVE_I_NEVERKNOWN, 1);

    /* We assist other goblins who get attacked. */
    set_give_aid(1);

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
                       this_object())), &->id(HIGH_PRIEST));
    string  bite_loc;
    int     bite_damage;
    object  target = one_of_list(targets);

    if (!target)
    {
        target = this_object();
    }

    if (attack_type)
    {
        return 0;
    }

    tell_room(environment(enemy),
        "The orcish priest chants a prayer, and raises his hands"
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
    command(one_of_list( ({
        "shout Protect sanctity of pit!",
        "emote turns to assist his fellow priests.",
        "shout This one pay ultimate price!",
        "shout Cast it into the pit!" }) ) );
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
        "emote shouts for assistance!",
        "shout This one, brothers! Kill this one!",
        "emote gestures for assistance from any nearby priests.",
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
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    return  one_of_list(Busy_Msgs) + "\n";
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
    tp->catch_msg(one_of_list(Busy_Msgs) + "\n");
} /* intro_responses */


/*
 * Function name:       not_here_func
 * Description  :       called when player asks question & leaves
 * Returns      :       0 -> don't answer the question
 */
public int
not_here_func()
{
     command("emote continues his ritual.");
     return 0;
} /* not_here_func */


/*
 * Function name:        assist_npc
 * Description  :        Have npcs help one another ... sometimes
 * Arguments    :        object enemy - who attacked us
 *
 * We'll have these guys be a bit less likely to assist, since
 * they are too tied up in their worship.
 */
public void 
assist_npc(object enemy)
{
    if (member_array(enemy, this_object()->query_enemy(-1)) >= 0) 
    {
        return;
    }

    if (!random(5))
    {
        assist();   
        this_object()->attack_object(enemy);
    }
    else
    {
        not_assist();
    }
}
