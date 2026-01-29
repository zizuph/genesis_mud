#pragma save_binary
#pragma strict_types

#include "defs.h"
#include "/d/Faerun/defs.h"
#include <filter_funs.h>

inherit SHIP_CAPT_BASE;

#define TICKET  (FLOTSAM_DIR + "ticket")

static void
create_faerie_captain()
{
    set_name("raylwen");
    add_name("captain");
    set_living_name("trader");
    set_long("This is the captain of the ship. She looks lithe but very muscular. Her commanding presence is evident in her stance as she watches her sailors. Her luxuriant red hair is tied behind her back with a long leather cord.\n");
    set_race_name("human");
    add_adj("lithe");
    add_adj("muscular");

    set_chat_time(15);
    add_chat("Curses to the Palanthian Navy, they stick their noses in everything!");
    add_chat("Those damn pirates makes us have to take the long route.");
    add_chat("If I have to sail one more stinking goblin I am going to toss him overboard!");
    add_chat("Blasted Kender! They cant keep their hands to themselves!");
    add_chat("The open sea is wonderful.");
    add_chat("Be careful when you board or leave the ship.");

    set_cchat_time(11);
    add_cchat("Hey! What have I've done to you???!");
    add_cchat("Begone, foul dog!");
    add_cchat("Bring it on, you scabrous traitor!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylights out of you!");
    add_cchat("Right! I'm really gonna stump you this time!");
    add_cchat("You won't live to tell anyone about this.");

    set_ticket(TICKET);
    set_price(PRICE);

    set_harbour("Faerun");
    set_target("Faerun Port");
    set_gender(G_FEMALE);
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
