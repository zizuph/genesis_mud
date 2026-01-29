/*
 *  /d/Sparkle/area/tutorial/npc/wep_merchant.c
 *
 *  This npc is located in the Weapon Shop of Greenhollow.
 *  He'll answer questions about the weapons he sells.
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
public void    weapons_answer();
public void    sword_answer();
public void    axe_answer();
public void    club_answer();
public void    dagger_answer();



/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("Zelnik");
    set_name("zelnik");
    add_name( ({ "zelnik shatterstack", "merchant", "shopkeeper",
                 "keeper", "smith",
                 "_silverdell_weapon_shopkeeper" }) );
    set_adj( ({ "wild-eyed", "fidgeting" }) );
    add_adj( ({ "shop", "weapon", "weapons" }) );
    set_race_name("gnome");

    set_title("Shatterstack, Weapon Smith of Greenhollow");

    set_long("This zaney fellow is here to help you buy or sell"
      + " any weapons you might need for your journeys.\n");

    default_config_npc(44);  /* Not too tiny */

    set_act_time(2);
    add_act("emote buzzes around the shop, messing around with the"
      + " merchandise.");
    add_act("emote says: Need weapons? Ask! Ask! ..."
      + " <ask> me about any of the wares I sell.");
    add_act("emote says: Don't trust your knuckles in a fight!"
      + " Buy a blade! Buy a blade!");
    add_act("emote says: Don't forget to read the tutorial"
      + " signs!");
    add_act("emote says: Need some armour, or general supplies?"
      + " Talk to the other two who sell stuff ... there, through"
      + " that door to the south.");

    set_job_response("I'm a merchant! I buy and sell weapons.");

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
    add_ask( ({ "weapon", "weapons", "blade", "blades" }),
        VBFC_ME("weapons_answer"));
    add_ask( ({ "sword", "swords", "longsword", "shortsword",
                "iron sword", "iron shortsword",
                "steel sword", "steel longsword" }),
        VBFC_ME("sword_answer"));
    add_ask( ({ "axe", "axes", "hatchet",
                "small hatchet", "small axe",
                "heavy axe", "heavy battle-axe", "battle-axe",
                "battleaxe", "heavy battleaxe" }),
        VBFC_ME("axe_answer"));
    add_ask( ({ "club", "clubs", "iron club", "wooden club",
                "wood club" }),
        VBFC_ME("club_answer"));
    add_ask( ({ "dagger", "daggers", "knife", "knives",
                "sharp knife", "dull dagger", "dull knife",
                "sharp dagger" }),
        VBFC_ME("dagger_answer"));

} /* add_trainer_asks */


/*
 * Function name:       weapons_answer
 * Description  :       response to an add_ask
 */
public string
weapons_answer()
{
    command("say Oooo ... ! Trust me! In a fight, you are going to"
      + " want something sharp and swingy! Swords! Axes! Daggers!"
      + " Even a club! They won't know what hit 'em!");
    return "";
} /* weapons_answer */


/*
 * Function name:       sword_answer
 * Description  :       response to an add_ask
 */
public string
sword_answer()
{
    command("say Yes! Yes! Buy a sword! They are the most common"
      + " weapons in Genesis ... long, sharp, easy to love!");
    return "";
} /* sword_answer */


/*
 * Function name:       axe_answer
 * Description  :       response to an add_ask
 */
public string
axe_answer()
{
    command("say An axe? Oh my, a beautiful thing! They swing like"
      + " a club and cut like a sword. What's not to like?!");
    return "";
} /* axe_answer */


/*
 * Function name:       club_answer
 * Description  :       response to an add_ask
 */
public string
club_answer()
{
    command("say Hate the sight of blood? A club does the trick without"
      + " a single cut!");
    return "";
} /* club_answer */


/*
 * Function name:       dagger_answer
 * Description  :       response to an add_ask
 */
public string
dagger_answer()
{
    command("say Knives and daggers are clever little things, aren't"
      + " they? I guess they never really do as much damage as a good"
      + " sword ... but they are just so much fun!");
    return "";
} /* dagger_answer */
