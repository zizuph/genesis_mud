/* Change the alignment to 250
 * From 750 which seemed kind of 
 * extreme for this NPC 
 * Damaris 2/2002
 */
inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("worker");
    add_name("brewery worker");
    set_race_name("hobbit");
    set_adj("hard-working");
    set_short("brewery worker");
    set_long("This small, busy little halfling is one of the brewery's "+
      "diligent workers. Rivulets of sweat pour from his face as he goes "+
      "about his duties. You can't help but wonder if some of that sweat "+
      "runs into the beer.\n");
    set_stats(({30,50,30,20,20,20}));
    set_alignment(250);
    set_skill(SS_UNARM_COMBAT,30);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_AWARENESS,30);
    set_act_time(6);
    add_act("emote sweats like a pig.");
    add_act("smile");
    add_act("say Hello! Are you here to buy some beer?");
    add_act("whisper hobbit Don't tell the guards...but I have some triple "+
      "stout beer on me.\n");
    set_cact_time(3);
    add_cact("say Wouldn't you rather drink some beer than hurt little old me?");
    add_cact("sigh");
    add_cact("sniff");
    add_speak("Whew! I've been working all day here!\n");
    set_knight_prestige(-8);
    set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
    object arm;
    seteuid(getuid(TO));
    arm = clone_object("/d/Kalad/common/port/arm/hbwapron");
    arm -> move(TO);
    arm = clone_object("/d/Kalad/common/port/obj/triple_stout");
    arm -> move(TO);
    command("wear all");
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
