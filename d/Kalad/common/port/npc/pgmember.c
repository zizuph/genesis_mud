inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("member");
    set_race_name("human");
    set_adj("press");
    add_adj("gang");
    set_short("press gang member");
    set_long("A burly-looking man who has a disconcertingly wild look in his "+
      "eyes. It becomes even more disconcerting when that same pair of eyes, along with the crazed look, "+
      "stares into your own.\n");
    set_stats(({40,30,40,20,20,30}));
    set_alignment(-25);
    set_skill(SS_WEP_CLUB,60);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_PARRY,50);
    set_skill(SS_AWARENESS,30);
    set_act_time(6);
    add_act("emote looks at you with a crazed look in his eyes.");
    add_act("grin crazily");
    add_act("say Hey scum! Get outta here!");
    add_act("poke all eye");
    set_cact_time(3);
    add_cact("say I'll beat the crap out of you!");
    add_cact("spit");
    add_cact("say You worthless pile of dung!");
    add_cact("think kicking your butt");
    set_knight_prestige(25);
    set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
    object wep,arm;
    seteuid(getuid(this_object()));
    arm = clone_object("/d/Kalad/common/port/arm/pgmarm");
    arm -> move(TO);
    command("wear all");
    wep = clone_object("/d/Kalad/common/port/wep/pgmclub");
    wep -> move(TO);
    command("wield all");
    MONEY_MAKE_SC(random(20))->move(TO,1);
}
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("say I'll kill you, " + ob->query_nonmet_name() + "!");
	command("kill " + lower_case(ob->query_real_name()));
    }
}
