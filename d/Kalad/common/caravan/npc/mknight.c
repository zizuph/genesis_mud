/*
 *  
 * Cotillion - 2019-04-03
 * - Changed to clone_unique
 */
#include "default.h"

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
inherit "/lib/unique";

void
create_kalad_monster()
{
    set_default_answer("What are you speaking of?!? Bloody fool!!!\n");
    add_ask(({"knights", "thanar knights", "holy order of thanar", "thanarians"}),
      "We shall force all of Kalad under the rule of Lord Thanar, greatest "+
      "of the gods!\n");
    add_ask(({"war"}),
      "Ahh, it shall be glorious. All the barbaric demihumans shall be "+
      "cleansed from this city.\n");
    set_name("artharkan");
    add_name("knight");
    set_race_name("human");
    set_adj("deadly");
    add_adj("commanding");
    set_long("An aura of complete confidence radiates from this man. His "+
      "regal looks cannot hide the seething anger and cruel nature of his "+
      "black-hearted soul. From his eyes can be seen but one thing...death.\n");
    set_stats(({150, 150, 150, 100, 100, 150}));
    set_alignment(-1000);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    set_title("the Master Knight of Thanar");
    set_act_time(3);
    add_act("ponder");
    add_act("emote gazes at a map of Kalad.");
    add_act("think the death and destruction soon to come");
    add_act("grin dem");
    add_act("swing");
    add_act("say It is the destiny of the human race to conquer the "+
      "lesser races of elves, dwarves, gnomes, hobbits and goblins.");
    set_cact_time(2);
    add_cact("say Now, someone to test my battle prowess against!");
    add_cact("laugh loud");
    add_cact("say You cannot hope to defeat a Master Knight of Thanar.");
    add_cact("say Such a pitiful fighter you are! I surpassed such "+
      "pitiful fighting when I was but a boy of twelve summers!!");
    add_cact("say You're almost too pitiful to kill!");
    add_cact("thanaraidme");
    add_speak("The coming war will result in the total expulsion of "+
      "demihumans from Kabal!\n");
    set_knight_prestige(1000);
    MONEY_MAKE_PC(random(3))->move(TO, 1);
    MONEY_MAKE_GC(random(10))->move(TO, 1);


    equip(({ 
                (ARM + "mkhelm"),
                (ARM + "mkplate"),
                (ARM + "mkgaunt"),
                (ARM + "mkgreav"),
                (ARM + "mkcloak"),
                (ARM + "ktmed"),
                (OBJ + "npc_symbol"),
                clone_unique(WEP + "mksword", 8, WEP + "lksword")
    }));
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

    hitresult = enemy->hit_me(700, W_BLUDGEON, me, -1);
    how = " without effect";
    if (hitresult[0] > 0)
	how == "";
    if (hitresult[0] > 10)
	how = " hard";
    if (hitresult[0] > 20)
	how = " very hard";
    if (hitresult[0] > 30)
	how = " extremely hard";
    if (hitresult[0] > 35)
	how = " with such force, the sound of bones and internal organs exploding can be heard";
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
do_peer(object obj)
{
    object who;

    if (who=present(obj, environment()))
    {
	command("peer "+ (who->query_real_name()));
    }
}

void
help_friend(object ob)
{
    if(ob && !query_attack() && present(ob, environment()))
    {
	command("say May Thanar have mercy on your soul...");
	command("grin mer");
	command("kill " + OB_NAME(ob));
    }
}

void
init_living()
{
    set_alarm(1.0, 0.0, &do_peer(TP));
}
