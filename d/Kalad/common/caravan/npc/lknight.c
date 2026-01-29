/*
*  Modified by Zignur 2017-09-20
*  Mirandus 2018-02-13 -  Added some actions indicating that he disagrees 
*  with the new stance of the Thanar Order which allows for it to make 
*  sense for him to remain below. He still wishes to carry out what 
*  he believes are the true plans of Thanar.
*/

#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

string
random_extra()
{
    int i = random(30);

    if (i < 3)
	return "stefell";
    else if (i < 6)
	return "boris";
    else if (i < 7)
	return "adroon";
    else if (i < 8)
	return "jarguss";
    else if (i < 9)
	return "chandyl";
    else if (i < 10)
	return "noormin";
    else if (i < 11)
	return "febbo";
    else if (i < 12)
	return "amrocar";
    else if (i < 13)
	return "andir";
    else if (i < 14)
	return "ulf";
    else if (i < 15)
	return "gorcil";
    else if (i < 16)
	return "brit";
    else if (i < 17)
	return "delniel";
    else if (i < 18)
	return "wilhelm";
    else if (i < 19)
	return "obildur";
    else if (i < 20)
	return "tandel";
    else if (i < 21)
	return "ardindel";
    else if (i < 22)
	return "mitus";
    else if (i < 23)
	return "lingorr";
    else if (i < 24)
	return "landil";
    else if (i < 25)
	return "kathin";
    else if (i < 26)
	return "baern";
    else if (i < 27)
	return "sinhmaar";
    else if (i < 28)
	return "rekgan";
    else
	return "fellir";
}

void
create_kalad_monster()
{
    string extra;
    extra = random_extra();
    set_name(extra);
    add_name("knight");
    add_name("warrior");
    set_race_name("human");
    set_adj("alert");
    add_adj("disciplined");
    set_long("An impressive-looking individual, he looks well-trained in "+
      "the arts of combat. You notice his keen eyes carefully appraising "+
      "your value as an opponent.\n");
 
    /* New stats changed by Zignur 2017-09-20 */  
    set_stats(({95,95,95,95,95,95}));
    set_alignment(-750);
    /* New skills changed by Zignur 2017-09-20*/
    set_skill(SS_WEP_SWORD, 80);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_PARRY, 80);
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_BLIND_COMBAT,50);
    
    set_title("the Warrior Knight of Thanar");
    set_act_time(6);
    add_act("emote carefully appraises you as an opponent.");
    add_act("say We Knights despise the lesser races.");
    add_act("say The leadership has sold out. I shall make them pay.");
    add_act("grin menacingly all");
    add_act("say Those damn fools. They've cowed to the pressure.");
    add_act("say I will never agree to return to the Cathedral.");
    add_act("say The Chosen Priest has made a mistake.");
    set_cact_time(3);
    add_cact("say I promise you a slow and painful death.");
    add_cact("say Fool! You shall die for attacking me!");
    add_speak("Leave.\n");
    set_knight_prestige(750);
    MONEY_MAKE_GC(random(3))->move(TO, 1);
    
    /* XP Adjustment, because of their special Zignur 2017-09-20 */
    set_exp_factor(120);    
}

void
arm_me()
{
     // Add some equipment
     /* Use the function equip instead Zignur */
    equip(({
    ARM + "lkhelm",
    ARM + "lkchain",
    WEP + "lksword",
      }));
      
    command("wield all");
    command("wear all");
    
}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
    command("say For Thanar!");
    command("kill " + OB_NAME(ob));
    }
}

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    me = this_object();
    if (random(10))
    return 0;
    hitresult = enemy->hit_me(100 + random(200), W_BLUDGEON, me, -1);
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
