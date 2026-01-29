#include "defs.h"
inherit STD_DIR + "good_fighter";
inherit LIB_DIR + "schedule";
inherit "/std/act/action";

void
create_npc()
{
    ::create_npc();
    set_name("guard");
    add_name("guardsman");
    set_race_name("human");
    set_adj("watchful");
    set_short("watchful guardsman");
    set_pshort("watchful guardsmen");
    set_stats(STAT_ARRAY(110));
    set_alignment(random(350));
    set_skill(SS_WEP_SWORD, 80);
    set_skill(SS_WEP_AXE, 75);
    set_skill(SS_WEP_CLUB, 75);
    set_skill(SS_WEP_POLEARM, 80);
    set_skill(SS_2H_COMBAT, 75);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 75);
    set_skill(SS_AWARENESS, 30);
    set_act_time(60);
    set_cact_time(3);
    add_cact("say Die foul creature!");
    add_cact("say You will pay for this!");
    set_default_answer("@@seen_emote|stares straight ahead.");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    equip(({
      one_of_list(({
        DRAKMERE_WEP_DIR + "g_sword", DRAKMERE_WEP_DIR + "g_pike",
        DRAKMERE_WEP_DIR + "g_axe", DRAKMERE_WEP_DIR + "g_mace",
      })),
      DRAKMERE_ARM_DIR + "dgchain", DRAKMERE_ARM_DIR + "dggreaves",
      DRAKMERE_ARM_DIR + "dghelm", DRAKMERE_ARM_DIR + "dgcloak",
      DRAKMERE_ARM_DIR + "polish_shield",
    }));
    MONEY_MAKE_GC(random(4))->move(TO, 1);
}

void
schedule()
{
    object routine = clone_object(STD_DIR + "autopath");
    routine->set_destination("beach");
    routine->set_live(TO);
    queue_routine(routine);
    start_schedule();
}
