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

#define FIGHT_SHIELD_WEP 1
#define FIGHT_WEP_WEP    2	 

int use_two_weapons() ;
int use_shield_weapon(); 

int fightmode;

void set_level(int sta, int ska);

void create_faerun_npc()
{
    int i;

    seteuid(getuid());


    set_race_name("human");
    set_short("base smart npc");
    set_pshort("base smart npcs");
    set_long("This is Kehr's base smart npc. This description should be customized.\n");

    add_prop(CONT_I_WEIGHT,80000+random(20000));
    add_prop(CONT_I_HEIGHT,160+random(20)+random(20));
    add_prop(LIVE_I_SEE_DARK,0);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE,1);
    
    set_alignment(0);
	
	// You REALLY need to call this yourself !
	//set_level (1,0);

    set_alarm(1.0, 0.0, "equip_me");
}

/* Sets stats and some skills around given averages
 * sta - stats average
 * ska - skill average
 *
 * WARNING - biased to create "warrior-type" npc's (higher str,dex,con and dis, lower wis and int)
 *           actual stat average might be up to 10% higher
 *			 
 */


void set_level(int sta, int ska) {
	
	int tmp;

	tmp = sta/10;
	
    set_base_stat(0, 110*sta/100 + random(tmp));
    set_base_stat(1, 120*sta/100 + random(tmp));
    set_base_stat(2, 120*sta/100 + random(tmp));
    set_base_stat(3,  70*sta/100 + random(tmp));
    set_base_stat(4,  80*sta/100 + random(tmp));
    set_base_stat(5, 100*sta/100 + random(tmp));
	
	tmp = ska/10;
    set_skill(SS_UNARM_COMBAT,	 80*ska/100 + random(tmp));
    set_skill(SS_DEFENCE,	 90*ska/100 + random(tmp));
    set_skill(SS_WEP_AXE,	100*ska/100 + random(tmp));
    set_skill(SS_WEP_CLUB,	100*ska/100 + random(tmp));
    set_skill(SS_WEP_SWORD,	100*ska/100 + random(tmp));
    set_skill(SS_WEP_POLEARM,	100*ska/100 + random(tmp));
    set_skill(SS_PARRY, 	 90*ska/100 + random(tmp));
    set_skill(SS_AWARENESS, 	 80*ska/100 + random(tmp));
    set_skill(SS_2H_COMBAT, 	 90*ska/100 + random(tmp));

}

void
equip_me()
{
    object torch;
    
    torch = clone_object("/std/torch");
    torch -> set_short("wooden torch");
    torch -> set_long("It is a plain wooden torch that will burn for a while.\n");
    
    torch -> move (this_object());
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
