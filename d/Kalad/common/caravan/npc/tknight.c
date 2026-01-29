/* Added some actions indicating that he disagrees with the new stance
*  of the Thanar Order which allows for it to make sense for him to remain
*  below. He still wishes to carry out what he believes are the true plans
*  of Thanar.
*/
#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#include <filter_funs.h>

int heal;

void
create_kalad_monster()
{
    int i;

    set_name("temer");
    add_name("wizard");
    add_name("knight");
    set_race_name("human");
    set_adj("terrible");
    set_short("terrible wizard");
    set_long("A terrible great human wizard. He looks unbeatable and you feel "+
      "evil radiating from him. He stares at you with unmitigated hatred "+
      "and bloodlust, as if daring an insignificant mortal such as yourself to dare "+
      "the unthinkable act of challenging him to a fight.\n"+
      "He is wearing a velvet black robe and a medallion of thanar.\n");

    for (i = 0; i < 5; i++)
	set_base_stat(i, 90 + random(20));
    set_base_stat(5, 100);

    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_CLIMB, 50);
    set_skill(SS_AWARENESS, 60);
    set_alignment(-1200);
    set_knight_prestige(950);
    set_act_time(3);
    add_act("say Insolent worms, noone can withstand my wizardly might.");
    add_act("smirk");
    add_act("say The leadership has sold out. I shall make them pay.");
    add_act("grin menacingly all");
    add_act("say Those damn fools. They've cowed to the pressure.");
    add_act("say I will never agree to return to the Cathedral.");
    add_act("say The Chosen Priest has made a mistake.");
    add_act("cackle dem");
    add_speak("Thanar shall rule over all creation.\n");

    add_prop(LIVE_I_SEE_DARK, 1000);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_alarm(1.0, 0.0, "arm_me");
    set_title("the Thorn Knight of Thanar");
}

void
arm_me()
{
    object wep, arm;
    seteuid(getuid(TO));
    arm = clone_object(ARM + "tkrobe");
    arm->move(TO);
    arm = clone_object(ARM + "ktmed");
    arm->move(TO);
    arm = clone_object(OBJ + "npc_symbol");
    arm->move(TO);
    command("wear all");
    MONEY_MAKE_PC(random(5))->move(TO, 1);
}

tell_watcher(string str, object enemy)
{
    object me, *ob;
    int i;

    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
	if (ob[i]->query_see_blood())
	    ob[i]->catch_msg(str);
}

int
special_attack(object enemy)
{
    int attacktype, i, penet;
    mixed* hitresult;
    string how;
    object me, *ob;
    me = this_object();

    attacktype = random(5);
    if (attacktype == 1)
    {
	ob = FILTER_OTHER_LIVE(all_inventory(environment(me)));

	for (i = 0; i < sizeof(ob); i++)
	{
	    penet = 500 + random(500);
	    penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_FIRE) / 50;
	    hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);

	    how = "not harmed";
	    if (hitresult[0] > 0)
		how == "barely burned";
	    if (hitresult[0] > 10)
		how = "slightly burned";
	    if (hitresult[0] > 20)
		how = "burned quite badly";
	    if (hitresult[0] > 40)
		how = "burned very badly";
	    if (hitresult[0] > 60)
		how = "utterly devastated";

	    ob[i]->catch_msg("You hear a rhythmic chanting and then a deadly eruption "+
	      "of hellish fire shoots forth from the wizard's hands at you!\n");
	    ob[i]->catch_msg("You were " + how + " by the fireball!\n");
	    tell_watcher(QCTNAME(ob[i]) + " is " + how + " by the fireball!\n", ob[i]);

	    if (ob[i]->query_hp() <= 0)
		ob[i]->do_die(me);
	}

	return 1;
    }

    if (attacktype == 2)
    {
	if (heal == 5)
	{
	    return 0;
	}

	heal += 1;
	write("The terrible wizard mumbles a few words.\n"+
	  "The terrible wizard now looks much healthier!\n");
	say("The terrible wizard mumbles a few words.\n"+
	  "The terrible wizard now looks much healthier!\n");
	me->heal_hp(1250);
	return 1;
    }
    return 0;
}
