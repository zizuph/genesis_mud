/*
 *  /d/Sparkle/area/city/npc/innkeeper.c
 *
 *  Hvaeni is the Innkeeper at the Silver Swan Inn in
 *  Sparkle.
 *
 *  Location: /d/Sparkle/area/city/rooms/inside/inn.c
 *
 *  Copyright (c) April 2003, by Cooper Sherry (Gorboth)
 * 
 *  Originally used as the innkeeper for this same establishment in
 *  Telberin in Emerald, but moved to be used in the Hub, since Telberin
 *  is essentially a dead zone. (Gorboth, April 2011)
 */
#pragma strict_types
#include "/d/Sparkle/lib/defs.h"

inherit "/d/Sparkle/area/city/npc/sparkle_npc";
inherit "/d/Genesis/lib/intro";
inherit "/d/Sparkle/lib/quest_reward";
inherit S_LIB_CLOCK;

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>


/* prototypes */
public void    create_sparkle_npc();
public void    introduce(object who);
public void    react_intro(object tp);


/*
 * Function name:        create_telberin_elf
 * Description  :        set up the npc
 */
public void
create_sparkle_npc()
{
    set_living_name("hvaeni");
    set_name("hvaeni");
    add_name( ({ "innkeeper", "keeper" }) );
    add_name("hvaeni metrius");
    add_adj( ({ "proud", "well-dressed" }) );

    set_race_name("elf");

    set_title("Metrius, Innkeeper of the Silver Swan");

    set_short("proud, well-dressed elf");
    set_long("This proud elf looks quite pleased. He appears to"
      + " take pride in his work and his surroundings.\n");

    set_stats( ({ 80, 130, 100, 150, 150, 110 }) ); /* Typical elf. */
    set_alignment(500); /* A pleasant fellow. */

    set_act_time(20);
    add_act("emote polishes the counter with a clean white rag.");
    add_act("emote turns to the menu, and wipes a smudge off its"
          + " side.");
    add_act("emote looks around and smiles.");
    add_act("emote mumbles: I wonder if we have enough venison"
          + " for the rest of the night.");
    add_act("emote tidies up behind the counter.");
    add_act("say In Telberin we never had this many customers ...");

    set_cact_time(10);
    add_cact("emote tries desperately to avoid your attacks.");
    add_cact("emote peers at you in fear and anger.");
    add_cact("shout I need assistance! Some fool has attacked me!");
    add_cact("emote searches madly in his apron for something to"
           + " fight you with.");

    remove_prop(LIVE_I_NEVERKNOWN);

    add_prop(OBJ_M_NO_ATTACK, "A strange force seems to stay your hand."
      + " As you look up, you notice the inkeeper peering at you with"
      + " a knowing sneer.\n");

    set_skill(SS_UNARM_COMBAT, 20);      /* Just a bit here ...       */
    set_skill(SS_AWARENESS, 50);         /* His job calls for it.     */
    set_skill(SS_LANGUAGE, 80);          /* He's been around. */

    add_ask( ({ "inn", "silver swan", "the silver swan",
                "silver swan inn", "the silver swan inn" }),
        "say The Silver Swan was known as the finest Inn in Telberin for"
      + " many generations. Unfortunately, that city no longer provides"
      + " enough customers, so I have moved the business here to"
      + " Sparkle.", 1);
    add_ask( ({ "telberin" }),
        "say Telberin is the Jewel of all Emerald! Have you never visited?"
      + " You should!", 1);
    add_ask( ({ "emerald" }),
        "say Emerald is the most beautiful of all the lands in Genesis."
      + " You should visit it someday.", 1);
    add_ask( ({ "room" }),
        "say Just <read> the menu, friend.", 1);
    add_ask( ({ "lemon", "lemons" }),
        "say Lemons? Hmmm ... well, I know some places use them as a"
      + " garnish for ice-water. But here we use mint, sorry.", 1);

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    setuid();
    seteuid(getuid());
} /* create_sparkle_npc */


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
        command("say Yes, what's that? Who's there?");
        return;
    }

    command("introduce me");
} /* react_intro */


/*
 * Function name:        intro_check
 * Description  :        Lets shorten the spam by having him intro if
 *                       the player doesn't know him yet.
 * Arguments    :        object who - the player
 */
public void
intro_check(object who)
{
    if (!IN_ARRAY(this_object()->query_real_name(),
         m_indices(who->query_introduced())))
    {
        command("say Ah! I do not believe I have had the pleasure ...");
        command("introduce myself");
    }
} /* intro_check */


/*
 * Function name:        arm_me
 * Description  :        set up the npc with any gear it needs
 */
public void
arm_me()
{
    object  arm;

    arm = clone_object("/d/Sparkle/area/orc_temple/wep/crude_dagger");
    arm->set_name("rag");
    arm->set_short("clean white rag");
    arm->set_adj( ({ "clean", "white" }) );
    arm->set_long("It is a bit damp, and smells slightly of lemons.\n");
    arm->move(this_object());

    command("wield all");
} /* arm_me */


/*
 * Function name:       alert_hour_change_hook
 * Description  :       This function gets called whenever the hour
 *                      hour changes in the City of Sparkle
 *                      NPCs can use this to act upon the hour,
 *                      to provide the semblance of a daily routine.
 *                      In the case of the enchanter, we use this to
 *                      trigger his acts, rather than using add_act().
 * Arguments    :       hour - current hour in Sparkle time
 */
public void
alert_hour_change_hook(int hour)
{
    if (is_busy())
    {
        /* Don't participate in routines when interacting. */
        return;
    }

    switch(hour)
    {
        case 20:
            command("stretch");
            command("say Ah, the hour is late. No matter ... I must not"
              + " leave my station.");
            break;
        default:
            break;
    }

    return;

} /* alert_hour_change_hook */


/* 
 * Function name:       job_answer
 * Description  :       response to add_ask
 */
public string
job_answer()
{
    command("say I am the keeper of the Silver Swan Inn. I've been"
      + " doing this for years now.");
    return "";
    
} /* job_answer */