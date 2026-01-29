/*
 *  /d/Sparkle/area/tutorial/npc/bar_patron1.c
 *
 *  This npc is located in the side room to the Red Weasel
 *  Tavern in Greenhollow. He is intended to teach players about
 *  itroductions.
 *
 *  Location: /d/Sparkle/area/tutorial/town/tavern2.c
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
public void    jack_answer();
public void    return_object(object obj, object from);
public void    feed_stanley(object ob, object from);



/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("Stanley");
    set_name("stanley");
    add_name( ({ "stanley firebrook", "patron", "_patron_1" }) );
    set_adj( ({ "loud", "intoxicated" }) );
    set_race_name("human");

    set_title("Firebrook, Champion Ale Drinker Three Years Running");

    set_long("The booming voice of this fellow can be heard throughout"
      + " the tavern. Though clearly drunk, he seems perfectly harmless"
      + " and is just having a good time. If you type <introduce myself>"
      + " he will tell you his name.\n");

    default_config_npc(30);  /* Not very tough */

    set_act_time(2);
    add_act("emote claps you on the back, almost knocking you down.");
    add_act("emote bellows: Oye! We've got a n-n-new one 'ere! S-s-say"
      + " there mate ... how's about giving us an introduction?");
    add_act("emote suddenly bursts into riotous laughter!");
    add_act("emote bawls: Hey Jack ... I b-b-bets I can outdrink ya"
      + " again tonight!");
    add_act("emote gets serious suddenly, and says: The Red W-w-weasel"
      + " has b-b-been very good to me.");
    add_act("emote drinks an amber ale.");

    set_job_response("J-j-job? Whasshhhat?");

    remove_prop(LIVE_I_NEVERKNOWN);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

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
        command("say W-w-whasha big idea? Where'd they get to?");
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
                "quest", "task", "help", "favor",
                "drinking champion", "ale drinking champion" }),
        VBFC_ME("drinking_answer"));
    add_ask( ({ "intro", "introduction", "introductions" }),
        VBFC_ME("intro_answer"));
    add_ask( ({ "jack", "friend", "best friend" }),
        VBFC_ME("jack_answer"));

} /* add_trainer_asks */


/*
 * Function name:       tavern_answer
 * Description  :       response to an add_ask
 */
public string
tavern_answer()
{
    command("say Th-th-the Red Weasel is the f-f-finest establishment"
      + " in all of G-G-Greenhollow! Another round, bartender!!");
    return "";
} /* tavern_answer */


/*
 * Function name:       drinking_answer
 * Description  :       response to an add_ask
 */
public string
drinking_answer()
{
    command("say I'm th-th-the drinking CHAMPION! S-s-say ... d'ya want"
      + " do go get me another ale? I'd really ap-ap-appreciate it.");
    return "";
} /* drinking_answer */


/*
 * Function name:       jack_answer
 * Description  :       response to an add_ask
 */
public string
jack_answer()
{
    command("say Jack? Oh, he's prolly my b-b-best friend in the whole."
      + " world. We've been through so many g-g-good times ...\n");
    command("cry");
    return "";
} /* jack_answer */


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
    if (obj->id("drink"))
    {
        set_alarm(0.5, 0.0, &feed_stanley(obj, to));
        return;
    }

    command("say Gee ... th-th-thanks but what I really n-n-need is"
      + " another drink!");
    command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
    if (environment(obj) == this_object())
    {
       command("drop " + OB_NAME(obj));
    }
} /* return_object */


/*
 * function name:        feed_stanley
 * description  :        the reaction when the npc is given a drink
 * arguments    :        object ob -- what the npc was given
 *                       object frm - where it came from
 * returns      :        1
 */
public int
feed_stanley(object ob, object from)
{
    object    sword;

    set_this_player(from);

    command("cheer");
    command("emote raises " + ob->short() + " in a toast.");
    command("emote shouts: To " + capitalize(from->query_real_name())
      + ", my new best friend!");
    command("drink " + ob->query_name());


    /*
     * Note ... I am using the code setup by the tutorial master file
     * here to store a bit which keeps track of whether the player
     * has been given the reward yet. Becuase I am using the code
     * intended mainly for use by the tutorial chapters, the function
     * names seem odd here. I am using the chapter number 1001 since
     * there will not be that many chapters in the tutorial. - Gorboth
     */
    if (!CHECK_TUTORIAL_BIT(STANLEY_BIT))
    {
        command("say You know ... I really d-d-don't think I'll be"
          + " n-n-needing this. Accept it as a t-t-token of my"
          + " appreciation!");

        sword = clone_object(WEP_DIR + "reward_sword");
        sword->move(this_object());
        command("give sword to " + this_player()->query_real_name());
        if (environment(sword) == this_object())
        {
            command("say Hmm, well I-I-I'll j-just drop it here.");
            command("drop sword");
        }
        SET_TUTORIAL_BIT(STANLEY_BIT);
    }
    else
    {
        command("say I w-w-wish I had another sword to give you!");
    }

    return 1;
} /* feed_stanley */


