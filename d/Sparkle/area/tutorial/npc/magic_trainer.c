/*
 *  /d/Sparkle/area/tutorial/npc/magic_trainer.c
 *
 *  This npc is located in the magic training room of the
 *  Greenhollow Adventurers Guild. She'll answer questions about
 *  the various skills she trains.
 *
 *  Location: /d/Sparkle/area/tutorial/town/adv_guild5.c
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
public void    spellcraft_answer();
public void    herbalism_answer();
public void    train_answer();
public void    magic_answer();
public void    return_object(object obj, object to);
public void    react_letter(object obj, object to);



/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("Bibbiss");
    set_name("bibbiss");
    add_name( ({ "bibbiss paderborn", "trainer",
                 "_tutorial_potion_giver" }) );
    set_adj( ({ "mysterious", "blue-eyed", }) );
    set_race_name("gnome");
    set_gender(G_FEMALE);

    set_title("Paderborn, Arcane Trainer of the Magic Arts");

    set_long("Though tiny in size, there is a potency in the"
      + " eyes of this gnome that you find yourself transfixed"
      + " by. She stands with an air of calm detachment to her"
      + " surroundings. She is able to train you in the ways"
      + " of magic, and will explain any of the skills she"
      + " offers if you <ask> her about them.\n");

    default_config_npc(60);  /* Not a very powerful npc */

    set_act_time(2);
    add_act("emote looks you up and down, smiling quietly.");
    add_act("emote says: I'm here to train you. Feel free to"
      + " <ask> me about any of the skills that I offer for"
      + " training.");
    add_act("emote says: I'd be glad to help you <learn>"
      + " new skills or <improve> the skills you've already"
      + " learned.");
    add_act("emote says: Don't forget to read the tutorial"
      + " signs!");
    add_act("emote says: Different guilds offer different skills to"
      + " different levels. You might find new magic skills to"
      + " learn elsewhere in the land, or places that train these"
      + " ones further than I do.");

    set_job_response("It is my job to train people in the ways of"
      + " spellcraft and magic.");

    remove_prop(LIVE_I_NEVERKNOWN);
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

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
    add_ask( ({ "spellcraft", "spellcasting skill",
                "spell casting", "spell casting skill" }),
        VBFC_ME("spellcraft_answer"));
    add_ask( ({ "herbalism", "herbalism skill", "herb",
                "herb skill", "herbs" }),
        VBFC_ME("herbalism_answer"));
    add_ask( ({ "train", "training", "improve", "improving",
                "learn", "learning", "skills", "skill",
                "skill training", "training skills", "trainer" }),
        VBFC_ME("train_answer"));
    add_ask( ({ "magic", "casting spells", "spells", "arcane arts",
                "magic skills", "magic skill" }),
        VBFC_ME("magic_answer"));
} /* add_trainer_asks */


/*
 * Function name:       spellcraft_answer
 * Description  :       response to an add_ask
 */
public string
spellcraft_answer()
{
    command("say Spellcraft is a skill that will assist you in"
      + " bending the will of magic to your control. Though a very"
      + " uncertain thing even to a master, the ability to"
      + " successfully cast spells will be beyond you entirely"
      + " unless you train in this skill.");
    return "";
} /* spellcraft_answer */


/*
 * Function name:       herbalism_answer
 * Description  :       response to an add_ask
 */
public string
herbalism_answer()
{
    command("say Herbalism is a large enough topic that there is"
      + " an entire chapter on it in this tutorial. Suffice it to"
      + " say that herbs are one of the most powerful things in"
      + " the land. Eating them can help you overcome all sorts of"
      + " obstacles by way of the useful properties they bestow"
      + " on the body (similar to buffs in other games.) By"
      + " training this skill, you will be better able to find"
      + " and identify herbs in the wilderness.");
    return "";
} /* herbalism_answer */


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
 * Function name:       magic_answer
 * Description  :       response to an add_ask
 */
public string
magic_answer()
{
    command("say Swinging swords and climbing hills aren't the only"
      + " ways to accomplish things. The arcane art of magic and casting"
      + " spells is a powerful ally to those who take the time to"
      + " study with trainers such as myself.");
    return "";
} /* magic_answer */


/* 
 * Function name:        return_object
 * Description  :        have npcs give things they are given back
 *                       to players
 * Arguments    :        object obj - the object given
 *                       object to  - the player who gave it
 */
public void
return_object(object obj, object to)
{
    if (obj->id("_tutorial_letter"))
    {
        set_alarm(0.5, 0.0, &react_letter(obj, to));
        return;
    }

    command("say Thanks, but I don't think I need that.");
    command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
    if (environment(obj) == this_object())
    {
       command("drop " + OB_NAME(obj));
    }
} /* return_object */


/*
 * Function name:        react_letter
 * Description  :        have the npc respond to a specific object
 */
public void
react_letter(object obj, object to)
{
    object  potion;

    set_this_player(to);

    if (!CHECK_TUTORIAL_BIT(POTION2_BIT))
    {
        if (CHECK_TUTORIAL_BIT(POTION_BIT))
        {
            command("say What happened? Did you lose the one I gave you?");
            command("sigh");
            command("say Very well, here is another. Try not to lose it!");
        }
        else
        {
            command("emote reads the crumpled letter.");
            command("ponder");
            command("emote closes her eyes in concentration.");
            command("emote waves her arms. Fire explodes from her"
              + " hands!");
            command("say Here, take this. Give it to the Farmer's Wife.");
        }

        potion = clone_object(OBJ_DIR + "potion");
        potion->move(this_object());
        command("give " + OB_NAME(potion) + " to "
          + this_player()->query_real_name());

        SET_TUTORIAL_BIT(POTION_BIT);
        obj->remove_object();
        return;
    }

    command("say This note is out of date. The Farmer's Wife already"
      + " has the potion I gave you.");
    obj->remove_object();
    return;
} /* react_letter */
