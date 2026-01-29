 /*****************************************************************************
*  /d/Kalad/common/isles/npc/largecrab.c
*
*  NPC: Large Crab
*
*  Created November 2020, Greneth
*
 *****************************************************************************/

 /*****************************************************************************
*  Defines
 *****************************************************************************/
#define H_HEAD 0
#define H_BODY 1
#define H_LARM 2
#define H_RARM 3
#define H_LEGS 4

 /*****************************************************************************
*  Includes
 *****************************************************************************/
#include "../local.h"

 /*****************************************************************************
*  Inherits
 *****************************************************************************/
inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";

 /*****************************************************************************
*  Function name: create_monster
*  Description  : Constructor for the monster
 *****************************************************************************/
create_monster()
{
   set_name("crab");
   set_adj("large");
   set_race_name("crab");
   set_long("This is a oversized crab that is about as big as a cat. It has "
   + "a blue-hued shell and sharp spiny legs. Its beady eyes shift randomly "
   + "looking in different directions.\n");
   set_stats(({50,60,50,40,40,60}));
   set_gender(G_NEUTER);
   set_skill(SS_PARRY, 30 + random(10));
   set_skill(SS_DEFENCE, 30 + random(10));
   set_skill(SS_UNARM_COMBAT, 30 + random(10));
   set_skill(SS_BLIND_COMBAT, 50 + random(10));
   set_skill(SS_SPELLCRAFT, 45);
   set_attack_unarmed(A_MOUTH, 30, 30, W_IMPALE, 10, "sharp jaws");
   set_attack_unarmed(A_L_HAND, 25, 25, W_SLASH, 45, "small left pincer");
   set_attack_unarmed(A_R_HAND, 25, 25, W_SLASH, 45, "small right pincer");
   set_attack_unarmed(A_LEGS, 25, 25, W_IMPALE, 45, "spiny legs");
   set_hitloc_unarmed(H_HEAD, ({ 20, 20, 20 }), 15, "beady eyes");
   set_hitloc_unarmed(H_BODY, ({ 30, 30, 30 }), 45, "hard shelled body");
   set_hitloc_unarmed(H_LARM, ({ 25, 25, 25 }), 10, "small left pincer");
   set_hitloc_unarmed(H_RARM, ({ 25, 25, 25 }), 10, "small right pincer");
   set_hitloc_unarmed(H_LEGS, ({ 25, 25, 25 }), 20, "spiny legs");
   add_prop(LIVE_I_NEVERKNOWN, 1);
   set_act_time(3);
   add_act("emote shuffles back and forth across the sand.");
   add_act("emote clamps one pincer shut.");
   set_cact_time(3);
   add_cact("emote turns its eyes towards you.");
   set_random_move(10);
   add_leftover(OBJ + "crableg.c","leg", random (10),"",0,1);
	add_leftover(OBJ + "crabmeat.c","meat", random (2),"",0,1);
   add_prop(NPC_I_NO_RUN_AWAY,1);
	remove_leftover("tooth", 1);
	remove_leftover("skull", 1);
	remove_leftover("rib", 1);
	remove_leftover("nail", 1);
	remove_leftover("heart", 1);
	remove_leftover("thighbone", 1);
	remove_leftover("kidney", 1);
	remove_leftover("intestine", 1);
	remove_leftover("meat", 1);
   remove_leftover("ear", 1);
	remove_leftover("scalp", 1);
	remove_leftover("toe", 1);
	remove_leftover("nose", 1);
	remove_leftover("kneecap", 1);
	remove_leftover("jaw", 1);
	remove_leftover("finger", 1);
}

 /*****************************************************************************
*  Function name: special_attack
*  Description  : Special water attack that drains fatigue and health
 *****************************************************************************/
int
special_attack(object enemy)
{
   mixed *hitresult;
   string result;

      if(random(3))
      {
         return 0;
      }
		  
      int penet = 550 + random(300);
      penet -= penet * enemy->query_magic_res(MAGIC_I_RES_WATER) / 100;
      hitresult = enemy->hit_me(penet, MAGIC_DT, TO, -1);
		  
   switch (hitresult[0])
   {
      case 0:
			result = "misses";
			break;
      case 1..10:
         result = "it barely hits you";
		   enemy -> add_fatigue(-5);
				if(enemy->query_fatigue() <= 0)
            {
               enemy->add_hp(-10);
            }
         break;
      case 11..20:
         result = "they hit you front and center, you feel drained";
		   enemy -> add_fatigue(-10);
				if(enemy->query_fatigue() <= 0)
            {
               enemy->add_hp(-20);
            }
         break;
      default:
         result = "you are completely blasted by them making you "
			+ "feel extremely tired";
		   enemy -> add_fatigue(-15);
				if(enemy->query_fatigue() <= 0)
            {
               enemy->add_hp(-30);
            }
         break;
   }

   enemy->catch_tell(query_The_name(enemy) + " spews forth a stream of "
	+ "bubbles at you and " + result + ".\n");
	
   tell_watcher(QCTNAME(TO) + " spews forth a stream of bubbles at "
	+ QTNAME(enemy) + ".\n", enemy);

   if (enemy->query_hp() <= 0)
   {
      enemy->do_die(this_object());
   }

   return 1;
}