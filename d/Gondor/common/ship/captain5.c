#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/ship/captain.c";
inherit "/d/Gondor/common/ship/pel_tours.c";

#include "/d/Gondor/defs.h"

#define TICKET  (SHIP_DIR + "ticket5")
#define PRICE   28

static void
create_gondor_captain()
{
    set_name("haradacil");
    add_name("sailor");
    set_living_name("haradacil");
    set_race_name("human");
    add_adj("proud");
    add_adj("old");
    set_title("the Merchant Captain");

    set_alignment(240);

    set_chat_time(15);
    add_chat("Hmmph. I think we're behind schedule again.");
    add_chat("Be warned - there are nasty press-gangs in Kabal, and they are known to harass newcomers.");
    add_chat("There is some well-brewed liquor in the liquour booty in Kabal!");
    add_chat("The Kabal port district is a rather dangerous place!");
    add_chat("I doubt the Corsairs will overtake us in this weather!");
    add_chat("The Corsairs give no quarter.");
    add_chat("Minas Tirith is still bustling with activity. Trade is good.");
    add_chat("The city of Kabal is a good place for trade.");
    add_chat("I heard one of the other traders ran into the Corsairs.");
    add_chat("Umbar is the Haven of the dreaded Corsairs.");
    add_chat("Competition is not hard nowadays.");
    add_chat("I wonder how long before the war breaks out.");
    add_chat("Fair wind today. We should be able to make good speed.");
    add_chat("In Minas Tirith, visit Hunthor, the Master of Advice!");
    add_chat("In Pelargir, visit Carastur, the Lord Councillor of the city!");
    add_chat("I've heard the plains of Rohan are orc infested. Stay to the road!");
    add_chat("At the Harlond they tell that armies of orcs and Haradrim have overrun Ithilien.");
    add_chat("In Edoras, look for Elfhelm the Marshal.");
    add_chat("Don't go to Ithilien unless by Leave of the Steward!");
    set_cchat_time(11);
    add_cchat("Hey! Are you one of the pirates of Umbar??!");
    add_cchat("Stop it, you pestering dog!");
    add_cchat("I fear noone but the Corsairs of Umbar!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylights out of you!");
    add_cchat("Right! I'm really gonna stump you this time!");
    add_cchat("Give it to me, big-nose!");
    add_cchat("I'm gonna smack you so hard....");

    set_ticket(TICKET);
    set_price(PRICE);

    set_up_pelargir_tour();

    set_harbour("Pelargir upon Anduin in Gondor");
    set_target("Kabal");
}

