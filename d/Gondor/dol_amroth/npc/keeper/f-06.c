/* -*- Mode: C -*-
 *
 * npc/keeper/f-06.c
 * 
 * Skippern 20(c)02
 *
 * The shopkeeper of the store in d-07.
 */
inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";

#include "../../defs.h"
#include <const.h>
#include <ss_types.h>

public void
create_dunadan()
{
    set_living_name("agnir");
    set_name("agnir");
    add_name( ({ "dunandan", "keeper", "shopkeeper", "armer", 
		   "weapon smith" }) );
    set_race_name("human");
    set_gender(G_MALE);
    set_title("Royal Weapon smith of Prince Imrahil");
    set_dunedain_house("Thalion");
    set_long("This strong man is the best weapon smith in Dol Amroth.\n");
    default_config_npc(85);

    set_base_stat(SS_STR, 100);

    set_skill(SS_APPR_OBJ, 85);
    set_skill(SS_APPR_VAL, 85);

    set_alignment(650);

    set_chat_time(75);
    add_chat("I have the best stock of weapons in all Gondor.");
}

public void
introduce_me(object pl, string name)
{
    command("say Greetings "+capitalize(name));
    command("introduce me to "+name);
    command("flex");
    command("say Are you looking for a sword maybe?");
}

public void
add_introduced(string name)
{
    object    pl;

    set_alarm(2.0, 0.0, &introduce_me(pl, name) );
}
