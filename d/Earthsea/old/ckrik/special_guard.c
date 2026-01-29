/*Code by Ckrik Nov, 97 for Earthsea

 *This is a guard with a simple damage special
 */


inherit "/d/Earthsea/std/monster";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <money.h>
#include <wa_types.h>

/* The combat special parameters.
 * SPA_DELAY = delay between specials
 * counter = the counter used in the special
 */

#define SPA_DELAY 8
static int counter = 4;



#define WEP "/d/Earthsea/ckrik/b_lngsword.c"
#define BARMOUR "/d/Earthsea/ckrik/b_platemail.c"
#define SHIELD "/d/Earthsea/ckrik/b_shield.c"
#define HELMET "/d/Earthsea/ckrik/b_helmet.c"
#define LEG "/d/Earthsea/ckrik/b_guards.c"



void
create_earthsea_monster()
{
  ::create_earthsea_monster();
  add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
  add_prop(LIVE_I_NEVERKNOWN, 0);
  set_name("guard");
  set_adj("strong");
  add_adj("guardian");
  set_race_name("human");
  set_gender(G_MALE);
  set_long("A castle guard. He is a well trained protector of the" +
	   " castle, always on alert. If there is any trouble in" +
	   " the castle he will be there to stop it. He seems to be" +
	   " well qualified for this job. Better not cause any" +
	   " trouble, and do not even think about doing something" +
	   " sneaky. His watchful eye will catch even the" +
	   " stealthiest of all rogues.\n");
 
  
  set_stats(({105 + random(10), 110 + random(10), 105 + random(10), 100, 100, 100}));

  set_hp(query_max_hp());
  set_all_hitloc_unarmed(50);
  
  set_skill(SS_DEFENSE, 85);
  set_skill(SS_PARRY, 70);
  set_skill(SS_WEP_SWORD, 90);
  set_skill(SS_UNARM_COMBAT, 65);
  set_skill(SS_AWARENESS, 80);
  set_skill(SS_BLIND_COMBAT, 50);
  
  set_act_time(50);
  add_act("emote adjusts his shiny bronze platemail.");
  add_act("say Do not cause any trouble!");
  add_act("emote keeps his eyes sharply on you.");

  set_cact_time(5);
  add_cact("emote prepares himself for combat.");
  add_cact("say Your corpse shall be an example for all to see.");
  add_cact("say Die worthless ruffian!");
  
  set_alignment((random(10) + 35));

}

int
arm_me()
{
    object wep, bodyarm, shield, helmet, guards;
    
    wep = clone_object(WEP);
    wep->move(this_object());
    bodyarm = clone_object(BARMOUR);
    bodyarm->move(this_object());
    shield = clone_object(SHIELD);
    shield->move(this_object());
    helmet = clone_object(HELMET);
    helmet->move(this_object());
    guards = clone_object(LEG);
    guards->move(this_object());
    this_object()->command("wield sword");
    this_object()->command("wear all");
    (MONEY_MAKE_GC((random(2) + 1)))->move(this_object());
    return 1;
}


/*****Special*****
 * This special is governed by a base damage of 100 + random 300
 * - the con of the victim.
 * If the dex of the victim is greater than a random 300 then the special
 * misses.
 */

int
special_attack(object enemy)
{
  string damage_lvl;
  mixed damage;
  int num = SPA_DELAY;
  
  if (++counter == SPA_DELAY)
    {
      counter = 0;

      if ((50 + random(300) < enemy->query_stat_dex))
	{
	  enemy->catch_msg("The strong guardian human looks silly" +
			   " as he completely misses you.\n");
	  tell_watcher("The strong guardian human looks silly" +
		       " as he misses an attempt to hit " + QCTNAME(enemy) 
		       + ".\n");
	}
      else
	{
	  damage = enemy->hit_me((100 + random(300) - 
				  enemy->query_stat_con()), 
				 W_BLUDGEON, this_object(), 0);
 
	  if (damage[0] <= 0) 
	    damage_lvl = "feel absolutely nothing.";
	  if (damage[0] > 0) 
	    damage_lvl = "feel a little bruised in the stomach.";
	  if (damage[0] > 15) 
	    damage_lvl = "feel like you are going to vommit.";
	  if (damage[0] > 25) 
	    damage_lvl = "feel quite hurt.";
	  if (damage[0] > 50) 
	    damage_lvl = "spew blood from you mouth.";
	  if (damage[0] > 75) 
	    damage_lvl = "are beat senseless.";

	  enemy->catch_msg("The strong guardian human strikes" +
		       " you hard in your stomach.\n");
	  enemy->catch_msg("You " + damage_lvl + "\n");

	  tell_watcher("The strong guardian human strikes "
		       + QCTNAME(enemy) + " in the stomach.\n");

	  if (damage[0] > 50) tell_watcher(QCTNAME(enemy) + " spews blood from " +
					   enemy->query_pronoun() +
					   " mouth.\n");
	  if (damage[0] > 75) tell_watcher(QCTNAME(enemy) +
					   " is beat senseless.\n");
      
	  if (enemy->query_hp() <= 0)
	    {
	      enemy->catch_msg("You spit your guts out and" + 
			       " collapse to the ground.\n");
	      tell_watcher("\n" + QCTNAME(enemy) + " spits " +
			   enemy->query_pronoun() +
			   " guts out and collapses to the ground.\n");
	      enemy->do_die(this_object());
	    }
	}
    return 1;
    }
    else
      {
	return 0;
      }
        
}



