/*
 *  /d/Sparkle/area/tutorial/npc/arm_merchant.c
 *
 *  This npc is located in the Armour Shop of Silverdell.
 *  He'll answer questions about the armours he sells.
 *
 *  Location: /d/Sparkle/area/tutorial/silverdell/armour_shop.c
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
public void    armours_answer();
public void    helm_answer();
public void    vest_answer();
public void    bracers_answer();
public void    greaves_answer();
public void    shield_answer();



/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("Foorman");
    set_name("foorman");
    add_name( ({ "foorman deepdweller", "merchant", "shopkeeper",
                 "keeper", "smith", "armourer",
                 "_silverdell_armour_shopkeeper" }) );
    set_adj( ({ "stoic", "dark-bearded" }) );
    add_adj( ({ "shop", "armour", "armours" }) );
    set_race_name("dwarf");

    set_title("Deepdweller, Armourer of Silverdell");

    set_long("This dwarf seems to take his work very seriously. He will"
      + " do trade in any armours you might need for your journeys.\n");

    default_config_npc(90);  /* A sturdy fellow */

    set_act_time(2);
    add_act("emote quietly takes stock of his wares.");
    add_act("emote says: Do you wish to buy or sell armours?");
    add_act("emote says: Armours can help you stay alive in a fight,"
      + " you know.");
    add_act("emote says: Don't forget to read the tutorial"
      + " signs!");
    add_act("emote says: If you happen to need weapons, or general"
      + " supplies, I'm afraid you'll have to do business through"
      + " that door to the east.");

    set_job_response("I'm a merchant. I buy and sell armours.");

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
    add_ask( ({ "armour", "armours", "protective clothing" }),
        VBFC_ME("armours_answer"));
    add_ask( ({ "helm", "helms", "helmet", "helmets", "head",
                "leather helm", "studded-leather helm" }),
        VBFC_ME("helm_answer"));
    add_ask( ({ "vest", "vests", "leather vest",
                "studded-leather vest" }),
        VBFC_ME("vest_answer"));
    add_ask( ({ "bracers", "leather bracers", "arm", "arms",
                "studded-leather bracers" }),
        VBFC_ME("bracers_answer"));
    add_ask( ({ "greaves", "leather greaves", "leg", "legs",
                "studded-leather greaves" }),
        VBFC_ME("greaves_answer"));
    add_ask( ({ "shield", "shields", "wood shield", "wooden shield",
                "sturdy shield", "sturdy wooden shield" }),
        VBFC_ME("shield_answer"));

} /* add_trainer_asks */


/*
 * Function name:       armours_answer
 * Description  :       response to an add_ask
 */
public string
armours_answer()
{
    command("say Wearing armours prevents your opponents from doing as"
      + " much damage to you in combat. In effect, they help you last"
      + " longer in a fight.");
    return "";
} /* armours_answer */


/*
 * Function name:       helm_answer
 * Description  :       response to an add_ask
 */
public string
helm_answer()
{
    command("say Helmets and helms protect the wearer's head from"
      + " damage.");
    return "";
} /* helm_answer */


/*
 * Function name:       vest_answer
 * Description  :       response to an add_ask
 */
public string
vest_answer()
{
    command("say Vests cover the torso of your upper body, protecting"
      + " your vital organs from harm.");
    return "";
} /* vest_answer */


/*
 * Function name:       bracers_answer
 * Description  :       response to an add_ask
 */
public string
bracers_answer()
{
    command("say Bracers protect the forearm and wrist. They are"
      + " of secondary importance to vests and helms, but good for"
      + " the warrior who wants complete protection.");
    return "";
} /* bracers_answer */


/*
 * Function name:       greaves_answer
 * Description  :       response to an add_ask
 */
public string
greaves_answer()
{
    command("say Wearing greaves will protect your lower legs"
      + " from harm.");
    return "";
} /* greaves_answer */


/*
 * Function name:       shield_answer
 * Description  :       response to an add_ask
 */
public string
shield_answer()
{
    command("say Shields are powerful tools of protection. If you are"
      + " wielding a one-handed weapon, your off hand can comfortably"
      + " hold a shield, giving you a good deal of added defence.");
    return "";
} /* shield_answer */
