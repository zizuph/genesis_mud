/*
 *  /d/Sparkle/area/tutorial/npc/thief_trainer.c
 *
 *  This npc is located in the thief training room of the
 *  Greenhollow Adventurers Guild. She'll answer questions about
 *  the various skills she trains.
 *
 *  Location: /d/Sparkle/area/tutorial/town/adv_guild6.c
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
public void    add_trainer_asks();
public void    sneak_answer();
public void    hide_answer();
public void    train_answer();
public void    thief_answer();



/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("Alivia");
    set_name("alivia");
    add_name( ({ "alivia shadowfoot", "trainer" }) );
    set_adj( ({ "dark", "stealthy", }) );
    set_race_name("hobbit");
    set_gender(G_FEMALE);

    set_title("Shadowfoot, Expert Thief and Trainer");

    set_long("Bare feet and shining eyes are all you can see"
      + " beyond the cloak that this tiny figure is wrapped"
      + " in. This hobbit is an expert at thief skills,"
      + " which she will be glad to teach you. You may"
      + " <ask> her about any of the skills she trains.\n");

    default_config_npc(80);  /* A rather powerful npc */

    set_act_time(2);
    add_act("emote looks you up and down, smiling slightly.");
    add_act("emote says: I'm here to train you. Feel free to"
      + " <ask> me about any of the skills that I offer for"
      + " training.");
    add_act("emote says: I'd be glad to help you <learn>"
      + " new skills or <improve> the skills you've already"
      + " learned.");
    add_act("emote says: Don't forget to read the tutorial"
      + " signs!");
    add_act("emote says: Different guilds offer different skills to"
      + " different levels. You might find new thief skills to"
      + " learn elsewhere in the land, or places that train these"
      + " ones further than I do.");

    set_job_response("It is my job to train people in thief skills.");

    remove_prop(LIVE_I_NEVERKNOWN);

    add_silverdell_asks();
    add_trainer_asks();

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
 * Function name:        add_trainer_asks
 * Description  :        hardel responds to questions about
 *                       the skills he trains.
 */
public void
add_trainer_asks()
{
    add_ask( ({ "sneak", "sneak skill",
                "sneaking", "sneaking skill" }),
        VBFC_ME("sneak_answer"));
    add_ask( ({ "hide", "hide skill",
                "hiding", "hiding skill" }),
        VBFC_ME("hide_answer"));
    add_ask( ({ "train", "training", "improve", "improving",
                "learn", "learning", "skills", "skill",
                "skill training", "training skills", "trainer" }),
        VBFC_ME("train_answer"));
    add_ask( ({ "thief", "thievery", "thief skills",
                "cloak and dagger" }),
        VBFC_ME("thief_answer"));
} /* add_trainer_asks */


/*
 * Function name:       sneak_answer
 * Description  :       response to an add_ask
 */
public string
sneak_answer()
{
    command("say Sneaking is a persons ability to enter or leave"
      + " a room without others noticing. The higher you train this"
      + " skill, the more awareness skill other people will need to"
      + " be able to notice you.");
    return "";
} /* sneak_answer */


/*
 * Function name:       hide_answer
 * Description  :       response to an add_ask
 */
public string
hide_answer()
{
    command("say Improving your hide skill will allow you to"
      + " try to become invisible to other people who come"
      + " into the room you are in. The higher your skill, the"
      + " more awareness skill other people will need to be able"
      + " to see you. You can also hide items in a room using"
      + " this skill. In the tutorial, this skill is not trained,"
      + " but you will find it available elsewhere in Genesis.");
    return "";
} /* hide_answer */


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
 * Function name:       thief_answer
 * Description  :       response to an add_ask
 */
public string
thief_answer()
{
    command("say Tired of having to work so hard for a bit of progress"
      + " in life? A bit of cloak and dagger never really hurt anyone!"
      + " Train with me, and you'll be that much better off.");
    return "";
} /* thief_answer */

