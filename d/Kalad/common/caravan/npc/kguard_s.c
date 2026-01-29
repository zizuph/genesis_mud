#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    set_name("guard");
    add_name("guardsman");
    set_race_name("human");
    set_adj("vigilant");
    add_adj("kabal");
    set_short("guardsman of Kabal");
    set_pshort("guardsmen of Kabal");
    set_long("He is a tall, dark-haired man whose job is to insure that "+
      "order is maintained in the great city of Kabal. Oftentimes he fails, "+
      "making him ever more cruel to those that defy him.\n");
    set_stats(({75, 70, 75, 55, 55, 65}));
    set_alignment(250);
    set_skill(SS_WEP_SWORD, 80);
    set_skill(SS_WEP_KNIFE, 60);
    set_skill(SS_2H_COMBAT, 70);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 75);
    set_skill(SS_AWARENESS, 30);
    set_act_time(6);
    add_act("peer all");
    add_act("say Beware.");
    add_act("say No buyers are allowed up the platform.");
    set_cact_time(3);
    add_cact("shout Fellow guardsmen, come to my aid!");
    add_cact("say You will die for this cowardly attack, you miserable cur.");
    add_speak("It will cost you one gold coin to pass.\n");
    set_knight_prestige(-3);
    set_default_answer("The guardsman of Kabal says: What?\n");
    add_ask(({"captain"}), "The guardsman of Kabal says: That would be Hahmal.\n");
    add_ask(({"pass", "passing"}), "The guardsman of Kabal says: Give me a gold "+
      "coin and you may pass.\n");
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    trig_new("%w 'gives' 'you' 'a' 'gold' 'coin.\n' %s", "react_pass");
}

void
arm_me()
{
    object wep, arm;
    seteuid(getuid(TO));

    arm = clone_object(ARM + "gchain");
    arm->move(TO);
    arm = clone_object(ARM + "ghelm");
    arm->move(TO);
    command("wear all");
    wep = clone_object(WEP + "gsword");
    wep->move(TO);
    wep = clone_object(WEP + "gdagger");
    wep->move(TO);
    command("wield all");
    MONEY_MAKE_GC(random(3)+1)->move(TO, 1);
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("say Villanous retch! Die!");
	command("kill " + OB_NAME(ob));
    }
}

void
return_pass(string who)
{
    object obj;
    int ran;
    if(obj = present(who, environment()))
    {
	command("grin greedily");
	command("say Thanks for the cash, " + obj->query_nonmet_name() + ".");
	command("say You may go up to the platform now.");
	obj->move_living("up to the platform", CVAN + "slave/s7");
    }
}

int
react_pass(string who, string dummy)
{
    if(who)
    {
	who = lower_case(who);
	set_alarm(3.0, 0.0, &return_pass(who));
	return 1;
    }
}

int
special_attack(object ob)
{
    string phurt;
    mixed *hitres;

    if(random(100) > 75)
    {
	if(query_combat_object()->cb_tohit(-1, 60 + random(25), ob) < 1)
	    return 0;

	if(!sizeof(query_weapon(-1)))
	    return 0;

	hitres = ob->hit_me(random(150)+100, W_BLUDGEON, TO, -1);
	phurt = " with hardly any effect";
	switch(hitres[0])
	{
	case 1..20:
	    phurt = "";
	    break;
	case 21..40:
	    phurt = " with a thud";
	    break;
	case 41..60:
	    phurt = " with a loud thud";
	    break;
	case 61..80:
	    phurt = " with a loud crack";
	    break;
	default:
	    phurt = " with a bone crushing sound";
	}

	tell_object(ob, query_The_name(ob)+" slams his foot into your "+
	  "chest"+phurt+"!\n");
	tell_watcher(QCTNAME(TO)+" slams his foot into "+QTNAME(ob)+"'s "+
	  "chest"+phurt+"!\n", ob);

	if(ob->query_hp() <= 0)
	    ob->do_die(TO);
	return 1;
    }
    return 1;
}
