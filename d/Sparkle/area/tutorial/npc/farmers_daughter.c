/*
 *  /d/Sparkle/area/tutorial/npc/farmers_daughter.c
 *
 *  This npc is located in the side hayloft of the barn north of
 *  Greenhollow. She is intended to give players a choice between good
 *  and evil.
 *
 *  Location: /d/Sparkle/area/tutorial/farm/hayloft.c
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 *  Updated by Gronkas August 1, 2016 to fix two typos
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
public string  default_answer();
public void    notify_death(object killer);



/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("Annie");
    set_name("annie");
    add_name( ({ "annie brown", "child", "_tutorial_farmers_daughter",
                 "girl" }) );
    set_adj( ({ "innocent", "little" }) );
    set_race_name("human");
    set_gender(G_FEMALE);

    set_title("Brown, the Farmer's Daughter");

    set_short("innocent little girl");
    set_long("There is a spirit and beauty in this young child that you"
      + " find quite extraordinary. She plays with carefree joy among"
      + " the bales of hay, her musical laughter ringing from the rafters"
      + " with each leap and scamper. The sunlight coming through the"
      + " window dances in her auburn hair. Here, truly, is the pure"
      + " image of untarnished innocence.\n");

    default_config_npc(1);  /* Completely vulnerable */
    set_alignment(400);     /* Killing innocents is EVIL */
    set_height_desc("extremely short");
    set_width_desc("lean");

    set_act_time(2);
    add_act("emote shrieks with joy!");
    add_act("emote pauses to look up at you, sunlight glinting in her"
      + " round brown eyes.");
    add_act("emote capers madly about in the hay, giggling all the while.");
    add_act("emote twirls in front of the window like a ballerina.");
    add_act("emote plops down on the ground and grabs her feet.");
    add_act("emote flashes you a daring smile, and leaps into the hay!");
    add_act("emote walks on her tiptoes from one side of the loft to the"
      + " other.");
    add_act("emote sings a childlike song. Her voice is hauntingly"
      + " beautiful.");
    add_act("emote leans out the window and lets the wind catch her hair.");

    set_job_response("What's a job?");

    remove_prop(LIVE_I_NEVERKNOWN);
    add_prop(OBJ_M_NO_ATTACK, 0); /* You can kill her. */
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    add_leftover(OBJ_DIR + "heart", "heart", 1, 0, 0, 1);

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
        command("say Where'd you go?");
        return;
    }

    command("introduce me");
} /* react_intro */


/* 
 * Function name:       default_answer
 * Description  :       we don't want hers to be the same
 */
public string
default_answer()
{
    command("emote listens to the question, but then just giggles"
      + " joyfully and jumps into the hay.");
    return "";
} /* default_answer */


/*
 * Function name: notify_death
 * Description:   Notify onlookers of my death,
 *                we need to set a bit in the killer
 * Arguments:     object killer - the object that killed me
 */
public void
notify_death(object killer)
{
    set_this_player(killer);

    tell_room(environment(this_object()),
        QCTNAME(this_object()) + " slumps to the ground and dies.\n");

    if (living(killer))
    {
        tell_object(killer, 
            "You have slaughtered an innocent child!\n");
        tell_room(environment(this_object()),  QCTNAME(killer) + 
            " slaughtered an innocent child!\n",
           ({ this_object(), killer }));

        if (!CHECK_TUTORIAL_BIT(KILLER_BIT))
        {
            write("Baron von Krolock will be pleased. Now you have but"
              + " to take her heart. This is no different than leftovers"
              + " on a wolf or mountain lion.\n");
            SET_TUTORIAL_BIT(KILLER_BIT);
        }
    }
} /* notify_death */

