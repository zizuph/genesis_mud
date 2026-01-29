/* -*- Mode: C -*-
 *
 * npc/m11-servant.c
 *
 * By Skippern 20(c)02
 *
 * This is the servant in mansion M-11.
 */
inherit "/d/Gondor/common/dunedain/npc/npc_dunadan.c";

#include "../defs.h"
#include <const.h>
#include <macros.h>
#include <ss_types.h>

/* Prototypes */

public void
create_dunadan()
{
    set_living_name("aranur");
    set_name("aranur");
    add_name( ({ "dunadan", "servant" }) );
    set_adj("humble");
    set_race_name("human");
    set_gender(G_MALE);
    set_title("humble servant of Sir Isaac");
    set_dunedain_house("Belecthor");
    set_long("This middle aged man is a servant for Sir Isaac of " +
	     "Belecthor, a welthy man of Dol Amroth.\n");

    default_config_npc(55);
    set_base_stat(SS_INT, 80);
    set_skill(SS_WEP_SWORD, 55);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_TRADING, 75);

    set_restrain_path(DOL_HILLS + "m-11");
    set_monster_home(DOL_HILLS + "m-11/hall1");
    set_random_move(30, 1);

    add_cmdsoul("/d/Gondor/common/dunedain/dunedain_soul");

    set_alignment(350);

    set_chat_time(200);
    add_chat("My master is a good man.");
    add_chat("It is a bit chilly in here, don't you think?");
    add_chat("The coctail party last week was a success.");
    add_chat("If I may say so, I am very found of the garden this year. " +
	     "Never seen more tulips in one place.");
    add_chat("I think the master should chop down that ugly pine tree " +
	     "in the front garden.");

    set_act_time(75);
    add_act("fire");
    add_act("fire");
    add_act("fire");
    add_act("glitter");
    add_act("gleam");
    add_act("silence");
    add_act("dpace");
}

public void
introduce_me(object pl, string name)
{
    command("say Greetings "+capitalize(name));
    command("introduce me to "+name);
    command("bow to "+name);
    command("say Whats your business with Isaac?");
}

public void
add_introduced(string name)
{
    object    pl;

    set_alarm(2.0, 0.0, &introduce_me(pl, name) );
}
