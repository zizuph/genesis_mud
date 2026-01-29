/*
 *  /d/Sparkle/area/tutorial/npc/combat_trainer.c
 *
 *  This npc is located in the combat training room of the
 *  Greenhollow Adventurers Guild. He'll answer questions about
 *  the various skills he trains.
 *
 *  Location: /d/Sparkle/area/tutorial/town/adv_guild3.c
 *
 *  Created July 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit NPC_DIR + "silverdell_npc";
inherit "/d/Genesis/lib/intro";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>


/* prototypes */
public void    create_silverdell_npc();
public void    introduce(object who);
public void    react_intro(object tp);
public void    add_hardel_asks();
public void    sword_answer();
public void    axe_answer();
public void    knife_answer();
public void    club_answer();
public void    defence_answer();
public void    train_answer();
public void    unarmed_answer();
public void    fighting_answer();



/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("Sera");
    set_name("sera");
    add_name( ({ "sera muur", "trainer", "_fighting_trainer" }) );
    set_adj( ({ "thin", "dextrous", }) );
    set_race_name("elf");
    set_gender(G_FEMALE);

    set_title("Muur, Combat Trainer of Greenhollow");

    set_long("Though not as tall as some of her kind, this elf"
      + " looks extremely deadly. It appears"
      + " as if she is the trainer here. You can <ask> her about"
      + " any of the skills that she trains.\n");

    default_config_npc(120);  /* We'll make her pretty impressive */

    set_act_time(2);
    add_act("emote looks you up and down, smiling broadly.");
    add_act("emote says: I'm here to train you. Feel free to"
      + " <ask> me about any of the skills that I offer for"
      + " training.");
    add_act("emote says: I'd be glad to help you <learn>"
      + " new skills or <improve> the skills you've already"
      + " learned.");
    add_act("emote says: Don't forget to read the tutorial"
      + " signs!");
    add_act("emote says: Different guilds offer different skills to"
      + " different levels. You might find new fighting skills to"
      + " learn elsewhere in the land, or places that train these"
      + " ones further than I do.");

    set_job_response("It is my job to train people to become"
      + " better fighters.");

    remove_prop(LIVE_I_NEVERKNOWN);

    add_silverdell_asks();
    add_hardel_asks();

    setuid();
    seteuid(getuid());
} /* create_silverdell_npc */


/*
 * Function name:        introduce
 * Description  :        create a delay between intro and reaction
 * Arguments    :        object who - the player
 */
public void
introduce(object who)
{
    set_alarm(itof(2 + random(5)), 0.0, &react_intro(who));
} /* introduce */


/*
 * Function name:        react_intro
 * Description  :        the npc introduces himself
 * Arguments    :        tp - the player
 */
void
react_intro(object tp)
{
    if (!present(tp, environment(this_object())))
    {
        command("say Where did they go?");
        return;
    }

    command("introduce me");
} /* react_intro */


/*
 * Function name:        add_hardel_asks
 * Description  :        hardel responds to questions about
 *                       the skills he trains.
 */
public void
add_hardel_asks()
{
    add_ask( ({ "sword", "sword skill", "swords" }),
        VBFC_ME("sword_answer"));
    add_ask( ({ "axe", "axe skill", "axes" }),
        VBFC_ME("axe_answer"));
    add_ask( ({ "knife", "knife skill", "dagger",
                "dagger skill", "knives", "daggers" }),
        VBFC_ME("knife_answer"));
    add_ask( ({ "club", "club skill", "clubs" }),
        VBFC_ME("club_answer"));
    add_ask( ({ "defence", "defence skill", "defense",
                "defense skill" }),
        VBFC_ME("defence_answer"));
    add_ask( ({ "unarmed", "unarmed skill", "unarmed combat",
                "unarmed combat skill" }),
        VBFC_ME("unarmed_answer"));
    add_ask( ({ "train", "training", "improve", "improving",
                "learn", "learning", "skills", "skill",
                "skill training", "training skills" }),
        VBFC_ME("train_answer"));
    add_ask( ({ "fight", "fighting", "combat", "combat skills",
                "fighting skills" }),
        VBFC_ME("fighting_answer"));
} /* add_hardel_asks */


/*
 * Function name:       sword_answer
 * Description  :       response to an add_ask
 */
public string
sword_answer()
{
    command("say Because swords are the most common weapons in"
      + " the land, training sword skill is an extremely smart"
      + " thing to do. The higher you train this skill, the better"
      + " you will be at dealing damage in battle with a sword.");
    return "";
} /* sword_answer */


/*
 * Function name:       axe_answer
 * Description  :       response to an add_ask
 */
public string
axe_answer()
{
    command("say Axe weapons are less commonly used when compared"
      + " to swords. Nonetheless, it is good to be versatile. Train"
      + " this skill to deal more combat damage with an axe.");
    return "";
} /* axe_answer */


/*
 * Function name:       knife_answer
 * Description  :       response to an add_ask
 */
public string
knife_answer()
{
    command("say Even though knives and daggers are much less"
      + " effective at dealing damage compared to a sword, they"
      + " are also much easier to obtain and cost less. Therefore,"
      + " for a new player, this is one of the best skills to start"
      + " off with.");
    return "";
} /* knife_answer */


/*
 * Function name:       club_answer
 * Description  :       response to an add_ask
 */
public string
club_answer()
{
    command("say Some people prefer weapons that crush rather than"
      + " cut. Maces, hammers, flails, morningstars, and plain old"
      + " clubs all fall under the club skill. If you want to do more"
      + " damage with weapons of this type, this is the skill for"
      + " you.");
    return "";
} /* club_answer */


/*
 * Function name:       defence_answer
 * Description  :       response to an add_ask
 */
public string
defence_answer()
{
    command("say Attacking is only half of any combat situation."
      + " When you aren't swinging your weapon, you are trying to"
      + " avoid being hit by your opponent. Training your skill"
      + " in defence makes you better at avoiding damage in"
      + " combat, and is one of the most important skills you"
      + " can learn.");
    return "";
} /* defence_answer */


/*
 * Function name:       train_answer
 * Description  :       response to an add_ask
 */
public string
train_answer()
{
    command("say Skills are your abilities in the game. At an"
      + " Adventurer Guild such as this, you can use the <learn>"
      + " command to see if there are any new skills you can add"
      + " to your repertoire. You can also use the <improve>"
      + " command to raise the level of skills you already know."
      + " Be sure to read the tutorial sign for more information"
      + " on this subject.");
    return "";
} /* train_answer */


/*
 * Function name:       unarmed_answer
 * Description  :       response to an add_ask
 */
public string
unarmed_answer()
{
    command("say Sometimes you'll find that you don't have a weapon"
      + " at the ready. Under such circumstances, it is useful to"
      + " be able to fend off an attacker with your bare hands. While"
      + " unarmed combat does less damage than combat with just"
      + " about any weapon, it is still a useful skill in a pinch.");
    return "";
} /* unarmed_answer */


/*
 * Function name:       fighting_answer
 * Description  :       response to an add_ask
 */
public string
fighting_answer()
{
    command("say Want to win a fight? The skills I train will be the ones"
      + " to focus on, if so.");
    return "";
} /* fighting_answer */
