#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/ship/captain.c";
inherit "/d/Gondor/common/ship/pel_tours.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define TICKET  (SHIP_DIR + "ticket2")
#define PRICE   30

public void
create_gondor_captain()
{
    set_name("earendil");
    set_living_name("earendil");
    set_race_name("elf");
    add_adj("fair");
    add_adj("weather-beaten");
    set_title("the Mariner");

    set_long("Earendil the Mariner, son of Tuor, son of Huor the " +
        "Steadfast, and of Idril Silverfoot, daughter of Turgon, King of " +
        "Gondolin. It was Earendil who sailed to Valinor to ask for mercy " +
        "from the Valar on behalf of both kindreds, elves and men. But " +
        "the tale of Earendil knows that Earendil sailed only the sky " +
        "after his journey across the ocean to Valinor. So this elf here " +
        "cannot be the Earendil that the old tale tells about, but must " +
        "be some admirer who took the name of his idol. But like the " +
        "Earendil of the tale, he is tall and fair, even though his travels " +
        "across the seas and the winds and waters he navigated left their " +
        "traces in his weather-beaten face.\n");
    set_stats(({ 75 + random(25), 75 + random(25), 65 + random(25), 65 + random(15), 65 + random(15), 90 }));
    set_alignment(1000);

    add_prop(CONT_I_HEIGHT,   216);
    add_prop(CONT_I_WEIGHT, 45000);
    add_prop(CONT_I_VOLUME, 44000);

    set_chat_time(5);
    add_chat("Hmmph. I think we're behind schedule again.");
    add_chat("We'll have to chance upon not meeting the Corsairs today.");
    add_chat("The Corsairs give no quarter.");
    add_chat("Pelargir is still bustling with activity. Trade is good.");
    //add_chat("Faerie is the fairest place in the world.");
    add_chat("Did you ever meet with Cirdan the Shipwright?.");
    add_chat("I heard one of the other traders ran into the Corsairs.");
    add_chat("Umbar is the Haven of the dreaded Corsairs.");
    add_chat("Competition is not hard nowadays.");
    add_chat("Somebody is opening a route to the Grey Havens I've heard.");
    add_chat("The Vingilot is the fairest of all ships.");
    add_chat("No mortal man ever reached the Bay of Eldamar, but Earendil.");
    add_chat("Aman, the Blessed Realm, lies beyond the Enchanted Isles.");
    add_chat("Beyond the Enchanted Isles and the Shadowy Seas, there lies Tol Eressea the Lonely Isle.");
    add_chat("Alqualonde, the Haven of the Swans, lies on the Bay of Eldamar in Aman.");
    add_chat("Tirion, the city of the Noldor, lies on the green hill Tuna in the Calacirya.");
    add_chat("In Minas Tirith, visit Hunthor, the Master of Advice!");
    add_chat("In Pelargir, visit Carastur, the Lord Councillor of the city!");
    add_chat("I've heard the plains of Rohan are orc infested. Stay to the road!");
    add_chat("At the Harlond they tell that armies of orcs and Haradrim have overrun Ithilien.");
    add_chat("In Edoras, look for Elfhelm the Marshal.");
    add_chat("Don't go to Ithilien unless by Leave of the Steward!");
    set_cchat_time(11);
    add_cchat("Hey! Are you one of the pirates of Umbar??!");
    add_cchat("Stop it, you pestering dog!");
    add_cchat("Cursed serf of the Evil One!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylights out of you!");
    add_cchat("Right! I'm really gonna stump you this time!");
    add_cchat("Give it to me, big-nose!");
    add_cchat("I'm gonna smack you so hard....");

    set_ticket(TICKET);
    set_price(30);

    set_up_pelargir_tour();

    set_harbour("Pelargir upon Anduin in Gondor");
    set_target("Port McDunn");
//    set_target("Faerie");
}
