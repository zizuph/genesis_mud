/*
 * Avatar of Thanar
 * 
 * Cotillion - 2019-04-03
 * - Changed to use global clone_unique
 */
#include "default.h"

inherit "/lib/unique";
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

/* This is the avatar of the god, Thanar */

void
create_kalad_monster()
{
    set_name("abbathor");
    set_living_name("_thanar_demon_");
    set_race_name("demon");
    set_adj("greater");
    add_adj("thanarian");
    set_long("A mighty figure of towering proportions. This being stands "+
      "a full twelve feet in height, with rippling muscles clearly visible "+
      "on his unarmored body. A mere glimpse at his face, with its glittering "+
      "red eyes and unforgiving stare, and you know that this being "+
      "possesses might far beyond that of the mightiest of mortals.\n");

    set_stats(({200, 200, 200, 135, 135, 150}));
    set_all_hitloc_unarmed(40);

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_SPELLCRAFT, 100);

    set_knight_prestige(1200);
    set_alignment(-1200);
    set_act_time(3);
    set_title("the Greater Demon of Thanar, Thanar's Sword of Vengence");

    add_act("grin demon");
    add_act("emote sneers in contempt at you.");
    add_act("emote seems to focus his attention inward.");
    add_act(({"kill elf", "kill dwarf", "kill gnome", "kill hobbit", 
    "kill goblin", "kill half-elf", "kill saurian"}));
    add_speak("He shall arise again!\n");
    set_cact_time(1);
    add_cact("command ranaht");
    add_cact("say Thanar is the most powerful god in Kalad!");
    add_cact("emote laughs at you in complete and utter contempt.");
    add_cact("laugh dem");
    add_cact("smirk");
    add_cact("command ranaht");
    add_cact("command dilvardyn");

    set_default_answer("The demon says: I don't answer foolish questions!\n");
    add_ask(({"thanar"}), "The demon says: I represent the reatest god in "+
      "all of Kalad, noone can withstand my wrath!\n");
    add_ask(({"kabal", "kalad"}), "The demon says: Thanar shall rule all of "+
      "it, all of it!\n");

    set_random_move(10);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_SEE_INVIS, 99);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    /*
       trig_new("%w 'kicks' 'you' %s", "react_attack");
       trig_new("%w 'pats' 'you' %s", "react_attack");
       trig_new("%w 'spits' 'on' 'you!\n' %s", "react_attack");
    */

    equip(({ 
        clone_unique(WEP + "sword_of_thanar", 4, WEP + "lksword"),
        OBJ + "a_t_object"
    }));
}

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;

    me = TO;

    if(random(3))
	return 0;

    hitresult = enemy->hit_me(850, W_BLUDGEON, me, -1);
    how = " with little effect";

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
	how = " with supreme and unholy godly might";

    me->catch_msg("You crush your opponent!\n"+
      capitalize(enemy->query_pronoun()) + " is hit" +
      how + ".\n");
    enemy->catch_msg(QCTNAME(me) + " aims a crushing blow at you!\n"+
      "You are hit" + how + ".\n");
    tell_watcher(QCTNAME(me) + " aims a crushing blow at " + QTNAME(enemy) + "!\n"+
      capitalize(enemy->query_pronoun()) + " is hit" +
      how + ".\n", enemy);

    if(enemy->query_hp() <= 0)
	enemy->do_die(me);

    return 1;
}

void
do_die(object killer)
{
    if(query_hp() > 0) return;

    write("Without warning, a sudden blast of pure and unholy energy "+
      "bathes the area with its terrible force. You watch in utter terror as "+
      "horrific creatures suddenly materialize before you, their leering "+
      "grins indicating their desire to possess your very soul!!!\n");
    say("Without warning, a sudden blast of pure and unholy energy "+
      "bathes the area with its terrible force. You watch in utter terror as "+
      "horrific creatures suddenly materialize before you, their leering "+
      "grins indicating their desire to possess your very soul!!!\n");


    int clones = 3;
    while (clones--) 
    {
        object demon = clone_object(NPC + "demon");
        demon->move(environment(TO));
    }

    ::do_die(killer);
}

void
return_attack(string who)
{
    object obj;
    int ran;

    if(obj = present(who, environment()))
    {
	command("emote snarls in outrage!!");
	command("say Die you miserable wretch!");
	command("kill " + OB_NAME(obj));
    }
}

int
react_attack(string who, string dummy)
{
    if(who)
    {
	who = lower_case(who);
	set_alarm(2.0, 0.0, &return_attack(who));
	return 1;
    }
}
