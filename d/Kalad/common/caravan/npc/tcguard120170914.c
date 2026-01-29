#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    set_name("ubenri");
    add_name("axeman");
    add_pname("axemen");
    set_race_name("human");
    set_adj("company");
    set_short("company axeman");
    set_pshort("company axemen");
    set_long("This man is one of the brutal axemen of the powerful and wealthy "+
      "trading company. He looks quite furious to see you here.\n");
    set_stats(({90, 80, 90, 50, 50, 85}));
    set_alignment(-100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 90);
    set_skill(SS_AWARENESS, 60);
    set_random_move(5);
    set_act_time(6);
    add_act("emote snarls at you with pure rage.");
    add_act(({"poke all", "say Leave before I kill you."}));
    add_act("say Get the hell out of here!");
    set_cact_time(3);
    add_cact("say I'm going to hack you into little bits!");
    add_cact("emote looks like he's going to hack you into little bits.");
    add_cact("shout Death to intruders!");
    add_speak("Only company members are allowed inside.\n");
    set_knight_prestige(100);
    set_default_answer("The company axeman says: What?!?\n");
    add_ask(({"passage", "pass", "passing"}), "The company axeman says: Noone "+
      "can enter the company building. Only company members are allowed "+
      "inside.\n");
    set_alarm(1.0, 0.0, "arm_me");
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
    wep = clone_object(WEP + "tcgaxe");
    wep->move(this_object());
    command("wield all");
    MONEY_MAKE_GC(random(3))->move(TO, 1);
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("growl angrily");
	command("say Die! Enemy of the Company!");
	command("kill " + OB_NAME(ob));
    }
}
