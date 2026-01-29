inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
    ::create_monster();
    set_name("sailor");
    set_race_name("human");
    set_adj("swarthy");
    set_short("swarthy sailor");
    set_long("This swarthy dark-haired man looks like he's lived all his "+
      "life out on the open sea. Perhaps that would explain why he looks "+
      "totally disgusted right now, considering the foul weather that has "+
      "been plaguing the Kaladian Sea. Gazing at his face, you note the "+
      "malicious glint therein.\n");
    set_stats(({40,50,40,30,30,50}));
    set_alignment(-100);
    set_skill(SS_WEP_SWORD,50);
    set_skill(SS_DEFENCE,50);
    set_skill(SS_PARRY,50);
    set_skill(SS_AWARENESS,30);
    set_skill(SS_UNARM_COMBAT,15);
    set_skill(SS_BLIND_COMBAT,15);
    set_skill(SS_SWIM,30);
    set_act_time(6);
    add_act("spit");
    add_act("complain all");
    add_act("say Damn weather, I hate it!");
    add_act("grumble");
    set_cact_time(3);
    add_cact("say I'll make you squeal like a newborn babe!");
    add_cact("emote spits in your eye!");
    add_cact("emote knees you in the stomach!");
    add_cact("grin");
    add_speak("I hate this weather, if you ask me, I think its because "+
      "of that damned and cursed island they just found.\n");
    set_default_answer("The swarthy sailor says: What???\n");
    add_ask(({"they"}),"The swarthy sailor says: Some dumb explorers...\n");
    add_ask(({"explorers","explorer"}),"The swarthy sailor says: How "+
      "should I know!\n");
    add_ask(({"island"}),"The swarthy sailor says: Its to the southwest somewhere.\n");
    set_knight_prestige(100);
    set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
    object wep,arm;
    seteuid(getuid(TO));
    arm = clone_object("/d/Kalad/common/port/arm/sailor_armour");
    arm -> move(TO);
    arm = clone_object("/d/Kalad/common/port/arm/sailor_boots");
    arm -> move(TO);
    command("say Damnit, ye've caught me unawares!");
    command("wear all");
    wep = clone_object("/d/Kalad/common/port/wep/sailor_sword");
    wep -> move(TO);
    command("say Crud, need to wield me damn weapon!");
    command("wield all");
    arm = clone_object("/d/Kalad/common/port/obj/fish");
    arm -> move(TO);
    MONEY_MAKE_SC(random(10))->move(TO,1);
}
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("say Eat seaweed, " + ob->query_nonmet_name() + "!");
	command("kill " + lower_case(ob->query_real_name()));
    }
}
