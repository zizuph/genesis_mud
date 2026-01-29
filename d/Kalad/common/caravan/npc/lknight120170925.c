#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    set_name("knight");
    add_name("guardian knight");
    set_race_name("human");
    set_adj("impressive");
    add_adj("well-trained");
    set_short("guardian knight of Thanar");
    set_long("An impressive-looking individual that possesses the keen "+
      "senses and instincts of someone that has trained all their life for "+
      "combat. Tattoed onto his forehead is a symbol of a dark sun.\n");
    set_stats(({100, 90, 100, 75, 75, 100}));
    set_alignment(-750);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 90);
    set_skill(SS_AWARENESS, 90);
    set_act_time(6);
    add_act("emote pledges anew his blade to the cause of Thanar.");
    add_act("emote sneers in contempt at the thought of the lesser non-human races.");
    add_act("emote makes a joke at the expense of hobbits.");
    add_act("glare all");
    add_act("say Only the faithful of Thanar may pass me.");
    set_cact_time(3);
    add_cact("say I will slay you quickly, that you may meet whatever "+
      "pitiful god it is that you worship!");
    add_cact("emote sings out a battlecry to Thanar!");
    add_cact("snarl all");
    add_cact("say Is that the best you've got! You misbegotten child of a hobbit cow!!");
    add_cact("say Hahaha! My blade shall split you like a newborn hobbit babe!");
    add_cact("say Hahahaha! You fight like a pitiful gnome!");
    add_speak("You may not pass...unless of course I suddenly found a "+
      "bit of gold in my possession.\n");
    set_knight_prestige(875);
    set_default_answer("The guardian knight of Thanar says: What?!?\n");
    add_ask(({"pass", "passage"}), "The guardian knight of Thanar says: Give me "+
      "one little gold coin...and I'll let you pass.\n");
    MONEY_MAKE_GC(random(4))->move(TO, 1);
    trig_new("%w 'gives' 'you' 'a' 'gold' 'coin.\n' %s", "react_leave");
    trig_new("%w 'gives' 'you' 'two' 'gold' 'coins.\n' %s", "react_leave");
    trig_new("%w 'gives' 'you' '12' 'silver' 'coins.\n' %s", "react_leave");
    trig_new("%w 'boldly' 'thrusts' %s", "react_symbol");
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
}

int
pass()
{
    object *ob;
    int i;
    ob = deep_inventory(TP);
    for(i = 0; i < sizeof(ob); i++)
	if(ob[i]->id("_sniff_my_licker"))
	{
	    write("You head deeper into the Thanarian headquarters.\n");
	    TP->move_living("east", CVAN + "lot/ur9");
	    return 1;
	}

    write("You cannot get past the knight!\nYou are stuck here.\n");
    return 1;
}

void
arm_me()
{
    object wep, arm;
    seteuid(getuid(TO));
    arm = clone_object(ARM + "lkhelm");
    arm->move(TO);
    arm = clone_object(ARM + "lkchain");
    arm->move(TO);
    command("wear all");
    wep = clone_object(WEP + "lksword");
    wep->move(TO);
    command("wield all");
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("shout For the glory of Thanar!!!");
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

    hitresult = enemy->hit_me(200 + random(200), W_BLUDGEON, me, -1);
    how = " without effect";

    if (hitresult[0] > 0)
	how == "";
    if (hitresult[0] > 10)
	how = " hard";
    if (hitresult[0] > 20)
	how = " very hard";

    me->catch_msg("You bodyslam your opponent!\n"+
      capitalize(enemy->query_pronoun())+" is bodyslammed"+
      how + ".\n");
    enemy->catch_msg(QCTNAME(me) + " bodyslams you!\n"+
      "You are bodyslammed" + how + ".\n");
    tell_watcher(QCTNAME(me) + " bodyslams " + QTNAME(enemy) + "!\n"+
      capitalize(enemy->query_pronoun()) + " is bodyslammed"+
      how + ".\n", enemy);

    if (enemy->query_hp() <= 0)
	enemy->do_die(me);

    return 1;
}

void
return_leave(string who)
{
    object obj;
    int ran;

    if(obj = present(who, environment()))
    {
	command("grin greedily");
	command("say Alright, you may pass now...");
	obj->move_living("east further down the hallway", CVAN + "lot/ur9");
    }
}

int
react_leave(string who, string dummy)
{
    if(who)
    {
	who = lower_case(who);
	set_alarm(3.0, 0.0, &return_leave(who));
	return 1;
    }
}

void
return_symbol(string who)
{
    object obj;
    int ran;

    if(obj = present(who, environment()))
    {
	command("beg " + OB_NAME(obj));
	command("say Forgive me, " + capitalize(obj->query_real_name()) + ", I did not realize it was you.\n");
	command("bow " + OB_NAME(obj));
	command("say You can pass.");
	obj->move_living("east further down the hallway", CVAN + "lot/ur9");
    }
}

int
react_symbol(string who, string dummy)
{
    if(who)
    {
	who = lower_case(who);
	set_alarm(3.0, 0.0, &return_symbol(who));
	return 1;
    }
}

void
init_living()
{
    ::init_living();
    AA(pass, pass);
}
