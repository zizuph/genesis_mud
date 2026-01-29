#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    add_name("guard");
    set_race_name("human");
    set_adj("company");
    set_short("company guard");
    set_long("This man is one of the guardsmen of the powerful and wealthy "+
      "trading company. He doesn't look too happy to see you here.\n");
    set_stats(({80, 85, 80, 60, 60, 85}));
    set_alignment(0);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 90);
    set_skill(SS_AWARENESS, 60);
    set_act_time(6);
    add_act("emote frowns unhappily at you.");
    add_act(({"poke all", "say Leave before someone gets hurt."}));
    add_act("say You're not supposed to be here.");
    add_act("say Only the most trusted guardsmen know the identity of the Lord of the Trading Company.");
    set_cact_time(3);
    add_cact("say Now I'm going to hurt you!");
    add_cact("emote looks like he's going to hurt you.");
    add_cact("shout Guards! An intruder!");
    add_speak("Only company members are allowed inside.\n");
    set_knight_prestige(0);
    set_title("the Company Guardsman");
    set_default_answer("The company guard says: What was that?\n");
    add_ask(({"passage", "pass", "passing"}), "The company guard says: Noone "+
      "can enter the company building. Only company members are allowed "+
      "inside.\n");
    this_object()->arm_me();
    /* XP Adjustment, Cotillion 2014-12-02 */
    set_exp_factor(120);
}

void
arm_me()
{
    object wep, arm;
    seteuid(getuid(this_object()));
    arm = clone_object(ARM + "tcgplate");
    arm->move(this_object());
    arm = clone_object(ARM + "tcghelm");
    arm->move(TO);
    command("wear all");
    wep = clone_object(WEP + "tcghalb");
    wep->move(this_object());
    command("wield all");
    MONEY_MAKE_GC(random(5))->move(this_object(), 1);
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("gasp");
	command("say Die! Enemy of the Company!");
	command("kill " + OB_NAME(ob));
    }
}
