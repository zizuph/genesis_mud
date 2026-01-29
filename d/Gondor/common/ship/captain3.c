#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/ship/captain.c";
inherit "/d/Gondor/common/ship/pel_tours";

#include <filter_funs.h>

#include "/d/Gondor/defs.h"

#define TICKET  (SHIP_DIR + "ticket3")
#define PRICE   24

public void    grimoire_found(object ob);

static void
create_gondor_captain()
{
    set_name("sardon");
    add_name("sailor");
    set_living_name("sardon");
    set_race_name("human");
    add_adj("proud");
    add_adj("old");
    set_title("the Sailor of the oceans");

    set_chat_time(15);
    add_chat("Hmmph. I think we're behind schedule again.");
    add_chat("We'll have to chance upon not meeting the Corsairs today.");
    add_chat("The Corsairs give no quarter.");
    add_chat("Minas Tirith is still bustling with activity. Trade is good.");
    add_chat("I heard strange tales about Gont Port.");
    add_chat("I heard one of the other traders ran into the Corsairs.");
    add_chat("Umbar is the Haven of the dreaded Corsairs.");
    add_chat("Competition is not hard nowadays.");
    add_chat("I wonder how long before the war breaks out.");
    add_chat("Fair wind today. We should be able to stay on schedule.");
    add_chat("In Minas Tirith, visit Hunthor, the Master of Advice!");
    add_chat("In Pelargir, visit Carastur, the Lord Councillor!");
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

    set_up_pelargir_tour();

    set_ticket(TICKET);
    set_price(PRICE);

    set_harbour("Pelargir upon Anduin in Gondor");
    set_target("Gont Port");
}

public void
no_grimoire()
{
    object *players;
    object *obs;
    int i;
    int j;
    int al_time;

    al_time = 4;
    players = FILTER_LIVE(all_inventory(ENV(TO)));

    for (i = 0; i < sizeof(players); i++)
    {
        obs = deep_inventory(players[i]);

        for (j = 0; j < sizeof(obs); j++)
        {
            if (obs[j]->id("refnasgrim"))
            {
                obs[j]->remove_object();
                set_alarm(itof(al_time), 0.0, &grimoire_found(players[i]));
                al_time += 2;
            }
        }
    }

    return;
}

void
grimoire_found(object ob)
{
    command("shout I don't want such dangerous things on my ship!");
    command("shout Give me that dangerous book.");
    ob->CATCH_MSF(TO, " takes your grimoire.");
    LTELL_ROOM(ENV(TO), ob, "The captain takes something from ", ".", ob);
}

