#include "defs.h"
inherit "/d/Raumdor/std/guard_std";

void
create_monster()
{
    int i;
    ::create_monster();
    set_name("guard");
    add_name("guardsman");
    set_race_name("human");
    set_adj("palace");
    add_adj("elite");
    set_short("elite palace guard");
    set_long("This is one of the royal elite palace guards. He is well " +
            "trained, and an aura of divine power surrounds him. " +
            "He regards you with a stern gaze.\n");

    set_stats(STAT_ARRAY(140));

    set_alignment(DRAKMERE_ALIGN);

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 95);
    set_skill(SS_AWARENESS, 60);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_act_time(6);
    add_act("emote stands straight.");
    add_act("emote adjusts his armour.");

    set_cact_time(3);
    add_cact("shout For Drakmere!");
    add_cact("say Die foul creature!!");
    add_cact("scream");
    add_cact("say You will pay for this!");

    equip(({
        one_of_list(({
            "/d/Raumdor/common/drakmere/wep/g_sword.c",    
            "/d/Raumdor/common/drakmere/wep/g_pike.c",
            "/d/Raumdor/common/drakmere/wep/g_axe.c",
            "/d/Raumdor/common/drakmere/wep/g_mace.c",
        })),
        "/d/Raumdor/common/drakmere/arm/eg_plate",
        "/d/Raumdor/common/drakmere/arm/eg_greaves",
        "/d/Raumdor/common/drakmere/arm/eg_helm",
        "/d/Raumdor/common/drakmere/arm/dgcloak",
        DRAKMERE_ARM_DIR + "eg_boots",

    }));
    MONEY_MAKE_GC(random(10))->move(TO,1);
}

void
init_living()
{
    ::init_living();
    if(TP->query_prop(LIVE_I_UNDEAD))
    {
        set_alarm(0.5,0.0,"kill_undead",TP);
    }
}

void
kill_undead(object ob)
{
    command("shout Creature of the Night! Die!!!");
    command("kill "+lower_case(ob->query_name()));
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        command("say I shall aid you brother!");
        command("say Drakmere!");
        command("kill " + OB_NAME(ob));
    }
}



