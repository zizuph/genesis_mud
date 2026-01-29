/*
 * Gemist example
 * by Finwe, September 2016
 */

#include "/d/Faerun/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";
inherit "/d/Faerun/lib/gems";

void create_monster()
{
    int i;

    seteuid(getuid());
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    add_adj("short");
    add_adj("gnarly");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("dwarf");
    add_name(npc_name);
    add_name("woman");
    set_short("short gnarly dwarf");
    set_long("TThis is the local gemist.\n");

    set_gender(G_MALE);
    add_prop(CONT_I_WEIGHT,85000);
    add_prop(CONT_I_HEIGHT,190);
    add_prop(NPC_I_NO_LOOKS, 900); /*sets visual looks */

    default_config_npc(30 + random(10));
    set_base_stat(SS_DEX, (40 + random(25)));

    set_alignment(110 + random(50));

    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_WEP_AXE,50);
    set_skill(SS_WEP_CLUB,50);
    set_skill(SS_WEP_KNIFE,50);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_2H_COMBAT, 50);

   /* Actions */
    set_act_time(5);
    set_cact_time(5);

    add_chat("I can buy and sell you gems.");
    add_chat("Do you have gems to sell?");
    add_chat("What gems do you want to sell me?.");

    add_prop(LIVE_I_NEVERKNOWN, 1);
}

void
init_living()
{
    ::init_living();
}
