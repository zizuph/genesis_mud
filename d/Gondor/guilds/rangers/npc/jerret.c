/*
 *  /d/Gondor/guilds/rangers/npc/humphrie.c
 *
 *  Innkeeper of the North Hideout Mess Hall.
 *
 *  Modification log:
 *
 *  15-Jul-01, Alto: revised to fit new rangers theme
 *  29-Oct-03, Tigerlily: fixed gender 
 */
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

inherit RANGERS_NPC + "npc_ranger.c";

#define CO_NO    2

public void
introduce(object player)
{
    command("hail " + OB_NAME(player));
    command("present me to " + OB_NAME(player));
}

public void
create_ranger() 
{
    set_living_name("jerret");
    set_name("jerret");
    add_name(({"shopkeeper", "owner", "shopowner"}));
    set_race_name("human");
    set_adj(({"tall", "stern-faced"}));
    set_gender(G_MALE);
    set_title("the Shopkeeper of the Rangers of the North");
    set_long("This is the shopkeeper of the northern hideout, Jerret. "
        + "He is tall and lean, and has a dangerous look about him. Rumour "
        + "has it that he was once a great warden of the northern hills until "
        + "a troll broke his legs and arms. These days he can generally be "
        + "found here in his shop, dusting the various items for sale.\n");
    default_config_npc(52);
    set_skill(SS_WEP_SWORD, 50);
    set_skill(SS_DEFENCE,   50);
    set_skill(SS_TRADING,   55);
    set_alignment(600 + random(200));
    set_chat_time(12);
    add_chat("Can I help you?");
    add_chat("Welcome to my shop!");
    add_chat("My name is Jerret.");
    add_chat("Bloody trolls. If there hadn't been three of them, I might "
        + "still be out there on the borders today.");
    add_chat("Have you got anything nice to sell?");
    add_chat("Perhaps you want to buy some excellent equipment?");

    add_cchat("Get out of here, you thieving scoundrel!");
    add_cchat("You won't get away with this, you know!");
    add_cchat("Guards! Help!");

    add_ask(({"troll", "trolls", "borders"}), "say Aye, I used to "
        + "spend many months at a time walking the northern borders. Killed "
        + "half a hundred trolls in my time. Then one day, three of them got "
        + "a jump on me and broke my legs and both arms. I still killed them, "
        + "but my days of walking the borders are over.", 1);

    set_company_no(CO_NO);
    set_size_descs("tall", "very lean");
}


/* solamnian prestige */
int
query_knight_prestige()
{
    return (-5);
}

