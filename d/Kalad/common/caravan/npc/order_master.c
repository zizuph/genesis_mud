#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

void
create_kalad_monster()
{
    set_name("milhaard");
    add_name("master");
    add_name("order master");
    set_race_name("human");
    set_adj("loyal");
    add_adj("powerful");
    set_long("He is a powerfully built human of an indeterminate age, the only "+
      "noticeable feature is the image of a dark sun on his forehead, "+
      "which indicates that he belongs to the Holy Order of Thanar. You "+
      "realize that he is guarding this room of the Thanar hideout.\n");
    set_stats(({125, 100, 125, 75, 75, 100}));
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    set_alignment(-1000);
    set_act_time(3);
    add_act("grin");
    add_act("say Thanar is my master.");
    add_act("think killing some hobbits and gnomes.");
    add_act("say Intruders in my master's home DIE.");
    add_act("say No fighting is allowed here in the sacred chamber.");
    add_speak("I have nothing more to say to you.\n");
    set_cact_time(3);
    add_cact("emote screams an unholy battle cry!");
    add_cact("say Thanar shall be pleased that I slayed you!");
    set_title("the Master of the Holy Order of Thanar");
    set_knight_prestige(1000);
    set_default_answer("The master says: I do not know what you speak of.\n");
    add_ask(({"order", "thanar"}), "The master says: We are the greatest "+
      "organization in all of Kalad. We seek to rid this world of the foul "+
      "non-humans so that humanity may rule all of creation!\n");
    trig_new("%w 'leaves' 'the' 'Holy' 'Order' %s", "react_leave");
    trig_new("%w 'attacks' %s", "react_attack");
}

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    me = this_object();
    if (random(5))
	return 0;
    hitresult = enemy->hit_me(500 + random(500), W_BLUDGEON, me, -1);
    how = " without effect";
    if(hitresult[0] > 0)
	how == "";
    if(hitresult[0] > 10)
	how = " hard";
    if(hitresult[0] > 20)
	how = " very hard";
    if(hitresult[0] > 30)
	how = " extremely hard";
    if(hitresult[0] > 40)
	how = " terrifyingly hard";
    if(hitresult[0] > 50)
	how = " with supreme unholy might";
    me->catch_msg("You kick your opponent!\n" +
      capitalize(enemy->query_pronoun()) + " is kicked" +
      how + ".\n");
    enemy->catch_msg(QCTNAME(me) + " kicks you!\n" +
      "You are kicked" + how + ".\n");
    tell_watcher(QCTNAME(me) + " kicks " + QTNAME(enemy) + "!\n" +
      capitalize(enemy->query_pronoun()) + " is kicked" +
      how + ".\n", enemy);
    if(enemy->query_hp() <= 0)
	enemy->do_die(me);
    return 1;
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
	command("say Thanar shall slay you for that!");
	command("kill " + OB_NAME(ob));
    }
}

void
return_leave(string who)
{
    object obj;
    int ran;

    if(obj = present(who, environment()))
    {
	command("say Traitors to the Order must die!");
	command("say Die " + capitalize(obj->query_real_name()) + "!");
	command("kill " + OB_NAME(obj));
    }
}

int
react_leave(string who, string dummy)
{
    if(who)
    {
	who = lower_case(who);
	set_alarm(1.0, 0.0, &return_leave(who));
	return 1;
    }
}

void
return_attack(string who)
{
    object obj;
    int ran;
    if(obj = present(who, environment()))
    {
	command("say I warned you not to fight here!!!");
	command("say Now you shall die!!!");
	obj->catch_msg("You feel as if your soul is being drained away!\n");
	say(QCTNAME(TP) + " looks visibly weaker.\n");
	obj->heal_hp(-1000);
    }
}

int
react_attack(string who, string dummy)
{
    if(who)
    {
	who = lower_case(who);
	set_alarm(1.0, 0.0, &return_attack(who));
	return 1;
    }
}
