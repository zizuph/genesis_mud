/*
 *  /d/Sparkle/area/tutorial/npc/gen_merchant.c
 *
 *  This npc is located in the General Store of Greenhollow.
 *  She'll answer questions about general supplies.
 *
 *  Location: /d/Sparkle/area/tutorial/town/general_store.c
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
public void    supplies_answer();
public void    light_answer();
public void    pack_answer();



/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("Posie");
    set_name("posie");
    add_name( ({ "posie shimmerbrook", "merchant", "shopkeeper",
                 "keeper",
                 "_silverdell_general_shopkeeper" }) );
    set_adj( ({ "bright", "cheerful" }) );
    add_adj( ({ "shop" }) ); /* for "exa shop keeper" */
    set_race_name("hobbit");
    set_gender(G_FEMALE);

    set_title("Shimmerbrook, Supplies Merchant of Greenhollow");

    set_long("This cheerful hobbit is here to help you buy or sell"
      + " any general supplies you might need for your journeys.\n");

    default_config_npc(15);  /* A pipsqueak! */

    set_act_time(2);
    add_act("emote fusses around the shop, tidying up.");
    add_act("emote says: Need any supplies? Feel free to"
      + " <ask> me about any of the wares I sell.");
    add_act("emote says: You just never know when you are going to"
      + " need a good torch or lamp!");
    add_act("emote says: Don't forget to read the tutorial"
      + " signs!");
    add_act("emote says: Are you looking for armours or weapons? If so,"
      + " talk to my associates to the north and west!");

    set_job_response("I'm a merchant! I sell general supplies.");

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
    add_ask( ({ "supplies", "general supplies", "wares" }),
        VBFC_ME("supplies_answer"));
    add_ask( ({ "torch", "torches", "lamp", "lamps", "oil",
                "flask", "flasks", "flask of oil", "oil flask",
                "oil flasks", "flasks of oil" }),
        VBFC_ME("light_answer"));
    add_ask( ({ "pack", "packs", "backpack", "backpacks", "bag",
                "bags" }),
        VBFC_ME("pack_answer"));

} /* add_trainer_asks */


/*
 * Function name:       supplies_answer
 * Description  :       response to an add_ask
 */
public string
supplies_answer()
{
    command("say General supplies are the sorts of things which help you"
      + " get your adventuring done right! Dark cave? Can't see? Better"
      + " buy a torch! Tired, can't carry enough? Purchase a backpack!");
    return "";
} /* supplies_answer */


/*
 * Function name:       light_answer
 * Description  :       response to an add_ask
 */
public string
light_answer()
{
    command("say Trying to get around in dark areas is no fun. Torches"
      + " solve the problem, but they burn out pretty quickly. Spend"
      + " a bit more money on a lamp and a few flasks of oil, and you can"
      + " adventure in the dark for hours.");
    return "";
} /* light_answer */


/*
 * Function name:       pack_answer
 * Description  :       response to an add_ask
 */
public string
pack_answer()
{
    command("say Backpacks are great! They let you carry quite a bit"
      + " more than your strength would normally allow.");
    return "";
} /* pack_answer */

