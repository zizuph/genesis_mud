/*
 *  /d/Sparkle/area/city/npc/kiki.c
 *
 *  This is Kiki, the Sparkle Bartender's Hellcat. She acts as the
 *  bouncer for the Boar's Head Tavern.
 *
 *  Created August 2018, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../defs.h"


/* Prototypes */
public void        create_monster();
public string      default_answer();
public void        unseen_hook();

/*
 * Function name:        create_monster
 * Description  :        The constructor for the monster
 */
public void
create_monster()
{
    set_race_name("hellcat");
    set_name("kiki");
    add_name( ({ "pet", "cat", "animal", "bouncer" }) );
    add_adj( ({ "massive" }) );

    set_short("massive hellcat");
    set_long("Perched above the bar is one of the largest and most"
      + " terrible looking cats you have ever laid eyes on. Its"
      + " black hair splays out in all directions, making it look"
      + " very fat. White whiskers jut from all angles from her"
      + " furry face which occasionally opens in a yawn filled with"
      + " massive deadly teeth.\n");

    set_gender(G_FEMALE);
    set_default_answer(VBFC_ME("default_answer"));

    set_alignment(0); /* no alignment */
    set_stats( ({ 300, 250, 400, 100, 100, 200 }) ); /* Death Cat! */
                  
    set_skill(SS_AWARENESS,    100);
    set_skill(SS_DEFENCE,      100);
    set_skill(SS_UNARM_COMBAT, 100);

    set_act_time(60);
    add_act("emote purrs loudly.");
    add_act("emote swishes her massive hairy tail back and forth.");
    add_act("emote blinks her huge yellow eyes slowly.");
    add_act("emote twitches her head and goes: \"Prrow!\".");

    set_no_show_composite(1); /* She isn't obviously in the room. */
    set_dont_answer_unseen(1);

    add_prop(OBJ_M_NO_ATTACK, "Just as you begin to make your move,"
      + " the massive hellcat seems to expand in size, rising on her"
      + " legs in a death pose which looms over you. You balk and"
      + " decide that suicide-by-cat is not to your liking.\n");

    setuid();
    seteuid(getuid());
} /* create_monster */


/*
 * Function name:   query_gender
 * Description:     Returns the gender code of the living.
 * Returns:         The code. (0 - male, 1 - female, 2 - netrum)
 */
public int
query_gender()
{
    return G_FEMALE;
}


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    command("emote " + one_of_list( ({
        "seems to consider the question, and then purrs loudly.",
        "makes some strange sounds in her throat.",
        "doesn't answer, but twitches her tail sharply.",
        "blinks slowly and does not answer.",
        "seems nonplussed at the question.",
            }) ));
    return "";
} /* default_answer */


/*
 * Function name: unseen_hook
 * Description:   This function gets called if this mobile couldn't see
 *		  who asked the question and is not supposed to answer
 *		  in that case.
 */
public void
unseen_hook()
{
    command("emote cocks her head, and looks around in confusion.");
    command("emote can't seem to see whoever made that noise.");
} /* unseen_hook */