/* Coded by Ckrik June 1998
 */


inherit "/d/Earthsea/std/monster.c";
inherit "/d/Earthsea/lib/width_height.c";
inherit "/d/Earthsea/lib/remember.c";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <money.h>
#include <wa_types.h>

/* The combat special parameters.
 * SPA_DELAY = delay between specials
 * counter = the counter used in the special
 */

#define SPA_DELAY 5
static int counter = 3;
#define SPECIAL_FORMULA 500 + random(600)


#define WEP "/d/Earthsea/ckrik/marisol/gigantic_sword.c"
#define BARMOUR "/d/Earthsea/ckrik/marisol/steel_plated.c"
#define HELMET "/d/Earthsea/ckrik/marisol/steel_helmet.c"
#define LEG "/d/Earthsea/ckrik/marisol/steel_guards.c"
#define ARM "/d/Earthsea/ckrik/marisol/steel_bracers.c"



void
create_earthsea_monster()
{
  ::create_earthsea_monster();
  set_name("loran");
  set_living_name("loran");
  set_title("Nari, Infamous Mercenary of Osskil");
  set_adj("ruthless");
  add_adj("titanic");
  set_race_name("human");
  set_gender(G_MALE);
  set_long("A ruthless titanic male human. " +
	   "He is definitely someone you do not " +
	   "want to mess with unless you are very sure of yourself. " +
	   "He towers over everyone around here.\n");
  set_height("very tall");
  set_width("normal width");

  
  set_stats(({160, 160, 175, 60, 55, 160}));

  set_hp(query_max_hp());
  
  set_skill(SS_DEFENSE, 100);
  set_skill(SS_PARRY, 90);
  set_skill(SS_WEP_SWORD, 95);
  set_skill(SS_AWARENESS, 35);
  set_skill(SS_BLIND_COMBAT, 80);
  
  set_act_time(50);
  add_act("emote laughs demonically.");
  add_act("say No one can stop me.");
  add_act("emote looks at you with his one good eye.");

  set_cact_time(45);
  add_cact("emote prepares himself for combat.");
  add_cact("say Your corpse shall decorate my belt.");
  add_cact("say Die weakling!");
  
  set_alignment(-100);
}

int
arm_me()
{
  object wep, bodyarm, helmet, guards, bracers;
  
  wep = clone_object(WEP);
  wep->move(this_object());
  bodyarm = clone_object(BARMOUR);
  bodyarm->move(this_object());
  helmet = clone_object(HELMET);
  helmet->move(this_object());
  guards = clone_object(LEG);
  guards->move(this_object());
  bracers = clone_object(ARM);
  bracers->move(this_object());
  this_object()->command("wield all");
  this_object()->command("wear all");
  (MONEY_MAKE_GC((random(2) + 2)))->move(this_object());
  return 1;
}

int
special_attack(object enemy)
{
  string damage_lvl;
  mixed damage;
  int num = SPA_DELAY;
  
  if (++counter >= SPA_DELAY + random(2) && this_object()->query_weapon(-1))
    {
      counter = 0;
      
      damage = enemy->hit_me(SPECIAL_FORMULA, 
			     W_SLASH, this_object(), -1);
 
      if (damage[0] <= 0) 
	  damage_lvl = "completely misses";
      if (damage[0] > 0) 
	damage_lvl = "slightly cuts";
      if (damage[0] > 15) 
	damage_lvl = "cuts a small wound on";
      if (damage[0] > 25) 
	damage_lvl = "slices a deep wound on";
      if (damage[0] > 50) 
	damage_lvl = "inflicts great damage on";
      if (damage[0] > 75) 
	damage_lvl = "hacks off a chunk of";
      
      enemy->catch_msg(QCTNAME(this_object()) + " swings his " +
		       "sword around and " + damage_lvl +
		       " your " + damage[1] + ".\n");
      
      tell_watcher(QCTNAME(this_object()) + " swings his " +
		   "sword around and " + damage_lvl +
		   " " + QTNAME(enemy) + "'s " + 
		   damage[1] + ".\n", enemy);
      if (damage[0] <= 0)
	{
	  this_object()->command("fume");
	  this_object()->command("say Lucky dodge, you won't " +
				 "be so lucky next time.");
	}
      if (enemy->query_hp() <= 0)
	{
	  enemy->catch_msg("You yell in agony as " +
			   QTNAME(this_object()) + " slices " +
			   "open your guts.\n");
	  tell_watcher(QCTNAME(enemy) + " yells in agony" +
		       " as " + QTNAME(this_object()) + " slices " +
		       "open " + enemy->query_pronoun() + " guts.\n", 
		       enemy);
	  enemy->do_die(this_object());
	}
      return 1;
    }
  return 0;
}
