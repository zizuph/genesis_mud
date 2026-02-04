/*
  guard for the caravan wagon
    by Udana, 03/06 Fixed Typos 05/06 Pasqua
*/

#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <money.h>
#include "../include/defs.h"



inherit NPC + "caravan_member.c";

#define RACES ({"human", "half-elf", "halfling"})
#define PLAYER_M_DISTRACTED_BY_GUARD "_player_m_distracted_by_guard"
#define PLAYER_M_STUNED_BY_GUARD "_player_m_stuned_by_guard"

/* merchant or coachman he's currently protecting */
object protecting = 0;

/* alarm for distracting enemies with sword */
int dAlarm;


void remove_g_distraction(object enemy);
void remove_g_stun(object enemy);

void create_caravan_member()
{
  set_name("guard");
	add_adj("caravan");
  set_race_name(RACES[random(sizeof(RACES))]);
  set_short("@@query_colour@@-uniformed caravan guard");
  set_long("Stern, armed @@query_race_name@@ standing before you is the guard of this caravan. Due to the repeated bandit attacks "+
    "on the road through silver forest, these bodyguards consist of the finest warriors of Calathin to defend the caravan.\n");
    
  set_gender(0);
  set_alignment(random(200));
  
  default_config_npc(100 + random(25));


  set_skill(SS_UNARM_COMBAT, 70);
  set_skill(SS_PARRY, 55 + random(20));
  set_skill(SS_DEFENCE, 80 + random(5));
  set_skill(SS_AWARENESS, 75);
  set_skill(SS_BLIND_COMBAT, 90 + random(50));
  set_skill(SS_WEP_SWORD, 80 + random(20));
  set_skill(SS_WEP_POLEARM, 80 + random(20));

  type = 0;
  set_hp(query_max_hp());
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
  /* Merchant or coachman is taking hits!*/
  if(victim->query_type() && enemy->query_attack() == victim)
    /* Merchants above coachmen */
    if(!protecting || protecting->query_type() < victim->query_type())
    {
      protecting = victim;
      victim->add_prop(OBJ_M_NO_ATTACK, "He's protected by caravan guards!\n");
      enemy->attack_object(TO);
      enemy->catch_msg("Guards rush forward, forcing you to attack them!\n");
      tell_room(E(TO), "Guards rush forward, forcing " + QTNAME(enemy) +
        " to attack them!\n", enemy);
      return;
    }
  /* Just assisting */
  attack_object(enemy);
  enemy->catch_msg(QCNAME(TO) + " attacks you!\n");
  tell_room(E(TO), QCNAME(TO) + " attacks " + QTNAME(enemy) + "!\n", enemy);
}

public void do_die(object killer)
{
  if(protecting)
    protecting->remove_prop(OBJ_M_NO_ATTACK);
  ::do_die(killer);
}

int special_attack(object enemy)
{
  
  /* special attack effects have identities so we know which one to remove */
  int distraction_id = 1;
  int stun_id = 1;

  /* add_sword, and add_partisan are set if certain damage is exceeded, to produce additional effects */
  int pen, attack_type, dt, add_effect;
  mixed *hitres;
  string attack_desc, damage_desc;

  /* normal attack */
  if(random(7) || !sizeof(query_weapon(-1)))
  return 0;
  
  if(query_weapon(-1)[0]->id("broadsword"))
    attack_type = 1;
  else
    attack_type = 0;
  
  if(!attack_type)
  {
    attack_desc = "performs a vicious stab with his partisan";
    dt = W_IMPALE;
    pen = 150;
    if(enemy->query_prop(PLAYER_M_DISTRACTED_BY_GUARD))
    {
      attack_desc = "takes an adventage of other guards manouver and performs a "+
	    "mighty slash with his partisan";
      dt = W_SLASH;
      pen += 200;
    }
    pen += random(400);
  }
  else
  {
    attack_desc = "performs a serie of quick blows with his sword"; 
    dt = W_SLASH;
    pen = 130 + random(300);
  }

  add_effect = 0;

  hitres = enemy->hit_me(pen, dt, TO, -1);
  damage_desc = "missing";
  if(hitres[0] >= 0)
    damage_desc = "slightly hurting";
  /* it's easier to distract then to stun*/
  if(hitres[0] >= 7 && attack_type)
	  add_effect = 1;
  /* it's enough to distract with the sword or stun with partisan.*/
  if(hitres[0] >= 15)
  {
	add_effect = 1;
    damage_desc = "hurting";
  }
  if(hitres[0] >= 20)
    damage_desc = "badly hurting";
  if(hitres[0] >= 40)
    damage_desc = "seriously injuring";
  if(hitres[0] > 60)
    damage_desc = "almost decapitating";
  
  /* Display what happened */
  enemy->catch_msg(QCTNAME(TO) + " " + attack_desc + ", " + damage_desc + " you.\n" );
  tell_watcher(QCTNAME(TO) + " " + attack_desc + ", " + damage_desc + " " + QTNAME(enemy) + ".\n", enemy);
  
  /* Additional effects, he distracts enemy with swords, so guys with partisans hit harder */
  if(attack_type && add_effect)
  {
    enemy->catch_msg("You're distracted by his quick moves.\n");
    distraction_id = enemy->query_prop(PLAYER_M_DISTRACTED_BY_GUARD) + 1;
    enemy->add_prop(PLAYER_M_DISTRACTED_BY_GUARD, distraction_id); 
    set_alarm(10.0 + 10.0 * rnd(), 0.0, &remove_g_distraction(enemy));
  }
  /* Partisan can stun someone. */
  if(!attack_type && add_effect)
  {
    enemy->catch_msg("You feel stunned!\n");
	if(enemy->query_prop(PLAYER_M_STUNED_BY_GUARD))
		enemy->add_stun();
    stun_id = enemy->query_prop(PLAYER_M_STUNED_BY_GUARD) + 1;
    enemy->add_prop(PLAYER_M_STUNED_BY_GUARD, stun_id); 
    set_alarm(10.0 + 5.0 * rnd(), 0.0, &remove_g_stun(enemy));
  }

  if(enemy->query_hp() <= 0)
    enemy->do_die(TO);
  return 1;
}

/* If distraction was most recent it is removed */
void remove_g_distraction(object enemy)
{
  enemy->add_prop(PLAYER_M_DISTRACTED_BY_GUARD, enemy->query_prop(PLAYER_M_DISTRACTED_BY_GUARD) - 1);
	if(enemy->query_prop(PLAYER_M_DISTRACTED_BY_GUARD) <= 0)
	{
		enemy->remove_prop(PLAYER_M_DISTRACTED_BY_GUARD);
		enemy->catch_msg("You feel you can focus on your environment again.\n");
	}
}

/* If that stun was most recent it's removed.*/
void remove_g_stun(object enemy)
{
	enemy->add_prop(PLAYER_M_STUNED_BY_GUARD, enemy->query_prop(PLAYER_M_STUNED_BY_GUARD) - 1);
	if(enemy->query_prop(PLAYER_M_STUNED_BY_GUARD) <= 0)
	{
		enemy->remove_prop(PLAYER_M_STUNED_BY_GUARD);
		enemy->remove_stun();
		enemy->catch_msg("You're no longer stunned.\n");
	}
}
