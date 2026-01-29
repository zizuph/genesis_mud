/*
 * /d/Gondor/rohan/edoras/npc/rosoldier.c
 *
 * 27-aug-1997, Olorin: Revision.
 */
#pragma strict_types
inherit "/d/Gondor/rohan/edoras/npc/edoras_soldier";
inherit "/d/Gondor/common/lib/logkill.c";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_guard()
{
    int     rnd1 = random(11),
	      rnd2 = random(21);
    ::create_guard();
    set_short(implode(query_adjs(), " ") + " soldier");
    set_pshort("tall blond-haired soldiers");
    set_pname("soldiers");

    default_config_npc(75 + rnd2);
    set_base_stat(SS_CON, 90 + rnd1 + rnd2/2);

    set_skill(SS_WEP_SWORD, 80 + rnd1);
    set_skill(SS_PARRY,     50 + rnd2);
    set_skill(SS_DEFENCE,   80 - rnd1);
    set_skill(SS_AWARENESS, 70 - rnd2);

    add_prop(CONT_I_VOLUME, 65000 + rnd1 * 1000);
    add_prop(CONT_I_WEIGHT, 65000 + rnd1 * 1000);
    add_prop(CONT_I_HEIGHT,   175 + rnd2);

    set_chat_time(16);
    add_chat("Harding says he spotted an Uruk on the plains, bad news indeed.");
    add_chat("Elfhelm will find out for sure, somehow.");
    add_chat("Saruman is up to no good. I can feel it!");
    add_chat("Orcs are the most vile beasts! All should die!");
    set_cchat_time(5);
    add_cchat("You dare to attack within the walls of Edoras!");
    add_cchat("Impudent dog! Go back to the hole you crawled out of!");
    add_cchat("Death to thee, Enemy of the Rohirrim!");
    MONEY_MAKE_CC(23 + random(48))->move(TO);
    MONEY_MAKE_SC(11 + random(24))->move(TO);
}

int query_knight_prestige(){ return -5;}


