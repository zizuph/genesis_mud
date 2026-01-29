/*
 *  /d/Sparkle/area/tutorial/npc/bar_patron2.c
 *
 *  This npc is located in the side room to the Red Weasel
 *  Tavern in Greenhollow. He is intended to teach players about
 *  itroductions.
 *
 *  Location: /d/Sparkle/area/tutorial/silverdell/tavern2.c
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
public void    tavern_answer();
public void    drinking_answer();
public void    intro_answer();
public void    stanley_answer();



/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("Jack");
    set_name("jack");
    add_name( ({ "jack farspitter", "patron", "_patron_2" }) );
    set_adj( ({ "charming", "thick-bearded" }) );
    set_race_name("dwarf");

    set_title("Farspitter, Regular Patron of the Red Weasel");

    set_long("This dwarf seems like a fun fellow. His beard is thick"
      + " and he is always smiling and laughing. He'd probably like"
      + " to know your name. You can <introduce myself> and he'll"
      + " tell you who he is.\n");

    default_config_npc(50);  /* medium sized */

    set_act_time(2);
    add_act("emote smiles at you and invites you to have a drink.");
    add_act("emote booms: Looks like we have a new friend here,"
      + " Stanley!");
    add_act("emote laughs loudly, pounding the table with his fist.");
    add_act("emote calls: Bartender! We could use another round!");
    add_act("emote drinks a mug of amber ale.");

    set_job_response("My job? Well, I suppose I'm here to keep an eye"
      + " on Stanley ... isn't that right Stanley!");

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
        command("say Where'd they go now?");
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
    add_ask( ({ "here", "bar", "tavern", "weasel", "red weasel" }),
        VBFC_ME("tavern_answer"));
    add_ask( ({ "drink", "drinking", "beer", "ale", "champion",
                "champion ale drinker", "ale drinker",
                "drinking champion", "ale drinking champion" }),
        VBFC_ME("drinking_answer"));
    add_ask( ({ "intro", "introduction", "introductions" }),
        VBFC_ME("intro_answer"));
    add_ask( ({ "stanley", "friend", "best friend", "stan" }),
        VBFC_ME("stanley_answer"));

} /* add_trainer_asks */


/*
 * Function name:       tavern_answer
 * Description  :       response to an add_ask
 */
public string
tavern_answer()
{
    command("say Hmm? The Red Weasel? Oh, this is a great place to come"
      + " and have a few drinks. Try the Ale!");
    return "";
} /* tavern_answer */


/*
 * Function name:       drinking_answer
 * Description  :       response to an add_ask
 */
public string
drinking_answer()
{
    command("say You'll never outdrink old Stanley here ... he's the"
      + " Tavern drinking champion!");
    return "";
} /* drinking_answer */


/*
 * Function name:       stanley_answer
 * Description  :       response to an add_ask
 */
public string
stanley_answer()
{
    command("say Stanley might be a bit of a drunk, but he's got a"
      + " heart of gold. I try to keep an eye on him.");
    command("cry");
    return "";
} /* stanley_answer */


/*
 * Function name:       intro_answer
 * Description  :       response to an add_ask
 */
public string
intro_answer()
{
    command("say Just type <introduce myself> to tell us all your name.");
    return "";
} /* intro_answer */

