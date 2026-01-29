/*
 * Farmer Guy
 * by Finwe, August, 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";
inherit "/d/Faerun/lib/gems";

int doing_quest = 0;    /* someone is doing the quest */
int quest_done  = 0;    /* quest is done, waiting for NPC to reset */

void arm_me();

void create_monster()
{
    int i;

    seteuid(getuid());
    set_name("ezfalol");
    add_name("farmer");
    set_title("Anton");
    npc_name = "_farm_human";

    add_adj("rugged");
    add_adj("suntanned");
    set_short("rugged suntanned human");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_race_name("human");
    add_name(npc_name);

    set_long("This is a " + query_short() + ". He is a member of the Anton " +
        "family, and owns the farm and everything on it. He has sun-bleached " +
        "brown hair and is muscular from all the hard work he does. His " +
        "skin is leathery and creased from years of working outside. \n");
    
    set_gender(G_MALE);
    add_prop(CONT_I_WEIGHT,100000);
    add_prop(CONT_I_HEIGHT,200);
            /* STR DEX CON INT WIS DIS */
    for (i = 0; i < 5; i++)
        set_base_stat(i, 80 + random(25));
    set_base_stat(5, 80);

    set_alignment(110 + random(50));

    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,90);
    set_skill(SS_WEP_AXE,70);
    set_skill(SS_WEP_CLUB,70);
    set_skill(SS_WEP_KNIFE,70);
    set_skill(SS_PARRY, 90);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_2H_COMBAT, 60);

   /* Actions */
    set_act_time(5);
    set_cact_time(5);
    add_chat("Farming is hard work, and not for the lazy people.");
    add_chat("If you're looking for something to do, go see the wife. " +
        "She may put ya to work.");
    add_chat("My family has worked this land for generations.");
    add_chat("Beware of the Mere. Many say it's haunted, and I agree.");
    add_chat("Those darn chickens are so pesky!");
    add_chat("I love my life!");
//    add_chat("That Kogar family is despicable. Their son stole my dear Ginnae from us!");
//    add_chat("Oh, I'd give anything to find my dear Ginnae!");

    set_cchat_time(5);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    arm_me();

    set_random_move(8);
    set_restrain_path(FROOM_DIR);

    set_pick_up_team(({npc_name}));

}


void
arm_me()
{
    object arm, wep, gem;

    make_gems(TO, 1);

    wep = clone_object(FWEP_DIR + "dagger");
    wep -> move(TO);

    arm = clone_object(FARM_DIR + "ltunic");
    arm -> move(TO);
    arm = clone_object(FARM_DIR + "pants");
    arm -> move(TO);

    command("wield weapon");
    command("wear all");

}

void
init_living()
{
    ::init_living();
    init_team_pickup();
}

void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
    command("say to " + TP->query_real_name() + " Nice to meet ya!");
    command("shake " + TP->query_real_name() );
}


void reset_monster()
{
    ::reset_monster();
    doing_quest = 0;
    quest_done  = 0;
}
