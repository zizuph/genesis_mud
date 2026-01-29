/*
 * Base class for a Neverwinter bridge guard 
 * by Kehr, October 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/lib/assist_friend";
inherit "/d/Faerun/lib/gems";
inherit "/lib/unique";

#define LOG "/d/Faerun/log/guard_combat"

#define RACE	({"human", "human", "dwarf", "elf"})
//#define WEAPON  ({"longsword", "battleaxe", "warhammer"})
#define WEAPON  ({"waraxe"})
#define SHIELD  ({"steel_shield"})
#define BOD_ARM ({"breastplate", "chainmail"})
//#define GREAVES ({"greaves", "greaves_i", "greaves_sp"})
//#define HELMET  ({""})

#define TYPE    ({"white-haired", "blue-eyed"})
#define PHYS    ({"tall", "muscular"})

#define NAME "guard"

#define FIGHT_SHIELD_WEP 1
#define FIGHT_WEP_WEP    2	 

int use_two_weapons() ;
int use_shield_weapon(); 

int fightmode;

void create_faerun_npc()
{
    string type, phys, race;
    int i;

    seteuid(getuid());

    npc_name = "guard";

    type = ONE_OF_LIST(TYPE);
    phys = ONE_OF_LIST(PHYS);
    race = ONE_OF_LIST(RACE);

    add_adj(type);
    add_adj(phys);

    set_race_name(race);
    add_name(NAME);

    set_short(phys + " " + type + " guard");
    set_pshort(phys + " " + type + " guards");
    set_long("This " + race + " is one of the guards whose task is to " + 
	"prevent people from approaching Neverwinter. He is strong and " + 
	"extremely confident in his abilities.\n");

    add_prop(CONT_I_WEIGHT,100000);
    add_prop(CONT_I_HEIGHT,200);
    add_prop(LIVE_I_SEE_DARK,10);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE,1);
    

    /* STR DEX CON INT WIS DIS */
    // these are soldiers, not wizards
    set_base_stat(0, 160 + random(25));
    set_base_stat(1, 130 + random(25));
    set_base_stat(2, 140 + random(25));
    set_base_stat(3, 80 + random(10));
    set_base_stat(4, 70 + random(10));

    //set_base_stat(0, 0 + random(25));
    //set_base_stat(1, 220 + random(25));
    //set_base_stat(2, 0 + random(25));
    //set_base_stat(3, 0 + random(10));
    //set_base_stat(4, 0 + random(10));
    // They are brave !
    set_base_stat(5, 160 + random(25));

    // everyone has a right to die here !
    set_alignment(0);

    set_skill(SS_UNARM_COMBAT,60);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_WEP_AXE,80);
    set_skill(SS_WEP_CLUB,80);
    set_skill(SS_WEP_SWORD,80);
    set_skill(SS_PARRY, 70);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_2H_COMBAT, 90);

   /* Actions */
    set_act_time(5);
    add_act("listen attent");
    add_act("watch");

    set_alarm(1.0,0.0,"arm_me");

    set_pick_up_team(({npc_name}));
}



void
arm_me()
{
    object arm, wep, gem;

    make_gems(TO, 1);

/*
    //arm ->move(this_object());
    arm = clone_object(ARM_DIR + ONE_OF_LIST(BOD_ARM));
    arm -> move(TO);
    arm = clone_object(ARM_DIR + ONE_OF_LIST(SHIELD));
    arm -> move(TO);
*/
    wep = clone_object(WEP_DIR + ONE_OF_LIST(WEAPON));
    wep -> move(TO);
    wep = clone_object(WEP_DIR + ONE_OF_LIST(WEAPON));
    wep -> move(TO);

//    arm = clone_object("/d/Krynn/common/armours/kite-shield.c");
//    arm -> move(TO);
    
    command("wear armours");
    command("wield weapon");

    fightmode = FIGHT_SHIELD_WEP;

}
void
init_living()
{
    ::init_living();
    init_team_pickup();
}

int use_two_weapons() 
{
	command("remove shield");
	command("wield all");
	return 0;
}

int use_shield_weapon() 
{
	command("unwield all");
	command("wear shield");
	command("wield all");
	return 0;
}

int special_attack(object enemy)
{
	object *enemies;
	int es, i;
	int flag=0;
	mixed *hitresult;

	// how many people do I defend from ?
	enemies = query_enemy(-1)->query_attack() & ({this_object()});
	es = sizeof (enemies);
	
	if (es == 0 && fightmode == FIGHT_SHIELD_WEP) {
		use_two_weapons();
		fightmode=FIGHT_WEP_WEP;
	} else if (es > 0 && fightmode == FIGHT_WEP_WEP) {
		use_shield_weapon();
		fightmode=FIGHT_SHIELD_WEP;
	}
	
	// lets punish mega tankers
//	dump_array(({TO}));
//	dump_array(query_attack()->query_enemy(-1));
	i = member_array(TO, query_attack()->query_enemy(-1));
	if (i>2) {
		write("You really think you can handle so much ? The guard " +
			"smiles wickedly and calls hit_me for you !\n");
		hitresult = enemy->hit_me(100, W_SLASH, TO, -1);
	}
	
	return 0;
}

// Mercade: filter(query_enemy(-1), &operator(==)(, 
// this_object()) @ &->query_attack());
// <CodeHelp> 00:40 Mercade: query_enemy(-1)->query_attack & ({ this_object() })
//

void update_internal(int a, int b, int c)
{
	tell_room(TO, "something changed\n");

}
