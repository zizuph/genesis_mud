/*
* Created by: Luther
* Date: Sept 2001 
*
* File: /d/Cirath/ridge/npc/v_skull.c
* Comments: The Big skeleton in th ruins of the valley
*/

#pragma strict_types
#pragma save_binary 
 
inherit "/d/Cirath/std/monster.c";
inherit "/d/Emerald/lib/equip";

#include "defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <options.h>

void
create_monster ()
{
	set_living_name("skull");	
	set_name("skull");
	add_name("guard");
	set_title("Nighmarish skeleton of the undead");
	set_race_name("skeleton");
	set_adj("decayed");
	add_adj("bone");

	set_long("This is a old skeleton patrolling this building. He looks extremely "
		+"nimble and watches you closely.\n");
	set_gender(2); 
	set_stats(({ 180, 320, 190, 40, 40, 150}));
	set_all_hitloc_unarmed(({200, 100, 50}));  
	set_skill(SS_DEFENCE, 90);
	set_skill(SS_UNARM_COMBAT, 90);
	set_skill(SS_BLIND_COMBAT, 100);
	set_skill(SS_PARRY, 90);
	set_skill(SS_WEP_POLEARM, 90);
	set_skill(SS_AWARENESS, 90);
	add_prop(LIVE_I_UNDEAD, 1);
	add_prop(LIVE_I_SEE_DARK,100);
	add_prop(NPC_I_NO_RUN_AWAY, 1);
	add_prop(LIVE_I_NEVERKNOWN, 1);
	add_prop(MAGIC_I_RES_FIRE, 80);
    	add_prop(MAGIC_I_RES_ACID, 80);
    	add_prop(MAGIC_I_RES_COLD, 80);
    	add_prop(MAGIC_I_RES_ELECTRICITY, 80);
    	add_prop(LIVE_I_QUICKNESS, 50); 
	set_alignment(-1000);
	add_prop(LIVE_I_NO_CORPSE, 1);
	set_act_time(5);
	set_cact_time(3);

	add_act("emote makes another patrol of the room.");
	add_act("emote stares at you wondering if it should attack.");
	add_act("emote peers at the back of the room.");
	add_act("emote looks around the building.");
		
	add_cact("emote growls at you.");
}

/* He currently has good unarmed so let him use it */
/* sets unarmed combat off, giving more attacks! */

int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}	


void
arm_me()
{
	//   if ( (special_shield == 0) || (sizeof(object_clones(special_shield)) == 0) )
	object special_shield;
	special_shield = find_object(RIDGE_ARM + "skull_shd");

	if(!random(4))
	{
		if ((!special_shield) ||(sizeof(object_clones(special_shield)) <= 3)) 
			add_equipment(RIDGE_ARM + "skull_shd");
		else
			add_equipment(RIDGE_ARM + "skull_shda");			
	}
	else
	{
		add_equipment(RIDGE_ARM + "skull_shda");
	}		
	add_equipment(RIDGE_WEP + "spear1");
	
}

