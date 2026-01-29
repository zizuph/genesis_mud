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
    set_cact_time(3);
    add_cact("say Now I'm going to hurt you!");
    add_cact("emote looks like he's going to hurt you.");
    add_cact("shout Guards! An intruder!");
    add_speak("Only company members are allowed inside...and of course, "+
      "those people with gold for trade...\n");
    set_knight_prestige(0);
    set_title("the Company Guardsman");
    set_default_answer("The company guard says: What was that?\n");
    add_ask(({"passage", "pass", "passing"}), "The company guard says: Noone "+
      "can enter the company building. Only company members are allowed "+
      "inside.\n");
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_alarm(1.0, 0.0, "arm_me");
    trig_new("%w 'gives' 'you' 'a' 'gold' %s", "react_gold");
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

void
return_gold(string who)
{
    object obj;
    int ran;

    if(obj = present(who, environment()))
    {
	command("smile greed");
	command("thank " + OB_NAME(obj));
	command("s");
	command("s");
    }
}

int
react_gold(string who, string dummy)
{
    if(who)
    {
	who = lower_case(who);
	set_alarm(3.0, 0.0, &return_gold(who));
	return 1;
    }
}
