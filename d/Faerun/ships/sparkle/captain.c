#pragma save_binary
#pragma strict_types

#include "defs.h"
#include "/d/Faerun/defs.h"
#include <filter_funs.h>

inherit SHIP_CAPT_BASE;

#define TICKET  (SPARKLE_DIR + "ticket")

static void
create_faerie_captain()
{
    set_name("waillan");
    add_name("sailor");
    set_living_name("waillan");
    set_long("This is the captain of the vessel. He looks like an experienced sea captain and has likely sailed the seas for many years. However, the captain looks clean shaven and very neat, which is unusual for someone who spends his lifetime on a ship.\n");
    set_race_name("human");
    add_adj("proud");
    add_adj("clean-shaven");

    set_chat_time(15);
    add_chat("The 'Sea Sprite' is the scourge of all smugglers.");
    add_chat("One day Captain Deudermont will meet his fate!");
    add_chat("The open sea has been rocky the last few days.");
    add_chat("I can outrun any ship chasing me!");
    add_chat("No one has been able to catch me.");
    add_chat("Be careful when you board or leave the ship.");
    add_chat("All my trading is legal, or that's what I tell the Lords " +
        "of Luskan.");

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
