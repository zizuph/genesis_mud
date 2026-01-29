/* -*- Mode: C -*-
 *
 * npc/keeper/a-05.c
 * 
 * Skippern 20(c)01
 *
 * The shopkeeper of the store in a-05.
 */
inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";

#include "../../defs.h"
#include <const.h>
#include <ss_types.h>

public void
create_dunadan()
{
    set_living_name("gurwen");
    set_name("gurwen");
    add_name( ({ "dunandan", "keeper", "shopkeeper", "tailor" }) );
    set_race_name("human");
    set_gender(G_MALE);
    set_title("Tailor of Dol Amroth");
    set_dunedain_house("Agarwaen");
    set_long("This is the shop keeper of the general shop.\n");
    default_config_npc(60);

    set_base_stat(SS_WIS, 75);

    set_skill(SS_APPR_OBJ, 85);
    set_skill(SS_APPR_VAL, 85);

    set_alignment(650);

    set_chat_time(75);
    add_chat("I have the best stock of clothings in all of Gondor.");
    add_chat("Interested in some new clothing?");
}

public void
introduce_me(object pl, string name)
{
    command("say Greetings "+capitalize(name));
    command("introduce me to "+name);
    command("grin friendly");
    command("say Looking for some clothes, are we?");
}

public void
add_introduced(string name)
{
  object    pl;

  set_alarm(2.0, 0.0, &introduce_me(pl, name) );
}
