/*
	*Maggot's dog, Grip
	*Altrus, April 2005
 *
 * 2005/04/29 Last update
 * 2011/08/02 Lavellan - Changed monster to creature so hitlocs/attacks work
 *                     - Improved descriptions and chances for them too
 *                     - Removed quickness and see invis (it's a dog!)
*/
//inherit "/std/monster";
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/attack";
//inherit "/cmd/std/command_driver";
inherit "/d/Shire/common/lib/tell";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <composite.h>
#include "/d/Shire/sys/defs.h"

#define A_BITE    0
#define A_LFPAW  1
#define A_RFPAW  2

#define H_BODY    0
#define H_BACK    1
#define H_HEAD    2
#define H_LFLEG  3
#define H_RFLEG  4
#define H_LHLEG  5
#define H_RHLEG  6
#define H_TAIL    7

//void create_monster()
void create_creature()
{
	set_name("grip");
	add_name("animal");
	add_adj("large");
	add_adj("snarling");
	set_race_name("dog");
	
	set_short("large snarling dog");
	
	set_long("This dog appears to be at least in part a wolf. It might be best not to provoke it or its master.\n");
	
	set_stats(({130, 150, 145, 5, 5, 160}));
	
	set_alignment(0);
	set_appearance(40);
	
	add_prop(CONT_I_WEIGHT, 40000);
	add_prop(CONT_I_HEIGHT, 250);
	
	set_skill(SS_UNARM_COMBAT, 100);
	set_skill(SS_AWARENESS, 75);
	set_skill(SS_BLIND_COMBAT, 100);

	//add_prop(LIVE_I_SEE_INVIS, 100);
	//add_prop(LIVE_I_QUICKNESS, 75);
	add_prop("_live_m_no_drain", "The dog quickly dodges out of your grasp!");
	add_prop(NPC_I_NO_RUN_AWAY, 1);
	add_prop(LIVE_I_NEVERKNOWN, 1);
	
	set_attack_unarmed(A_BITE, 50, 60, W_IMPALE, 60, "fangs");
	set_attack_unarmed(A_LFPAW, 40, 50, W_BLUDGEON, 20, "left front paw");
	set_attack_unarmed(A_RFPAW, 40, 50, W_BLUDGEON, 20, "right front paw");
	
	//Remove default hit locations and implement new ones
	for (int i = 0; i < 5; i++)
        remove_hitloc(i);
	
	/*set_hitloc_unarmed(H_BODY, 45, 20, "body");
	set_hitloc_unarmed(H_BACK, 45, 5, "back");
	set_hitloc_unarmed(H_HEAD, 40, 5, "head");
	set_hitloc_unarmed(H_LFLEG, 20, 8, "left front leg");
	set_hitloc_unarmed(H_RFLEG, 20, 8, "right front leg");
	set_hitloc_unarmed(H_LHLEG, 20, 7, "left hind leg");
	set_hitloc_unarmed(H_RHLEG, 20, 7, "right hind leg");
	set_hitloc_unarmed(H_TAIL, 10, 20, "tail");*/
	
	combat_reload();
	set_hitloc_unarmed(H_BODY, 30, 35, "body");
	set_hitloc_unarmed(H_HEAD, 20, 18, "head");
	set_hitloc_unarmed(H_LFLEG, 15, 12, "left front leg");
	set_hitloc_unarmed(H_RFLEG, 15, 12, "right front leg");
	set_hitloc_unarmed(H_LHLEG, 15, 10, "left hind leg");
	set_hitloc_unarmed(H_RHLEG, 15, 10, "right hind leg");
	set_hitloc_unarmed(H_TAIL, 5, 3, "tail");
	
	set_act_time(5);
	add_act("growl");
	add_act("emote barks loudly.");
	add_act("emote sniffs the air, the hair on its back bristling.");
	add_act("emote snarls savagely.");
}

int special_attack(object enemy)
{
	int dog_dex = query_stat(SS_DEX);
	int dog_str = query_stat(SS_STR);
	mixed *hitresult;
	string how;

  	if (random(5))
	{
		return 0;  
	}

	hitresult = enemy->hit_me(dog_str + dog_dex + random(50) , W_IMPALE, TO, -1);

	switch (hitresult[0])
	{
		case 0:
			how = "completely miss";
		break;
		case 1..10:
			how = "barely wound";
		break;
		case 11..30:
			how = "lightly wound";
		break;
		case 31..50:
			how = "moderately wound";
		break;
		case 51..60:
			how = "seriously wound";
		break;
		default:
			how = "savagely wound";
	}

	enemy->catch_tell(query_The_name(enemy) + " snaps at you!\n" + "Its fangs " + how + " you.\n");
	tell_watcher(QCTNAME(TO) + " snaps at " + QCTNAME(enemy) + "!\n" + "Its fangs " + how + " " + HIM_HER(enemy) + ".\n", enemy);

	return 1; 
}