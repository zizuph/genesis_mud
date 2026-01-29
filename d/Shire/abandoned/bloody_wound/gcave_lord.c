#include "../local.h"
#include <wa_types.h>

inherit GOBLIN_BASE;
inherit KILL_LOGGER;

void create_goblin()
{
    set_name("Goblin Lord");
    set_base_gob(140);
    set_ran_gob(30);
#ifndef LORD_WIELDS_HALBERD
    set_ran_wep(({ "club" }));
    set_ran_arm(({ "shield" }));
    set_def_arm(({ "mail", "helm" }));
#else
    add_equipment(({MISTY_WEP_DIR + "halberd_sup", MISTY_ARM_DIR + "helm_sup",
	MISTY_ARM_DIR + "mail_sup"}));
#endif
    set_looks(({ "lord" }));
    set_chats(({ "Get out of here!!!  I have called NOBODY!!!",
	"Do I have to call guards or should I kill you myself?",
	"How did you get here???",
	"I will stop giving food to those stupid guards that let you in!"
      }));
    set_c_chats(({ "I will smash your head you stupid worm!",
	"What do you think you are?" }));

    // We don't drop our weapons from a ranger brawl.
    add_prop("_ranger_m_no_disarm_drop", 1);
    // Kill logger
    set_kill_log_name("goblin_lord");
}

int special_attack(object enemy)
{
    string what;
    object bleeding, *weapons;
    string wep_short;

    if (!random(25))
    {
	what = ONE_OF(({"head","left arm","right arm","chest","stomach",
	    "left shoulder","left leg","right shoulder",
	    "right leg","neck"}));
#ifdef LORD_WIELDS_HALBERD
	weapons = query_weapon(-1);
	if (sizeof(weapons))
	    wep_short = weapons[0]->short();
	else
	    return 0;
	enemy->catch_msg(QCTNAME(TO) + " impales your "+what+" very hard with "+
	  HIS_HER(TO) +" "+ wep_short +".\n");
	tell_room(ENV(TO), QCTNAME(TO)+" impales "+QTNAME(enemy)+"'s "+what+
	  " very hard with "+HIS_HER(TO)+" " + wep_short + ".\n", enemy);

#else
	enemy->catch_msg(QCTNAME(TO) + " hits your "+what+ " very hard.\n");
	tell_room(ENV(TO),QCTNAME(TO)+" hits "+QTNAME(enemy)+"'s "+
	  what +" very hard.\n", enemy);
#endif
	if (objectp(bleeding = present("_bleeding_wound", enemy)))
	{
	    if (bleeding->query_bleeding_where() == what)
	    {
		bleeding->reset_wound();
		enemy->catch_msg("The force of the blow reopens your wound!\n");
		enemy->tell_watchers("The force of "+QTNAME(TO)+"'s blow "+
		  "reopens "+QTNAME(enemy)+"'s bloody wound.\n", TO);
	    }
	}
	else
	{
	    bleeding = clone_object(MISTY_OBJ_DIR+"bleeding");
	    bleeding->set_bleeding_where(what);
	    bleeding->move(enemy,1);
	}
	enemy->hit_me(query_stat(SS_STR)/2, W_IMPALE, TO, -1);
	return 1;
    }
    return 0;
}

int
query_is_goblin_lord()
{
    return 1;
}
