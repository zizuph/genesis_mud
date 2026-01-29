/* Change the alignment to 200
 * From 550 which seemed kind of 
 * extreme for this NPC 
 * Damaris 2/2002
 */
inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("guard");
    add_name("halfling guard");
    set_race_name("hobbit");
    set_adj("big");
    set_short("halfling guard");
    set_long("A large, burly-looking halfling guardsman. Although he is "+
      "large for his race, he stands no taller than three and a half feet "+
      "in height.\n");
    set_stats(({30,60,30,30,30,25}));
    set_alignment(250);
    set_skill(SS_WEP_SWORD,50);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_PARRY,50);
    set_skill(SS_AWARENESS,30);
    set_act_time(6);
    add_act("emote looks like he wants some beer.");
    add_act("smile");
    add_act("say Hello! Are you here to buy some beer?");
    set_cact_time(3);
    add_cact("say Wouldn't you rather drink some beer than hurt little old me?");
    add_cact("sigh");
    add_speak("I'm just here to make sure nothing goes amiss.\n");
    set_knight_prestige(-8);
    set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
    object wep,arm;
    seteuid(getuid(TO));
    arm = clone_object("/d/Kalad/common/port/arm/hbglarm");
    arm -> move(TO);
    command("wear all");
    wep = clone_object("/d/Kalad/common/port/wep/hbgsword");
    wep -> move(TO);
    command("wield all");
    MONEY_MAKE_SC(random(10))->move(TO,1);
}
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("say You mean old " + ob->query_race_name() + "!");
	command("say Stop fighting my friend!");
	command("kill " + lower_case(ob->query_real_name()));
    }
}
