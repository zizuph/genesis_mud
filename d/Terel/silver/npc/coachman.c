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

#define ADJ ({"bald", "old", "short", "fat"})

#define RACES ({"human", "half-elf", "halfling"})


void create_caravan_member()
{
  set_name("coachman");
  set_race_name(RACES[random(sizeof(RACES))]);
  set_adj(ADJ[random(sizeof(ADJ))]);
  set_short(query_adj(0) + " coachman");
  set_long("An old coachman sitting in front of the wagon. It looks like only "+
    "the sound of his whip cracking from time to time keeps him awake.\n");
    
  set_gender(0);
  set_alignment(0);
  
  default_config_npc(60 + random(20));


  set_skill(SS_UNARM_COMBAT, 60);
  set_skill(SS_PARRY, 60);
  set_skill(SS_DEFENCE, 75);
  set_skill(SS_AWARENESS, 50);
  set_skill(SS_BLIND_COMBAT, 70);

  /* for his whip */

  set_skill(SS_WEP_CLUB, 75);


  set_hp(query_max_hp());
  type = 2;
}

public void help_friend(object enemy, object victim)
{
  /* He only changes target for his own wagonmates, no point at attacking the same guy again. */
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
  if(!present(enemy, E(TO)))
  {
    command("smirk");
    return;
  }
  /* Just assisting */
  remove_prop(LIVE_S_EXTRA_SHORT);
  attack_object(enemy);
  enemy->catch_msg(CAP(query_short()) + " attacks you!\n");
  tell_room(E(TO), CAP(query_short()) + " attacks " + QTNAME(enemy) + "!\n", enemy);
}

