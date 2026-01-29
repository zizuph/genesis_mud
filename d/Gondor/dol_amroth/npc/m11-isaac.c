/* -*- Mode: C -*-
 *
 * npc/m11-isaac.c
 *
 * By Skippern 20(c)02
 *
 * This is the lord of the mansion M-11 in Dol Amroth.
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
    set_living_name("isaac");
    set_name("isaac");
    add_name( ({ "dunadan", "master", "sir", "lord" }) );
    set_adj("fat");
    add_adj("rich");
    set_race_name("human");
    set_gender(G_MALE);
    set_title("Shipowner");
    set_dunedain_house("Belecthor");
    set_long("He is a welthy shipowner clad in epxencive and beautiful " +
	     "clothes bought from various trading centers throughout " +
	     "the world.\n");

    default_config_npc(75);
    set_base_stat(SS_INT, 80);
    set_base_stat(SS_WIS, 85);
    set_skill(SS_WEP_SWORD, 55);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_TRADING, 75);

    add_cmdsoul("/d/Gondor/common/dunedain/dunedain_soul");

    set_alignment(350);

    set_chat_time(200);
    add_chat("I hope I get some news about the Morninstar soon, " +
	     "it ought to be back from Mithlond any day now.");
    add_chat("What could have happened to Eveningstar? She had the " +
	     "best captain and the best crew.");
    add_chat("I cannot understand why Mr. Hagworth hates me for. I havn't " +
	     "done him any wrong.");
    add_chat("Please leave me commoner, I need peace to work.");
    add_chat("I hope it doesn't mean trouble when the army leaves town this " +
	     "way.");

    set_act_time(75);
    add_act("emote takes a sip from his cognac.");
    add_act("emote pats on his cigar.");
    add_act("emote puffs a smokering with his cigar.");
    add_act("emote dips the tip of his cigar in the cognac.");
    add_act("fire");
    add_act("fire");
    add_act("fire");
    add_act("ponder");
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
    command("grumble");
    command("say If you have nothing important to me please leave, I am " +
	    "a busy man.");
}

public void
add_introduced(string name)
{
    object    pl;

    set_alarm(2.0, 0.0, &introduce_me(pl, name) );
}
