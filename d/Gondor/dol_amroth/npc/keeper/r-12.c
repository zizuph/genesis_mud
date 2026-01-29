/* -*- Mode: C -*-
 *
 * npc/keeper/r-12.c
 * 
 * Skippern 20(c)01
 *
 * The shopkeeper of the store in r-12.
 */
inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";

#include "../../defs.h"
#include <const.h>
#include <ss_types.h>

public void
create_dunadan()
{
    set_living_name("indrew");
    set_name("indrew");
    add_name( ({ "dunandan", "keeper", "shopkeeper", "alchemist" }) );
    set_race_name("human");
    set_gender(G_MALE);
    set_title("Drug Clerk");
    set_dunedain_house("Amandil");
    set_long("This good man looks like he have taken a sip or two from " +
	     "the stock in this alchemy shop.\n");
    default_config_npc(65);

    set_base_stat(SS_WIS, 75);

    set_skill(SS_APPR_OBJ, 85);
    set_skill(SS_APPR_VAL, 85);

    set_alignment(650);

    set_act_time(5000);
    add_act("emote takes a sip from a bottle, and puts it back on the shelf.");
    set_chat_time(75);
    add_chat("Did you know the antidote curing hangovers taste like honey?");
    add_chat("I once had a potion here who turned frogs into princesses, " +
	     "now who bought that agains?");
}

public void
introduce_me(object pl, string name)
{
    command("say Greetings "+capitalize(name));
    command("introduce me to "+name);
    command("smile");
    command("say Interested in some potions?");
}

public void
add_introduced(string name)
{
    object    pl;

    set_alarm(2.0, 0.0, &introduce_me(pl, name) );
}
