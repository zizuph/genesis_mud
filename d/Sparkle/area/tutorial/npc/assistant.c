/*
 *  /d/Sparkle/area/tutorial/npc/aziz.c
 *
 *  This is the first npc new players will meet in the game. He
 *  is part of the conversation tutorial, and will hand out
 *  coins to players who complete his conversation tree.
 *
 *  Location: /d/Sparkle/area/tutorial/town/road_1.c
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 *
 *  Updated August 2015, by Bart Freeman (Tedare)
 *  Changed the line of questioning to pertain to the main
 *  quest in this area while still teaching conversation skills.
 */
 
#pragma strict_types
#include "../defs.h"

inherit NPC_DIR + "silverdell_npc2";
inherit "/d/Genesis/lib/intro";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>


/* prototypes */
public void    create_silverdell_npc();
public void    introduce(object who);
public void    react_intro(object tp);
public void    add_aziz_asks();
public void    forget_answer();
public int     index;
/* definitions */

#define        QUEST_OFFER      "_rillian_quest_aziz_offer"


/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("aziz");
    set_name("aziz");
    add_name("aziz balank");
    set_adj( ({ "friendly", "young" }) );
    set_race_name("elf");
    add_name("_silverdell_innkeeper");

    set_title("Balank, Unappreciated Wizard's Assistant");

    set_long("A bored look is baked on his face. Laziness"
      + " eminates from his posture.\n");

    default_config_npc(20);  /* We'll make him mildly impressive */
    set_job_response("I do as I'm told.\n");
	add_aziz_asks();

    remove_prop(LIVE_I_NEVERKNOWN);
	add_prop(LIVE_I_ALWAYSKNOWN, 1);
    setuid();
    seteuid(getuid());
} /* create_silverdell_npc */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    command("smile . "+this_player()->query_real_name());
    command("say I don't have much to say about that topic. I'm"
      + " here to help recruit adventurers for the Mayors quest."
      + " The survival of Greenhollow and Silverdell as a whole"
      + " depends on us finding a way to defeat Baron von Krolock"
      + " before he can unleash his demons on us.");
    return "";
} /* default_answer */


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
 * Function name:        add_aziz_asks
 * Description  :        aziz has a dialogue tree
 *                       which can lead to him giving out
 *                       rewards to players who complete it
 */
public void
add_aziz_asks()
{	
	add_ask( ({ "forget me"}),
		VBFC_ME("forget_answer"));
		
} /* add_aziz_asks */

public string
forget_answer()
{
	
        for (index = 0; index < 70; index++) 
		{
			CLEAR_TUTORIAL_BIT(index);
		}
		command("say As you wish!");
 
}




