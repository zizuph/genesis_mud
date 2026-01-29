#include "defs.h"
inherit "/d/Raumdor/std/guard_std";

void
create_monster()
{
    ::create_monster();
    set_name("guard");
    add_name("guardsman");
    set_race_name("human");
    set_adj("vigilant");
    add_adj("drakmere");
    set_short("vigilant guardsman");
    set_pshort("vigilant guardsmen");
    set_long("He is a tall, stout individual. He wears a black and red "+
        "cloak over his shoulders, the colors of Drakmere. On his chest is "+
        "a large golden cross. His eyes dart about, looking for danger. He "+
        "looks like he has seen many a grim sight, and is prepared for "+
        "anything.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_stats(STAT_ARRAY(110));
    set_alignment(DRAKMERE_ALIGN);
    set_skill(SS_WEP_SWORD, 80);
    set_skill(SS_WEP_AXE, 75);
    set_skill(SS_WEP_CLUB, 75);
    set_skill(SS_WEP_POLEARM, 80);
    set_skill(SS_2H_COMBAT, 75);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 75);
    set_skill(SS_AWARENESS,30);
    set_act_time(20);
    add_act("emote adjusts his armour.");
    add_act("emote stands straight.");
    add_act("emote looks into the distance.");
    add_act("pace deliberately");
    add_act("emote leans to one side.");
    add_act("wait dutifully");
    add_act("mumble guards");
    add_act("emote stares stoically.");
    add_act("breathe");
    set_cact_time(3);
    add_cact("shout Fellow guardsmen, come to my aid!");
    add_cact("say Die foul creature!!");
    add_cact("scream");
    add_cact("say You will pay for this!");
    set_default_answer("The guardsman of Drakmere says: What?\n");

    /* Cotillion, 2016-03-03 */
    set_exp_factor(130);

    equip(({
        one_of_list(({
            "/d/Raumdor/common/drakmere/wep/g_sword.c",    
            "/d/Raumdor/common/drakmere/wep/g_pike.c",
            "/d/Raumdor/common/drakmere/wep/g_axe.c",
            "/d/Raumdor/common/drakmere/wep/g_mace.c",
        })),
        "/d/Raumdor/common/drakmere/arm/dgchain",
        "/d/Raumdor/common/drakmere/arm/dggreaves",
        "/d/Raumdor/common/drakmere/arm/dghelm",
        "/d/Raumdor/common/drakmere/arm/dgcloak",
    }));
    MONEY_MAKE_GC(random(4))->move(TO,1);
}
