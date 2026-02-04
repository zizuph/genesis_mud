/*
  Coachman for the caravan wagon
    by Udana, 03/06
*/

#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <money.h>
#include "../include/defs.h"



inherit NPC + "caravan_member.c";

#define ADJ ({"bald", "handsome", "wealthy", "fat"})

#define RACES ({"human", "half-elf", "halfling"})


void create_caravan_member()
{
  set_name("merchant");
  set_race_name(RACES[random(sizeof(RACES))]);
  set_adj(ADJ[random(sizeof(ADJ))]);
  set_short(query_adj(0) + " merchant");
  set_long("A wealthy looking citizen of Calathin is probably an owner of this wagon.\n");
    
  set_gender(0);
  set_alignment(0);
  
  default_config_npc(80 + random(20));


  set_skill(SS_UNARM_COMBAT, 60);
  set_skill(SS_PARRY, 60);
  set_skill(SS_DEFENCE, 75);
  set_skill(SS_AWARENESS, 50);
  set_skill(SS_BLIND_COMBAT, 70);
  set_skill(SS_WEP_KNIFE, 75);
  type = 1;
  add_prop(OBJ_M_HAS_MONEY, 1000 + random(1000));

  set_hp(query_max_hp());
}

public void help_friend(object enemy, object victim)
{
  if(!present(enemy, E(TO)))
  {
    command("smirk");
    return;
  }
  if(query_attack())
    if(query_attack() == enemy || victim->query_colour() != colour ||
	    (query_attack()->query_attack() && query_attack()->query_attack()->query_colour() == colour))
   {
	if(member_array(enemy, query_enemy(-1)) == -1)
	{
		object tmp = query_attack();
		attack_object(enemy);
		attack_object(tmp);
	}
	return;
    }
	 /* Just assisting */
  attack_object(enemy);
  enemy->catch_msg(QCNAME(TO) + " attacks you!\n");
  tell_room(E(TO), QCNAME(TO) + " attacks " + QTNAME(enemy) + "!\n", enemy);
}

