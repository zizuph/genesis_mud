 /*
 *  /d/Sparkle/area/tutorial/npc/innkeeper.c
 *
 *  This npc is located in the Greenhollow Inn. He will
 *  respond to questions about the food on the menu.
 *
 *  Location: /d/Sparkle/area/tutorial/town/inn.c
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
public void    oats_answer();
public void    soup_answer();
public void    sweetroot_answer();
public void    duck_answer();
public void    venison_answer();
public void    eating_answer();
public void    brother_answer();
public void    menu_answer();



/*
 * Function name:        create_silverdell_npc
 * Description  :        set up the npc
 */
public void
create_silverdell_npc()
{
    set_living_name("Traeni");
    set_name("traeni");
    add_name( ({ "traeni metrius", "_silverdell_innkeeper" }) );
    set_adj( ({ "proud", "well-dressed", }) );
    set_race_name("elf");

    set_title("Metrius, Innkeeper of the Greenhollow Inn");

    set_long("This is the Innkeeper of the Greenhollow Inn. He is"
      + " a very happy looking elf, who obviously loves what"
      + " he does for a living. You can <ask> him about any"
      + " of the items on the menu.\n");

    default_config_npc(100);  /* He's an old elf from Telberin */

    set_act_time(2);
    add_act("emote cheerfully tidies up around the inn.");
    add_act("emote says: I am at your service. Feel free to"
      + " <ask> me about any of the items on the menu.");
    add_act("emote muses to himself: I wonder how my brother"
      + " is doing over in Telberin. It has been too long since"
      + " my last visit.");
    add_act("emote says: Don't forget to read the tutorial"
      + " signs!");
    add_act("emote says: In some inns, you'll be able to rent"
      + " a room for the night. Since you are so close to the"
      + " hilltop here, that isn't really necessary.");

    set_job_response("It is my job to cook meals for the hungry"
      + " citizens of Greenhollow, and travellers like yourself.");

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
    add_ask( ({ "food", "eating" }),
        VBFC_ME("eating_answer"));
    add_ask( ({ "oats", "creamed oats" }),
        VBFC_ME("oats_answer"));
    add_ask( ({ "soup", "onion soup" }),
        VBFC_ME("soup_answer"));
    add_ask( ({ "sweetroot", "root", "baked sweetroot" }),
        VBFC_ME("sweetroot_answer"));
    add_ask( ({ "duck", "roasted duck", "roast", "roast duck" }),
        VBFC_ME("duck_answer"));
    add_ask( ({ "venison", "fillet", "fillet of venison",
                "venison fillet" }),
        VBFC_ME("venison_answer"));
    add_ask( ({ "telberin", "brother", "emerald" }),
        VBFC_ME("brother_answer"));
    add_ask( ({ "menu", "pricelist" }),
        VBFC_ME("menu_answer"));

} /* add_trainer_asks */


/*
 * Function name:       eating_answer
 * Description  :       response to an add_ask
 */
public string
eating_answer()
{
    command("say Food is a very imporant aspect of Genesis. If you"
      + " don't keep your belly full, it takes forever to recover"
      + " from fatigue. You should probably focus on skill training"
      + " with your coins initially, but then be sure to spend a few"
      + " on keeping your belly full, too.");
    return "";
} /* eating_answer */


/*
 * Function name:       oats_answer
 * Description  :       response to an add_ask
 */
public string
oats_answer()
{
    command("say The oats are a delicious little treat. However, on"
      + " an empty stomach it will take you around 20 or more to"
      + " get completely full. You might want something bigger unless"
      + " you aren't very hungry.");
    return "";
} /* oats_answer */


/*
 * Function name:       soup_answer
 * Description  :       response to an add_ask
 */
public string
soup_answer()
{
    command("say Ahhh ... the onion soup is delicious. If you are"
      + " really hungry, you might want something bigger though. On"
      + " an empty stomach, it will take 10 or more soups to fill"
      + " you up.");
    return "";
} /* soup_answer */


/*
 * Function name:       sweetroot_answer
 * Description  :       response to an add_ask
 */
public string
sweetroot_answer()
{
    command("say The sweetroot is like a baked potato, and will fill"
      + " you up fairly quickly. If you eat about 6 or so, you should"
      + " start to feel pretty full.");
    return "";
} /* sweetroot_answer */


/*
 * Function name:       duck_answer
 * Description  :       response to an add_ask
 */
public string
duck_answer()
{
    command("say The duck is simply exquisite! You'll be full in no"
      + " time eating that succulent meat. I'd say 5 or so will do"
      + " you before you start feeling pretty well-fed.");
    return "";
} /* duck_answer */


/*
 * Function name:       venison_answer
 * Description  :       response to an add_ask
 */
public string
venison_answer()
{
    command("say Well, now that is a real meal! I'm not sure if you"
      + " are even hungry enough to eat a single venison. If you want"
      + " to give it a try, be my guest ... you'll be full before you"
      + " can bat an eye!");
    return "";
} /* venison_answer */


/*
 * Function name:       brother_answer
 * Description  :       response to an add_ask
 */
public string
brother_answer()
{
    command("say Hmmm ... ? Oh, yes, I have a brother who runs an inn"
      + " in the city of Telberin in Emerald. You know, it is funny, but"
      + " we learned to cook together, so his menu is nearly identical to"
      + " mine!");
    command("laugh merrily");
    return "";
} /* brother_answer */


/*
 * Function name:       menu_answer
 * Description  :       response to an add_ask
 */
public string
menu_answer()
{
    command("say The menu? Its right here. Just type <read menu> to"
      + " see the different food you can order.");
    return "";
} /* menu_answer */
