#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/ship/captain.c";

#include "/d/Gondor/defs.h"

#define TICKET  (SHIP_DIR + "ticket4")
#define PRICE   30

static void
create_gondor_captain()
{
    set_name("serkenen");
    set_living_name("serkenen");
    set_race_name("human");
    add_adj("weather-beaten");
    add_adj("one-eyed");
    set_title("the Corsair");

    set_alignment(-250);

    set_chat_time(12);
    add_chat("Business is bad nowadays, there are not many merchantmen sailing anywhere.");
    add_chat("We have to chance upon not meeting the Gondorian navy today.");
    add_chat("The Haradrim give no quarter, but luckily, they don't have many ships.");
    add_chat("There's hardly any ship sailing up the Gwathlo these days.");
    add_chat("I wish I were back at Umbar!");
    add_chat("Sometimes, I think there are more corsairs on the seas than merchantmen.");
    add_chat("I wonder how long before the war breaks out.");
    add_chat("I've heard talk that the Dark Lord is capturing ships to increase His navy.");
    add_chat("Since Ithilien has fallen to the Lord of Morgul, it isn't even safe for us any more!");
    add_chat("One day, I'll retire in Umbar.");
    add_chat("Umbar is a beautiful place, very peaceful, comfortable to live in.");
    add_chat("Without any traders to capture, we have to take on paying passengers. "+
        "It's a mean world for a hard working corsair!");
    add_chat("The inn in Vingaard Keep is a good place to get drunk, if they only had decent drinks there!");
    set_cchat_time(11);
    add_cchat("Hey! Are you one of the cursed rangers??!");
    add_cchat("Stop it, you pestering dog!");
    add_cchat("I fear noone but the Dark Lord!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylights out of you!");
    add_cchat("Right! I'm really gonna stump you this time!");
    add_cchat("Give it to me, big-nose!");
    add_cchat("I'm gonna smack you so hard....");

    add_ask(({"inn","palanthas"}),
	    "say Oh, I believe the proprietor is having trouble to organize " +
	    "enough supplies for his inn.",1);

    set_ticket(TICKET);
    set_price(PRICE);

    set_harbour("Tharbad in Gondor");
    set_target("Kalaman");
}

/* 
 * Solamnian knights prestige 
 */
public int query_knight_prestige() { return 100; }

