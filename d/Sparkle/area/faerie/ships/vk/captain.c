#pragma save_binary
#pragma strict_types

#include "defs.h"
#include <filter_funs.h>

inherit SHIP_CAPT_BASE;

#define TICKET  (VK_SHIP_DIR + "ticket")
#define PRICE   30

static void
create_faerie_captain()
{
    set_name("vilik");
    add_name("sailor");
    set_living_name("vil'ik");
    set_race_name("human");
    add_adj("proud");
    add_adj("old");
    set_title("the Captain of the Seas");

    set_chat_time(15);
    add_chat("Those elves are mysterious creatures.");
    add_chat("They say that sea creatures are rampant in the oceans.");
    add_chat("I've seen dragons fly overhead while sailing.");
    add_chat("The sea is a wonderful place to spend time.");
    add_chat("Sailing the open sea is one of my favorite past times.");
    add_chat("Be careful when you leave the ship.");
    add_chat("When in Faerie, be sure to visit Menerial, the Chief Delegate. " +
        "He may need help.");
    add_chat("I have heard orcs are slowly moving into Faerie.");

    set_cchat_time(11);
    add_cchat("Hey! What I've done to you???!");
    add_cchat("Begone, foul dog!");
    add_cchat("Bring it on, you scabrous traitor!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylights out of you!");
    add_cchat("Right! I'm really gonna stump you this time!");
    add_cchat("You won't live to tell anyone about this.");

    set_ticket(TICKET);
    set_price(PRICE);

    set_harbour("Faerie");
    set_target("Vingaard Keep Port");
}

/*
 * Function name: init_living
 * Description:   The normal init_living
 */
void
init_living()
{
    ::init_living();
    
    if (ticket)
    {
        add_action(buy, "buy");
    }
}
