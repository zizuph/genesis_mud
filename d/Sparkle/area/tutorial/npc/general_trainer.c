/*
 *  /d/Sparkle/area/tutorial/npc/general_trainer.c
 *
 *  This npc is located in the general training room of the
 *  Greenhollow Adventurers Guild. He'll answer questions about
 *  the various skills he trains.
 *
 *  Location: /d/Sparkle/area/tutorial/town/adv_guild4.c
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
public void    awareness_answer();
public void    climb_answer();
public void    trading_answer();
public void    swim_answer();
public void    language_answer();
public void    train_answer();
public void    enemy_answer();
public void    object_answer();
public void    appraise_answer();
public void    general_answer();



/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("Paulsen");
    set_name("paulsen");
    add_name( ({ "paulsen battershell", "trainer" }) );
    set_adj( ({ "strong", "weathered", }) );
    set_race_name("dwarf");

    set_title("Battershell, Traveller of the Lands and General Trainer");

    set_long("This dwarf looks as if he has seen and done a great many"
      + " things in his time. His body reflects the experience of many"
      + " nights spent beneath the stars, yet in his eyes you see the"
      + " wisdom that can only be gained by much travel in far off"
      + " lands. He will be happy to train you in the general skills"
      + " which will help you get by in the game. You can <ask> him about"
      + " any of the skills that he trains.\n");

    default_config_npc(100);  /* He's a tough old bird */

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
      + " different levels. You might find new general skills to"
      + " learn elsewhere in the land, or places that train these"
      + " ones further than I do.");

    set_job_response("It is my job to train people in the general"
      + " skills that help them get by in the land.");

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
    add_ask( ({ "awareness", "awareness skill" }),
        VBFC_ME("awareness_answer"));
    add_ask( ({ "climb", "climb skill", "climbing",
                "climbing skill" }),
        VBFC_ME("climb_answer"));
    add_ask( ({ "swim", "swim skill", "swimming skill",
                "swimming" }),
        VBFC_ME("swim_answer"));
    add_ask( ({ "trading", "trading skill", "trade", "trade skill" }),
        VBFC_ME("trading_answer"));
    add_ask( ({ "language", "language skill" }),
        VBFC_ME("language_answer"));
    add_ask( ({ "train", "training", "improve", "improving",
                "learn", "learning", "skills", "skill",
                "skill training", "training skills", "trainer" }),
        VBFC_ME("train_answer"));
    add_ask( ({ "appraise enemy", "enemy", "appraise enemy skill" }),
        VBFC_ME("enemy_answer"));
    add_ask( ({ "appraise value", "value", "appraise value skill" }),
        VBFC_ME("value_answer"));
    add_ask( ({ "appraise object", "object", "appraise object skill" }),
        VBFC_ME("object_answer"));
    add_ask( ({ "appraise", "appraise skill" }),
        VBFC_ME("appraise_answer"));
    add_ask( ({ "general", "general skills", "general trainer" }),
        VBFC_ME("general_answer"));
} /* add_trainer_asks */


/*
 * Function name:       awareness_answer
 * Description  :       response to an add_ask
 */
public string
awareness_answer()
{
    command("say Awareness is one of the most critical skills for"
      + " explorers and people who enjoy a good quest. Without"
      + " a high awareness skill, you might miss those important"
      + " details that help you to get further along the path."
      + " Awareness is also important for seeing hidden things"
      + " or people who are trying to sneak around unseen.");
    return "";
} /* awareness_answer */


/*
 * Function name:       climb_answer
 * Description  :       response to an add_ask
 */
public string
climb_answer()
{
    command("say You will find places in the realms which require"
      + " you to have an advanced understanding of how to climb."
      + " Imagine being at the bottom of a cliff, and high above"
      + " you is treasure among the rocks ... but you just"
      + " can't seem to get up there ... Time to train your climbing"
      + " skill!");
    return "";
} /* climb_answer */


/*
 * Function name:       trading_answer
 * Description  :       response to an add_ask
 */
public string
trading_answer()
{
    command("say Improving your skill in trading will help you"
      + " get rich more quickly. The better your trading skill,"
      + " the better the prices you get when you buy and sell"
      + " merchandise.");
    return "";
} /* trading_answer */


/*
 * Function name:       swim_answer
 * Description  :       response to an add_ask
 */
public string
swim_answer()
{
    command("say Certain regions of Genesis have bodies of water"
      + " that require an adventurer to have knowledge of swimming"
      + " in order to travel effectively. Raising this skill will"
      + " ensure that you do not find yourself waiting on the shore"
      + " while others venture forth.");
    return "";
} /* swim_answer */


/*
 * Function name:       language_answer
 * Description  :       response to an add_ask
 */
public string
language_answer()
{
    command("say Being well-versed in the various languages of Genesis"
      + " can come in extremely handy, especially when trying to solve"
      + " quests. Improve this skill to increase your understanding of"
      + " foreign tongues.");
    return "";
} /* language_answer */


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
 * Function name:       enemy_answer
 * Description  :       response to an add_ask
 */
public string
enemy_answer()
{
    command("say This skill gives you the ability to get a sense"
      + " of your opponent at a glance. In particular, it will"
      + " make your comparisons more accurate when judging if"
      + " the enemy is too difficult for you to kill.");
    return "";
} /* enemy_answer */


/*
 * Function name:       value_answer
 * Description  :       response to an add_ask
 */
public string
value_answer()
{
    command("say This skill gives you the ability to judge the"
      + " value of anything in your inventory using the <appraise>"
      + " command.");
    return "";
} /* value_answer */


/*
 * Function name:       object_answer
 * Description  :       response to an add_ask
 */
public string
object_answer()
{
    command("say This skill gives you the ability use the <compare>"
      + " and <appraise> commands better with items. Specifically, it"
      + " is useful for determining which of two weapons or armours"
      + " are better.");
    return "";
} /* object_answer */


/*
 * Function name:       appraise_answer
 * Description  :       response to an add_ask
 */
public string
appraise_answer()
{
    command("say There are three different appraise skills - appraise"
      + " enemy, appraise value, and appraise object. Which do you wish"
      + " to know about?");
    return "";
} /* appraise_answer */


/*
 * Function name:       general_answer
 * Description  :       response to an add_ask
 */
public string
general_answer()
{
    command("say I'm the expert around here at training General Skills."
      + " What I teach might not be the thing that wins your fights for"
      + " you. However, these types of skills are just the thing for"
      + " completing quests and exploring the land.");
    return "";
} /* general_answer */
