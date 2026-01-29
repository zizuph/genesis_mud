inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* fat merchant, by Sarr */
void
create_monster()
{
    ::create_monster();
    set_name("fatty");
    set_race_name("human");
    set_adj("fat");
    add_adj("greedy");
    set_long(
    "This is one of the many traveling merchants roaming the market.\n"+
    "This one seems to be particulary well fed, and judging by the\n"+
    "bulges in his pockets, well off. He stares at you with greed in his\n"+
    "beady black eyes.\n");
    set_alignment(200);
    set_knight_prestige(-200);
    set_stats(({60,30,40,40,40,20}));
    set_skill(SS_WEP_KNIFE,60);
    set_skill(SS_PARRY,50);
    set_skill(SS_DEFENCE,30);
    add_prop(NPC_M_NO_ACCEPT_GIVE,0);
    add_speak("I used to work for the House of Drumar.\n");
    set_act_time(4);
    add_act("say I'll make you an offer you can't refuse....");
    add_act("emote grins greedily.");
    add_act("say There is a price for everything.");
    add_act("emote dusts off his cloak.");
    add_act("emote peers around, looking for a some poor sucker to con.");
    add_act("say If you are good, you can make anyone belive you.");
    add_act("emote grins smugly.");
    set_cact_time(3);
    add_cact("shout Guards! Help me! Murder!");
    add_cact("emote peers around franticly, looking for an escape.");
    add_cact("say I can pay you well! Please spare me!");
    add_cact("I have 5 children to feed! Please!");
    add_cact("I just an honest, hard-working man! What did I do to you!?");
    set_alarm(1.0, 0.0, "arm_me");
}
void
arm_me()
{
    object arm;
    object wep;
    seteuid(getuid(TO));
    arm = clone_object("/d/Kalad/common/market/arm/dmcloak.c");
    arm -> move(TO);
    command("wear all");
    wep = clone_object("/d/Kalad/common/market/wep/smdagger.c");
    wep -> move(TO);
    command("wield all");
    MONEY_MAKE_SC(random(48))->move(TO,1);
}

