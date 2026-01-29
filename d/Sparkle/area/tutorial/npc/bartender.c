 /*
 *  /d/Sparkle/area/tutorial/npc/bartender.c
 *
 *  This npc is located in the Greenhollow tavern. He will
 *  respond to questions about the drinks on the menu.
 *
 *  Location: /d/Sparkle/area/tutorial/silverdell/inn.c
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
public void    ale_answer();
public void    wine_answer();
public void    whiskey_answer();
public void    drinking_answer();
public void    menu_answer();
public void    tavern_answer();



/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("Garg");
    set_name("garg");
    add_name( ({ "garg anklebarn", "_silverdell_bartender",
                 "bartender", "barkeeper", "barkeep" }) );
    set_adj( ({ "loud", "muscular", }) );
    set_race_name("goblin");

    set_title("Anklebarn, Bartender of the Red Weasel Tavern");

    set_long("This is the bartender of the Red Weasel Tavern."
      + " He saunters back and forth behind the bar getting"
      + " drinks for his customers. You can <ask> him about"
      + " anything on the pricelist.\n");

    default_config_npc(140);  /* He's a beast! */

    set_act_time(2);
    add_act("emote polishes a beer mug.");
    add_act("emote says: What'll it be, there? Y'can"
      + " <ask> me about any of the items on the pricelist.");
    add_act("emote runs a damp cloth over the bar, rubbing"
      + " at a sticky spot.");
    add_act("emote says: Check the tutorial sign, bub.");
    add_act("emote says: Thirsty? I can serve ya up whatever'll"
      + " whet yer whistle! Just <read pricelist> to see what"
      + " I've got.");

    set_job_response("Eh? I serve drinks to the likes of you,"
      + " bub!");

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
        command("say Where'd they get to?");
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
    add_ask( ({ "drink", "drinking", "alcohol", "drinks" }),
        VBFC_ME("drinking_answer"));
    add_ask( ({ "ale", "amber ale", "amber" }),
        VBFC_ME("ale_answer"));
    add_ask( ({ "wine", "barley wine" }),
        VBFC_ME("wine_answer"));
    add_ask( ({ "whiskey", "shot", "shot of whiskey" }),
        VBFC_ME("whiskey_answer"));
    add_ask( ({ "menu", "pricelist" }),
        VBFC_ME("menu_answer"));
    add_ask( ({ "tavern", "bar", "pub", "weasel",
                "red weasel", "here" }),
        VBFC_ME("tavern_answer"));
} /* add_trainer_asks */


/*
 * Function name:       drinking_answer
 * Description  :       response to an add_ask
 */
public string
drinking_answer()
{
    command("say Liquid courage, bub! Liquid courage! You don't"
      + " want to land yourself in a fight without it!");
    return "";
} /* drinking_answer */


/*
 * Function name:       ale_answer
 * Description  :       response to an add_ask
 */
public string
ale_answer()
{
    command("say These here ales are plenty tasty, bub, don't"
      + " doubt that for a minute. They ain't exactly got much"
      + " kick to 'em, though. You'd have to drink upwards of"
      + " ten or more get yerself completely drunk.");
    return "";
} /* ale_answer */


/*
 * Function name:       wine_answer
 * Description  :       response to an add_ask
 */
public string
wine_answer()
{
    command("say Oh yeah! These wines'll have you loopy before"
      + " you know it. Drink three or more of these and you'll"
      + " be happy as a clam!");
    return "";
} /* wine_answer */


/*
 * Function name:       whiskey_answer
 * Description  :       response to an add_ask
 */
public string
whiskey_answer()
{
    command("say Hoo now! Lookin' fer the strong stuff, are ya?"
      + " I'd be surprised if you could even get one of these"
      + " down, but if you do, ye'll be howlin' at the moon"
      + " in no time flat!");
    return "";
} /* whiskey_answer */


/*
 * Function name:       menu_answer
 * Description  :       response to an add_ask
 */
public string
menu_answer()
{
    command("say Yep, its right here, bub. Just <exa pricelist>"
      + " to see what I can get'cha.");
    return "";
} /* menu_answer */


/*
 * Function name:       tavern_answer
 * Description  :       response to an add_ask
 */
public string
tavern_answer()
{
    command("say I've been workin' in this here pub ever since"
      + " Lars brought me to Greenhollow.");
    return "";
} /* tavern_answer */
