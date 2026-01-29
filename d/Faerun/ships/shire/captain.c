#pragma save_binary
#pragma strict_types

#include "defs.h"
#include "/d/Faerun/defs.h"
#include <filter_funs.h>

inherit SHIP_CAPT_BASE;

#define TICKET  (SHIRE_DIR + "ticket")

static void
create_faerie_captain()
{
    set_name("dastrin");
    add_name("captain");
    set_living_name("pirate");
    set_long("This is the captain of the ship. He looks like experienced, but is smelly and unclean. His face is scarred and he has a crokked nose, and he looks like he's spent his life running from the law. The captain probably knows the sea very well, but, looking at him, he doesn't look too trustworthy.\n");
    set_race_name("human");
    add_adj("dirty");
    add_adj("smelly");

    set_chat_time(15);
    add_chat("Curses to Captain Deudemont!");
    add_chat("One day Captain Deudermont will meet his fate!");
    add_chat("I know the sea like I know my own lovers.");
    add_chat("The wide, open sea is beautiful.");
    add_chat("There is no other place I'd rather be than out at sea..");
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
