#include "default.h"

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

void
create_kalad_monster()
{
    int i;
    set_name("goliath");
    add_name("bodyguard");
    set_race_name("half-ogre");
    set_adj("massive");
    add_adj("menacing");
    set_long("A large being, standing well over seven feet in height. "+
      "From a distance he seems passable as a human being, but upon closer "+
      "inspection you realize that ogre blood runs through this being's "+
      "veins. Although hulking and nearly as massive as a true ogre, he has "+
      "a certain look of intelligence in his eyes, and it isn't one of "+
      "malice.\n");
    for(i = 0; i < 3; i++)
	set_base_stat(i, 125 + random(50));
    set_base_stat(3, 50);
    set_base_stat(4, 50);
    set_base_stat(5, 125);
    set_alignment(100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_SPELLCRAFT, 20);
    set_act_time(6);
    add_act("glare all");
    add_act("snarl all");
    add_act("growl all");
    add_act(({"smirk", "wipe"}));
    add_act(({"impress", "strut"}));
    add_act("shave");
    add_act("axelick");
    set_cact_time(6);
    add_cact("command alrandulgur");
    set_title("the Master Bodyguard");
    set_knight_prestige(-1);
}

void
arm_me()
{
    object wep, arm;
    seteuid(getuid(TO));
    arm = clone_object(ARM + "mbgslarm");
    arm->move(TO);
    arm = clone_object(ARM + "mbgloves");
    arm->move(TO);
    arm = clone_object(ARM + "mbgboots");
    arm->move(TO);
    command("wear all");
    wep = clone_object(WEP + "mbgaxe");
    wep->move(TO);
    command("wield all");
    MONEY_MAKE_PC(random(2))->move(TO, 1);
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("say Now you'll die! Stupid " + ob->query_race_name() + "!");
	command("kill " + OB_NAME(ob));
    }
}

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    me = TO;
    if (random(5))
	return 0;
    hitresult = enemy->hit_me(300 + random(400), W_BLUDGEON, me, -1);
    how = " without effect";
    if (hitresult[0] > 0)
	how == "";
    if (hitresult[0] > 5)
	how = " hard";
    if (hitresult[0] > 10)
	how = " very hard";
    if (hitresult[0] > 15)
	how = " extremely hard";
    if (hitresult[0] > 20)
	how = " tremendously hard";
    if (hitresult[0] > 25)
	how = " so hard, the sound of bones snapping can be heard";
    if (hitresult[0] > 30)
	how = " so incredibly hard, that blood explodes everywhere";
    me->catch_msg("You bearhug your opponent!\n"+
      capitalize(enemy->query_pronoun())+" is bearhugged"+
      how + ".\n");
    enemy->catch_msg(QCTNAME(me) + " bearhugs you!\n"+
      "You are bearhugged" + how + ".\n");
    tell_watcher(QCTNAME(me) + " bearhugs " + QTNAME(enemy) + "!\n"+
      capitalize(enemy->query_pronoun()) + " is bearhugged"+
      how + ".\n", enemy);
    if (enemy->query_hp() <= 0)
	enemy->do_die(me);
    return 1;
}
