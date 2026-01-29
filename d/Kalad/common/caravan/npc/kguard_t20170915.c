#include "default.h"
inherit "/d/Kalad/std/monster";

string
random_extra()
{
    int i;
    i = random(3);
    if(i < 1)
	return WEP + "gmace";
    else if (i < 2)
	return WEP + "gsword";
    else
	return WEP + "gaxe";
}

void
create_kalad_monster()
{
    int i;
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
    for(i = 0; i < 3; i++)
	set_base_stat(i, 70 + random(25));
    set_base_stat(3, 55);
    set_base_stat(4, 55);
    set_base_stat(5, 65);
    set_alignment(333);
    set_skill(SS_WEP_CLUB, 70);
    set_skill(SS_WEP_SWORD, 80);
    set_skill(SS_WEP_AXE, 75);
    set_skill(SS_WEP_KNIFE, 60);
    set_skill(SS_2H_COMBAT, 75);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_PARRY, 75);
    set_skill(SS_AWARENESS, 30);
    set_act_time(6);
    add_act("peer all");
    add_act("say Beware.");
    add_act("emote scratches his chin in thought.");
    add_act("emote adjusts his armour.");
    set_cact_time(3);
    add_cact("shout Fellow guardsmen, come to my aid!");
    add_cact("say You will die for this cowardly attack, you miserable cur.");
    add_cact("scream");
    add_cact("say Filthy savage!!");
    add_cact("say Scum, I'll make you wish you'd never been born.");
    add_speak("Only if you are trustworthy enough may you pass me.\n");
    set_knight_prestige(-3);
    set_default_answer("The guardsman of Kabal says: What?\n");
    add_ask(({"captain"}), "The guardsman of Kabal says: That would be Hahmal.\n");
    add_ask(({"pass", "passing"}), "The guardsman of Kabal says: If you "+
      "are trustworthy enough, you may pass.\n");
    add_prop(NPC_I_NO_RUN_AWAY, 1);
}

void
arm_me()
{
    object wep, arm;
    int i;
    string extra;
    extra = random_extra();
    seteuid(getuid(TO));
    arm = clone_object(ARM + "gchain");
    arm->move(TO);
    arm = clone_object(ARM + "ghelm");
    arm->move(TO);
    command("wear all");
    wep = clone_object(extra);
    wep->move(TO);
    wep = clone_object(WEP + "gdagger");
    wep->move(TO);
    command("wield all");
    MONEY_MAKE_GC(random(4))->move(TO, 1);
    MONEY_MAKE_SC(random(10)+5)->move(TO, 1);
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("say Villanous wretch! Die!");
	command("spit " + OB_NAME(ob));
	command("kill " + OB_NAME(ob));
    }
}

int
pass()
{
    if(TP->query_alignment() < 1)
    {
	write("You try to pass the guardsman of Kabal but are stopped.\n");
	write("The guardsman of Kabal says: You may not pass, evil one!\n");
	say(QCTNAME(TP) + " tries to pass the guardsman of Kabal but is stopped.\n");
	say("The guardsman of Kabal says: You may not pass, evil one!\n");
	write("It looks like you'll have to find another way up.\n");
	return 1;
    }

    write("The guardsman of Kabal allows you to pass.\n");
    write("The guardsman of Kabal ushers you upstairs.\n");
    say("The guardsman of Kabal allows " + QTNAME(TP) + " to pass.\n");
    say("The guardsman of Kabal ushers " + QTNAME(TP) + " upstairs.\n");
    TP->move_living("up the stairs", CVAN + "gateway/tower2");
    return 1;
}

int
special_attack(object ob)
{
    string phurt;
    mixed *hitres;

    if(random(100) > 75)
    {
	if(query_combat_object()->cb_tohit(-1, 65 + random(25), ob) < 1)
	    return 0;

	if(!sizeof(query_weapon(-1)))
	    return 0;

	hitres = ob->hit_me(random(200)+100, W_BLUDGEON, TO, -1);
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

void
init_living()
{
    ::init_living();
    AA(pass, pass);
}
