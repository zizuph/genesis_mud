/* Removed the wound and added a different special.
 *  Igneous Jan 7th 1998
 * Added UNIQUE_WEAPON code to limit number of JBS in the game
 *  to a total of 10.
 *  Jaypeg Apr 99
 * Added global var MAX_UNIQUE_ITEMS to regulate max number of 
 *  halberds in game
 *  Finwe, October 2001
 */

#include "../local.h"
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>
#include <ss_types.h>
#include "/d/Shire/sys/defs.h"

inherit GOBLIN_BASE;
inherit KILL_LOGGER;
inherit "/lib/unique";

// Prototypes
void check_stats();

static int Armed = 0;

void create_goblin()
{
    set_name("Goblin Lord");
     add_name("lord");
//    add_name("_misty_goblin_");
    set_base_gob(150);
    add_adj("goblin lord");
    add_adj("huge");
    add_adj("lord");
    set_ran_gob(25);
#ifndef LORD_WIELDS_HALBERD
    set_ran_wep(({ "club" }));
    set_ran_arm(({ "shield" }));
    set_def_arm(({ "mail", "helm" }));
#else
    add_equipment(({ARM_DIR + "helm_sup", ARM_DIR + 
	"mail_sup" }));
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

    // Do a quick stat check to make sure he doesn't have them
    // set below a certain value.
    set_alarm(0.1,0.0,&check_stats());
}

void
arm_shire_npc()
{
    object wep;

    if (!Armed)
    {
	wep = clone_unique(WEP_DIR + "halberd_sup", MAX_UNIQUE_ITEMS, 
	  WEP_DIR + "pole_high");
	wep->move(this_object());
	Armed = 1;
    }
    ::arm_shire_npc();
}

void
check_stats()
{
    set_base_stat(SS_STR, MAX(150, query_base_stat(SS_STR)));
    set_base_stat(SS_DEX, MAX(140, query_base_stat(SS_DEX)));
    set_base_stat(SS_CON, MAX(160, query_base_stat(SS_CON)));
    refresh_mobile();
}


int
query_is_goblin_lord()
{
    return 1;
}

void
check_my_weapon() 
{
    if (!query_skill(SS_UNARM_COMBAT) && !sizeof(query_weapon(-1)))
    {
	set_skill(SS_UNARM_COMBAT, 94);
	map(query_combat_object()->query_attack_id(), cr_reset_attack);
    }
    else
    if (query_skill(SS_UNARM_COMBAT))
    {
	remove_skill(SS_UNARM_COMBAT);
	map(query_combat_object()->query_attack_id(), cr_reset_attack);
	map(query_weapon(-1), update_weapon);
    }
}

int
find_valid_enemy(object foe)
{
    if (ENV(foe) != ENV(TO))   
	return 0;
    if (!sizeof(foe->query_weapon(-1)))
	return 0;

    // Passed all checks.    
    return 1;
}

int
special_attack(object ob)
{
    object *foes, *weapons, *my_weapons, weapon;

    check_my_weapon();

    if (random(7))
	return 0;
    my_weapons = query_weapon(-1);
    weapons = ob->query_weapon(-1);

    // If I have no weapon wielded I can't do this attack.
    if (!sizeof(my_weapons))
    {
	// Posibily do an unarmed attack here?
	return 0;
    }

    // My enemy has no weapon so lets look for another :)
    if (!sizeof(weapons))
    {
	if (!sizeof(foes = filter(query_enemy(-1), find_valid_enemy)))
	    return 0;
	ob = foes[random(sizeof(foes))];
	weapons = ob->query_weapon(-1);
    }

    // Sanity check
    if (!sizeof(weapons))
	return 0;
    // What weapon are we attacking.
    weapon = weapons[random(sizeof(weapons))];

    // Do we hit with this attack?
    if (query_combat_object()->cb_tohit(-1,100,ob) >= 0)
    {
	if (!weapon->query_prop(OBJ_I_IS_MAGIC_WEAPON))
	{
	    // See if we are able to break non-magical weapons.
	    if (resolve_task(TASK_DIFFICULT, ({TS_DEX, SS_WEP_POLEARM}), ob,
		({SKILL_AVG, TS_DEX, TS_WIS, SKILL_END, SS_PARRY})) >= 0)
	    {
		ob->catch_tell("The "+query_nonmet_name()+" strikes your "+
		  weapon->short()+" with "+HIS_HER(TO)+" "+
		  my_weapons[0]->short()+" with tremendous force damaging "+
		  "your "+weapon->short()+" beyond repair.\n");
		tell_room(ENV(TO), QCTNAME(TO) + " strikes "+QTNAME(ob)+
		  "'s "+weapon->short()+" with "+HIS_HER(TO)+" "+
		  my_weapons[0]->short()+" with tremendous force damaging "+
		  QTNAME(ob)+"'s "+weapon->short()+" beyond repair.\n", 
		  ({TO,ob}));
		weapon->remove_broken();
		return 1;
	    }
	}
	ob->catch_tell("The "+query_nonmet_name()+" strikes your "+
	  weapon->short()+" with "+HIS_HER(TO)+" "+
	  my_weapons[0]->short()+" leaving your "+weapon->short()+
	  " somewhat damaged from the blow.\n");
	tell_room(ENV(TO), QCTNAME(TO) + " strikes "+QTNAME(ob)+
	  "'s "+weapon->short()+" with "+HIS_HER(TO)+" "+
	  my_weapons[0]->short()+" leaving "+QTNAME(ob)+"'s "+
	  weapon->short()+" somewhat damaged by the blow.\n",({TO,ob}));
	// The weapon condition gets worse by 1-2 levels.
	weapon->set_dull(weapon->query_dull() + random(2) + 1); 
	return 1;
    }
    else
    {
	// Damn we missed so nothing bad happens.. but lets let people
	// know we tried to do something.
	ob->catch_tell("The "+query_nonmet_name()+" attempts to strike "+
	  "your "+weapon->short()+" with "+HIS_HER(TO)+" "+
	  my_weapons[0]->short()+", but you manage to avoid the blow.\n");
	tell_room(ENV(TO), QCTNAME(TO) + " attemptes to strike "+QTNAME(ob)+
	  "'s "+weapon->short()+" with "+HIS_HER(TO)+" "+
	  my_weapons[0]->short()+", but "+QTNAME(ob)+" manages to "+
	  "avoid the blow.\n",({TO,ob}));    
	return 1;
    }
    return 1;
}
