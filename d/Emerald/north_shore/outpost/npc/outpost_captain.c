/*
 *  /d/Emerald/north_shore/outpost/npc/outpost_captain.c
 *
 *  This is the Captain of the North Shore outpost. He is rather
 *  tough, and will be part of a small tour quest for Telberin.
 *
 *  Copyright (c) August 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/telberin/npc/telberin_guard";

#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

/* prototypes */
public void        react_intro(object tp);
public void    rillian_answer();


void 
create_guard() 
{
    set_living_name("markul");
    set_name("markul");
    add_name( ({ "captain", "markul attada" }) );
    set_adj( ({ "haggard", "war-torn" }) );
    add_adj( ({ "outpost" }) );

    set_title("Attada, Captain of the North Shore Outpost");

    set_short("haggard war-torn elf");
    set_long("This elf is an unmistakable leader of many. His size"
      + " and stature alone would be enough to strike fear into most"
      + " enemies, and yet it is his eyes that you most notice. They"
      + " burn with fire and purpose, almost as one who knows that"
      + " death is near, and yet wills to face it. He looks grim,"
      + " indeed.\n");

    config_guard(160);

    set_act_time(7);
    add_act("emote peers grimly out of the windows.");
    add_act("emote mutters: How can I be expected to hold this outpost"
      + " under such circumstances?");
    add_act("emote says: Surely there will be word from the City soon.");
    add_act("emote peers briefly at a few things on the desk, and"
      + " then returns to his vigil at the window.");
    add_act("emote paces slowly back and forth, his eyes downcast.");
    add_act("emote says: They will return for another attack soon,"
      + " I am sure of it. How much longer can we hold out?");

    set_cact_time(4);
    add_cact("emote shouts: Your blood shall soon stain this floor"
      + " as well, fool!");
    add_cact("emote cries: Attackers within the complex! To arms!"
      + " To arms!");
    add_cact("emote peers at you with grim determination.\n");
    add_cact("emote snarls: We've stood our ground against worse"
      + " than the likes of you!");


    add_prop(LIVE_I_NO_CORPSE, 1);

    add_ask( ({ "rillian" }),
        VBFC_ME("rillian_answer"));

    arm_me();
}

void
arm_me()
{
    setuid();
    seteuid(getuid());
    add_equipment(OUTPOST_WEP_DIR + "magic_sabre");
    add_equipment(OUTPOST_ARM_DIR + "plate");
    add_equipment(OUTPOST_ARM_DIR + "shield");

    if (!random(3))
    {
        add_equipment("/d/Genesis/gems/obj/diamond");
    }
}


/*
 * Function name: notify_death
 * Description:   Notify onlookers of my death,
 *                though in this case, we do not want a death,
 *                but merely a defeat.
 * Arguments:     object killer - the object that killed me
 */
public void
notify_death(object killer)
{
    if (environment(this_object())->id("_north_shore_outpost_hq"))
    {
        tell_room(environment(this_object()), 
            QCTNAME(this_object()) + " cries out: Foul servants"
              + " of darkness, you'll not take me! I must warn"
              + " the city of your terrible deeds!\n"
              + QCTNAME(this_object()) + " casts aside his"
              + " arms and dives through the southern window.\n");

        environment(this_object())->trigger_escape();
    }
    else
    {
        tell_room(environment(this_object()),
            QCTNAME(this_object()) + " cries out: Telberin will"
              + " know of your deeds, foul servant of Darkness!\n"
              + QCTNAME(this_object()) + " casts aside his arms"
              + " and dashes away!\n");
    }

    if (living(killer))
    {
        tell_object(killer, 
            "You defeated " + query_the_name(this_object()) + ".\n");
        tell_room(environment(this_object()),  QCTNAME(killer) + 
            " defeated " +  query_objective() + ".\n",
           ({ this_object(), killer }));
    }
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
} /* react_intro */


/*
 * Function name:       rillian_answer
 * Description  :       response to an add_ask
 */
public string
rillian_answer()
{
    command("say What? Rillian? What are you talking about?");
    command("ponder");
    command("say Come to think of it, a young lad by that name"
      + " did come over with a garrison quite a long time"
      + " ago. I'd completely forgotten about it, what with all"
      + " of our hardships here.");
    command("say He spent a few nights here in the outpost and"
      + " then took a few weeks worth of food and supplies with"
      + " him. He disappeared into the forest north of the"
      + " dock and we never saw him again.");
    command("say I always assumed that he had returned via"
      + " the ferry on his own. Perhaps he did not survive the"
      + " wilds. I must say he had a green look about him.");
    command("say Alas, I have no more time to discuss this matter."
      + " We are under terrible pressure here, and I must"
      + " return to my duties.");
    return "";
} /* rillian_answer */
