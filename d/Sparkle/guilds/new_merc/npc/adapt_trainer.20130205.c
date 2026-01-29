/*
 *  /d/Sparkle/guilds/new_merc/npc/adapt_trainer.c
 *
 *  This is the training master for the Free Mercenary Guild. Members can
 *  ask him where to find the right trainer for each of their adaptable
 *  skills.
 *
 *  Created January 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/monster";
inherit "/d/Genesis/lib/intro";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "../merc_defs.h"

/* Prototypes */
public void        create_monster();
public void        introduce(object who);
public void        react_intro(object tp);

/* Global Variables */
public int     *V_Skills = MERC_MASTER->query_skillnum_index();

/*
 * Function name:        create_monster
 * Description  :        set up the npc
 */
public void
create_monster()
{
    int     *v_skills;
    string  *a_map;
    mixed    s_name,
             s_trainer,
             s_desc,
             s_place;

    set_living_name(MERC_SCHOLAR);
    set_name(lower_case(MERC_SCHOLAR));
    add_name( ({ "trainer", "instructor", "teacher", "man" }) );
    set_race_name("human");
    add_adj( ({ "rugged", "impassive" }) );

    set_title("Thalhaussen, Master of Adaptation and Mercenary"
      + " Specialist");

    set_short("rugged impassive human");
    set_long("The man who stands before you has the look of someone who"
      + " has seen many travels, won many contests of blood, and learned"
      + " a great deal. He is scarred, and favors one leg slightly, yet"
      + " the look in his eye commands respect and attention.\n");

    set_stats( ({ 150, 180, 175, 130, 200, 190 }) );
    set_alignment(0); /* Serves no cause but his own. */

    set_act_time(4);
    add_act("emote lifts his cloak and checks the wrapping on his"
      + " thigh.");
    add_act("emote says: The one who would serve no master but himself"
      + " must first become student to every master.");
    add_act("emote says: Ask me about the skill you seek to harness for"
      + " your own purposes.");
    add_act("emote says: I am skilled, yes ... but I am no teacher of"
      + " the various talents of life. You must seek out the true"
      + " masters of these things for your training to begin with me.");
    add_act("emote says: What do I train? Nothing, and yet anything that"
      + " is already within you. My skill is to adapt the training you"
      + " already have to your needs for the day.");
    add_act("emote pauses to adjust the fitting of his sidearm.");

    set_cact_time(4);
    add_cact("shout What treachery is this?! You'll not be so quick"
      + " to dispatch of me!");
    add_cact("emote snarls at you, and springs with a sudden agility"
      + " that belies his age!");
    add_cact("say So! You think you can take this old man?");

    set_default_answer(VBFC_ME("default_answer"));

    remove_prop(LIVE_I_NEVERKNOWN);
    add_prop(OBJ_M_NO_ATTACK, "Noticing the change in your posture, a"
      + " number of Mercenaries on the training yard turn to glare at"
      + " you. Seeing the weapons in their hands and the death in their"
      + " eyes, you decide not to risk it.\n");

    set_skill(SS_WEP_SWORD, 75 + random(25));
    set_skill(SS_WEP_POLEARM, 75 + random(25));
    set_skill(SS_WEP_AXE, 75 + random(25));
    set_skill(SS_WEP_KNIFE, 75 + random(25));
    set_skill(SS_WEP_CLUB, 75 + random(25));
    set_skill(SS_DEFENCE, 75 + random(25));
    set_skill(SS_2H_COMBAT, 75 + random(25));
    set_skill(SS_BLIND_COMBAT, 75 + random(25));
    set_skill(SS_PARRY, 75 + random(25));
    set_skill(SS_DEFENCE, 75 + random(25));

    setuid();
    seteuid(getuid());

    v_skills = MERC_MASTER->query_skillnum_index();
    a_map = MERC_MASTER->query_adapt_map();

    foreach (int v_skill: v_skills)
    {
        s_name = SS_SKILL_DESC[v_skill][0];
        s_trainer = capitalize(a_map[s_name][1]);
        s_desc = a_map[s_name][3];
        s_place = a_map[s_name][2];

        add_ask(s_name, one_of_list(
            ({ "say Learning to " + s_desc + " would indeed serve you"
             + " well. None can teach you better than the master who"
             + " taught me. Seek out " + s_trainer + " " + s_place
             + ".",
               "say " + s_trainer + " ... you must find " + s_trainer
             + ". Search " + s_place + " and then <adapt> the skill"
             + " you seek with this true master of the art.",
               "say If learning to " + s_desc + " is your aim, then you"
             + " must first look for " + s_trainer + " " + s_place
             + ". Do not forget to bring platinum coins!",
               "say Ahh ... yes, I remember when I myself studied how"
             + " to " + s_desc + " with " + s_trainer + "! You will"
             + " need to gather your platinum and seek " + s_place
             + " for this true master of that lore.",
               "say What did you say? " + capitalize(s_name) + "? "
             + " It was a long time ago ... let me try to recall. Ah,"
             + " yes ... " + s_place + " ... I remember now. You must"
             + " go there and learn from " + s_trainer + ".",
               "say " + capitalize(s_name) + ", is it? I almost"
             + " remember enough of that to teach you myself! But"
             + " no ... I will send you to study with the true master, "
             + s_trainer + "! Look " + s_place + ", and do not"
             + " forget your coinpurse!"
            }) ), 1);
    }

    add_ask( ({ "trainers", "master trainer", "master trainers",
                "master", "masters", "skill masters", "skill master" }),
        "say The true masters of any skill must be sought and studied"
      + " under before you can learn to adapt that skill. The masters"
      + " are many, and scattered throughout the realms. Feel free to"
      + " <ask> me about any skill, and I will tell you where to seek"
      + " instruction.", 1);
    add_ask( ({ "skill", "skills" }),
        "say To get a list of your skills, use the <skills> command"
      + " at your leisure. However, to see which skills you have already"
      + " learned to adapt, and those that you yet require training in"
      + " for further adaptability, use the <adapt list> command.", 1);
    add_ask( ({ "adapt", "adaptability", "adaptability skill",
                "adaptation", "adaptation skill" }),
        "say The ability to adapt to the needs of any given moment are the"
      + " hallmark of a worthy Mercenary. Use the <adapt help> command"
      + " for a full explanation.", 1);
} /* create_monster */     


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
        command("say Where'd they go now?");
        return;
    }

    command("introduce me");
} /* react_intro */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    command("smile . "+this_player()->query_real_name());
    command("say Friend, I am here to provide answers to questions"
      + " about the adaptability skill. You can ask me about any skill"
      + " and I will tell you where you can find the master trainer"
      + " of that skill. As a Mercenary, you can type <merchelp adapt>"
      + " to gain full understanding about the ability.");
    return "";
} /* default_answer */