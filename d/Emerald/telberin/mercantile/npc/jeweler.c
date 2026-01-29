/*
 *  /d/Emerald/telberin/mercantile/npc/amshal.c
 *
 *  This is the Jeweller and Goldsmith of the Jeweller's
 *  Shop in Telberin.
 *
 *  Copyright (c) July 2003, by Cooper Sherry (Gorboth)
 *
 *  Note: some of the credit for the emotes should go to
 *        the original coder of
 *        /d/Emerald/telberin/mercantine/gem_shop/gem_trader
 *        I normally wouldn't steal emotes. But these were
 *        so good, I figured they deserved to be in the game.
 *        Very nicely imagined, whoever created them -
 *        thank you!
 */
#pragma strict_types

inherit "/d/Emerald/telberin/npc/telberin_elf";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

#define SAW_TORQUE_PROP    "_telberin_jeweler_saw_torque"

/* Prototypes */
public void        torque_reaction(object who);



/*
 * Function name:        create_telberin_elf
 * Description  :        set up the elf
 */
public void
create_telberin_elf()
{
    set_living_name("amshal");
    set_name("amshal");
    add_name("inhuin ralei");
    add_name( ({ "shopkeeper", "jeweler", "jeweller", "goldsmith", }) );
    set_adj( ({ "well-dressed", "silver-haired" }) );

    set_short("well-dressed, silver-haired elf");
    set_title("Fendant, Goldsmith of the Telberin Merchants"
            + " Guild");

    set_long("This is clearly an elf who feels that wealth is"
      + " a matter not to be hidden away. Dressed from head"
      + " to toe in beautiful clothing lined with silver and"
      + " gold, he wears many jewels - some on his hands,"
      + " many on his neck, and even a few on the buckles"
      + " of his shoes.\n");

    config_elf(70);  /* The guy stares at jewels all day */

    set_act_time(20);
    add_act("methodically polishes the glass surface of the"
      + " jewel case, taking care to remove all smudges.");
    add_act("emote removes a gem from the case, and carefully"
      + " polishes it with a piece of cloth.");
    add_act("emote fishes a loupe from one of his pockets and"
      + " studies a gemstone through it.");
    add_act("emote stares contentedly around the room.");
    add_act("emote places a big gem on one of the scale pans. " +
        "He grins with joy when the scale pan drops to the counter with " +
        "with a rather loud clang.");

    set_cact_time(10);
    add_cact("emote tries desparately to avoid your attacks.");
    add_cact("emote peers at you in fear and anger.");
    add_cact("shout I need assistance! Some fool has attacked me!");
    add_cact("emote shrieks: Villain! You'll not have my gemstones!"); 

    set_job_response("Why, I am a master jeweler, and merchant of fine"
      + " gems. Please, look around!");
}


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
        command("say Yes, what's that? Who's there?");
        return;
    }

    command("introduce me");

    ::react_intro(tp);
} /* react_intro */


/*
 * Function name:        react_torque
 * Description  :        Players who have the torque get a reaction
 *                       out of this guy.
 */
public void
react_torque(object who)
{
    if (who->query_prop(SAW_TORQUE_PROP))
    {
        return;
    }

    if (!CAN_SEE(TO, who))
    {
        return;
    }

    if (!present("ctower_torque", who))
    {
        return;
    }

    command("gasp");
    set_alarm(2.0, 0.0, &torque_reaction(who));

    return;
} /* react_torque */

void
init_living()
{
    ::init_living();

    set_alarm(1.0, 0.0, "react_torque", this_player());
}


/*
 * Function name:        torque_reaction
 * Description  :        have there be various reactions to the 
 *                       torque so it doesn't get old so fast
 */
public void
torque_reaction(object who)
{
    string   str;

    switch(random(4))
    {
        case 0:
            str = "That torque is simply the most glorious piece"
                + " of jewelry I've ever had the pleasure of gazing"
                + " upon!";
            break;
        case 1:
            str = "That ... that torque ... beautiful beyond words!";
            break;
        case 2:
            str = "God of Light! Never in my life have I seen anything"
                + " so radiant as that torque you bear!";
            break;
        case 3:
            str = "The ... the beauty ... the singular splendour ..."
                + " ... that torque ... I find myself at a loss for"
                + " words!";
            break;
        case 4:
            str = "Many beautiful things have I seen in this"
                + " shop ... but none so dazzling as that jeweled"
                + " torque you carry!";
            break;
        default: 
            str = "Light above us! That torque is simply magnificent!";
            break;
    }

    command("say to " + who->query_real_name() + " " + str);
    who->add_prop(SAW_TORQUE_PROP, 1);

    return;
} /* torque_reaction */
