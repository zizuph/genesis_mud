/*
 *  /d/Gondor/rohan/isengard/npc/gate_guard.c
 *
 *  Opus, Aug 1997
 *
 *  Copyright   1997 by Robert Miller
 *
 *  Modification Log:
 */
#pragma strict_types

#include "/d/Gondor/defs.h"
inherit ISEN_DIR + "npc/isengard_monster";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

public void
create_isengard_monster()
{
    set_name("guard");
    add_name( ({"man", "dunlending"}));
    set_pname("guards");
    add_pname( ({"men", "dunlendings"}));
    set_short("dark-haired guard");
    set_race_name("human");
    set_adj("dark-haired");
    set_long( BSN(
	"A dark-haired guard protecting Isengard from any possible "+
	"threats. He stands before you ready to perform his duties."));
    set_alignment(-350 - random(200));
    set_stats(({ 74 + random(12),
	80 + random(8),
	70 + random(5),
	60 + random(7),
	55 + random(10),
	80 + random(7)}));
    set_skill(SS_WEP_POLEARM,    random(15) + 65);
    set_skill(SS_PARRY,          random(20) + 35);
    set_skill(SS_DEFENCE,        random(15) + 65);
    set_skill(SS_AWARENESS,      random(20) + 30);
    set_skill(SS_BLIND_COMBAT,   50);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_chat_time( random(15) + 55);
    add_chat("What business do you have here?");
    add_chat("How I long for some action.");
    add_chat("All of this standing is making my feet hurt.");
    add_chat("No one will get past me unless I want them to.");
    add_chat("Curse the king and his followers... their day will soon come!");

    set_cchat_time( random(8) + 10);
    add_cchat("Just wait until Saruman hears about this... You will be sorry.");
    add_cchat("Don't expect to leave here alive, scum!");

    set_act_time(60+ random(15));
    add_act("emote adjusts his armor.");
    add_act("yawn");
    set_cact_time(10 + random(10));
    add_cact("shout Help! Send reinforcements!");
    add_cact("shout We are under attack!");

    MONEY_MAKE_SC( 15 + random(20))->move(TO);
    MONEY_MAKE_GC( 7 + random(10))->move(TO);
    set_equipment( ({ISEN_DIR + "wep/poleaxe",
	ISEN_DIR + "arm/brigandine",
	ISEN_DIR + "arm/whhelm"}));
}

int query_knight_prestige() { return 850; }


