/*
 *	/d/Gondor/common/ship/captain1.c
 *
 *	Dirhavel, the captain of the ship from 
 *	Pelargir to Sparkle
 *
 *	Modification log:
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/ship/captain.c";
inherit "/d/Gondor/common/ship/pel_tours.c";

#include "/d/Gondor/defs.h"

#define TICKET (SHIP_DIR + "ticket")
#define PRICE  30

public void
create_gondor_captain()
{
    set_name("dirhavel");
    set_living_name("dirhavel");
    set_race_name("human");
    add_adj("weather-beaten");
    add_adj("rugged");
    set_title("the Seafarer");

    set_chat_time(12);
    add_chat("Hmmph. I think we're behind schedule again.");
    add_chat("We'll have to chance upon not meeting the Corsairs today.");
    add_chat("The Corsairs give no quarter.");
    add_chat("Pelargir is still bustling with activity. Trade is good.");
    add_chat("Sparkle is a nice place, not considering all the rats.");
    add_chat("I heard one of the other traders ran into the Corsairs.");
    add_chat("Umbar is the Haven of the dreaded Corsairs.");
    add_chat("Competition is not hard nowadays.");
    add_chat("I wonder how long before the war breaks out.");
    add_chat("Somebody is opening a route to the Grey Havens I've heard.");
    add_chat("Fair wind today. We should be able to stay on schedule.");
    add_chat("In Minas Tirith, visit Hunthor, the Master of Advice!");
    add_chat("In Pelargir, visit Carastur, the Lord Councillor!");
    add_chat("I've heard the plains of Rohan are orc infested. Stay to the road!");
    add_chat("At the Harlond they tell that armies of orcs and Haradrim have overrun Ithilien.");
    add_chat("In Edoras, look for Elfhelm the Marshal.");
    add_chat("Don't go to Ithilien unless by Leave of the Steward!");
    add_chat("There is a boy in Pelargir named Grub who might need some help.");
    add_chat("I saw a young boy on the Pelargir docks looking for some help.");
    add_chat("I heard the village of Riverstead is being overrun by orcs!");
    set_cchat_time(11);
    add_cchat("Hey! Are you one of the pirates of Umbar??!");
    add_cchat("Stop it, you pestering dog!");
    add_cchat("I fear noone but the Corsairs of Umbar!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylights out of you!");
    add_cchat("Right! I'm really gonna stump you this time!");
    add_cchat("Give it to me, big-nose!");
    add_cchat("I'm gonna smack you so hard....");

    set_up_pelargir_tour();

    set_ticket(TICKET);
    set_price(PRICE);

    set_harbour("Pelargir in Gondor");
    set_target("Sparkle");
}

