
/*

  Feldon - Ship captain for Poros to island of Tolfalas
  Palmer 12 Aug 2006

*/


#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/ship/captain.c";

#include <filter_funs.h>

#include "/d/Gondor/defs.h"

#define TICKET  (SHIP_DIR + "ticket9")
#define PRICE   24


static void
create_gondor_captain()
{
    set_name("feldon");
    add_name("sailor");
    set_living_name("feldon");
    set_race_name("human");
    add_adj("proud");
    add_adj("old");
    set_title("the Sailor of the oceans");

    set_chat_time(15);
    add_chat("We'll have to chance upon not meeting the Corsairs today.");
    add_chat("The Corsairs give no quarter.");
    add_chat("I've heard the Black Numenoreans are exploring Tolfalas.");
    add_chat("I heard one of the other traders ran into the Corsairs.");
    add_chat("Umbar is the Haven of the dreaded Corsairs.");
    add_chat("Competition is not hard nowadays.");
    add_chat("I wonder how long before the war breaks out.");
    add_chat("Fair wind today. We should be able to stay on schedule.");
    add_chat("At the Harlond they tell that armies of orcs and Haradrim have overrun Ithilien.");
    set_cchat_time(11);
    add_cchat("Stop it, you pestering dog!");
    add_cchat("I fear noone but the Corsairs of Umbar!");
    add_cchat("Right, you'll pay for that!");
    add_cchat("Come on! I'll beat the living daylights out of you!");
    add_cchat("Right! I'm really gonna stump you this time!");
    add_cchat("I'm gonna smack you so hard....");

    set_ticket(TICKET);
    set_price(PRICE);

    set_harbour("Poros");
    set_target("Tolfalas");
}

