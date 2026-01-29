/* Coded by Ckrik June 1998
 * Eventually there will be a quest associated with him
 */

inherit "/d/Earthsea/travellers/std/monster_base";
inherit "/d/Earthsea/lib/width_height";
inherit "/d/Earthsea/lib/remember";
inherit "/d/Earthsea/lib/intro";
inherit "/lib/unique";

#include "defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <money.h>
#include <wa_types.h>
#include <options.h>

/* The combat special parameters.
 * SPA_DELAY = delay between specials
 * counter = the counter used in the special
 */

#define SPA_DELAY 4
static int counter = 3;
#define SPECIAL_FORMULA (900 + random(650))

#define ALT_WEP "/d/Earthsea/gont/gont_city/wep/msword"
#define WEP THWIL+"wep/gigantic_sword"
#define BARMOUR THWIL+"arm/steel_plated"
#define HELMET THWIL+"arm/steel_helmet"
#define LEG THWIL+"arm/steel_guards"
#define ARM THWIL+"arm/steel_bracers"

void
create_traveller_monster()
{
  set_name("loran");
  set_living_name("_loran_");
  set_title("Infamous Mercenary, Lead Raider of the Band of the Hawks");
  set_adj("ruthless");
  add_adj("titanic");
  set_race_name("human");
  set_gender(G_MALE);
  set_long(break_string("He is definitely someone you do not " +
	   "want to mess with unless you are very sure of yourself. " +
	   "He towers over everyone around here. \n", 70));
  set_height("very tall");
  set_width("normal width");  
  set_stats(({300, 325, 300, 160, 150, 300}));
  set_skill(SS_DEFENSE, 120);
  set_skill(SS_PARRY, 120);
  set_skill(SS_WEP_SWORD, 120);
  set_skill(SS_AWARENESS, 75);
  set_skill(SS_BLIND_COMBAT, 100);
  
  set_guild_stat(SS_RACE, 16000000);
  set_act_time(50);
  add_act("emote shifts his eyes around.");
  add_act("emote looks at you with his piercing eyes.");
  add_act("flex");
  add_act("caress sword");
  set_cact_time(45);
  add_cact("say Your corpse will decorate my belt.");
  add_cact("say Die!");
  set_exp_factor(200);
  set_alignment(-10);
  setuid();
  seteuid(getuid());
  add_equipment(({BARMOUR, HELMET, LEG, ARM}));
  //clone_object(WEP)->move(this_object());
  clone_unique(WEP, 4, ALT_WEP, 75)->move(this_object());
  command("wield all");
  set_random_move(90);
  set_restrain_path(({THWIL+"h", THWIL+"t", THWIL+"a",
		      ROKE_BEACH, 
			"/d/Earthsea/gont/beach/beach_rooms/"}));
  add_ask(({"quest", "task", "help"}), "say Hmpf...You're of no " +
	  "use to me right now, but I may have something in mind later.\n", 1);
  //add_prop("_ranger_i_not_disarm", 1);
  log_my_kills("/d/Earthsea/log/npc_logs/mercenary_kills", 1);
  log_my_deaths("/d/Earthsea/log/npc_logs/mercenary_deaths", 1);
}

int
special_attack(object enemy)
{
  string damage_lvl;
  mixed damage;
  int num = SPA_DELAY;
  
  if (++counter >= SPA_DELAY + random(1) && sizeof(this_object()->query_weapon(-1)) > 0)
  {
      counter = 0;
      
      damage = enemy->hit_me(SPECIAL_FORMULA, 
			     W_SLASH, this_object(), -1);
 
      if (damage[0] > 0) 
	damage_lvl = "slightly cuts";
      if (damage[0] > 15) 
	damage_lvl = "cuts a small wound on";
      if (damage[0] > 25) 
	damage_lvl = "slices a deep wound on";
      if (damage[0] > 50) 
	damage_lvl = "inflicts great damage on";
      if (damage[0] > 75) 
	damage_lvl = "hacks off a chunk of flesh of";
      if (damage[0] > 0)
	{
	  switch(random(2))
	    {
	    case 0:
	      enemy->catch_msg(QCTNAME(this_object()) + " swings his " +
	         this_object()->query_weapon(-1)[0]->query_short() +
			       " around and " + damage_lvl +
			       " you.\n");
	      
	      tell_watcher(QCTNAME(this_object()) + " swings his " +
		 this_object()->query_weapon(-1)[0]->query_short() +
			   " around and " + damage_lvl +
			   " " + QTNAME(enemy) + ".\n", enemy);
	      
	      break;
	    default:
	      enemy->catch_msg(QCTNAME(this_object()) + " suddenly " +
		    "whips up his " + 
		    this_object()->query_weapon(-1)[0]->query_short() +
		    " and " + damage_lvl + " you.\n");
	      tell_watcher(QCTNAME(this_object()) + " suddenly " +
			   "whips up his " + 
			   this_object()->query_weapon(-1)[0]->query_short() +
			   " and " + damage_lvl + " " +
			   QTNAME(enemy) + ".\n", enemy);
	      break;
	    }
	}
      else
	{
	  if (!enemy->query_option(OPT_GAG_MISSES))
	    {
	      enemy->catch_msg(QCTNAME(this_object()) + " swings his " +
			  this_object()->query_weapon(-1)[0]->query_short() +
			  " and narrowly misses you.\n");
	    }
	  tell_watcher_miss(QCTNAME(this_object()) + " swings his " +
			    this_object()->query_weapon(-1)[0]->query_short() +
			    " and narrowly misses " + QTNAME(enemy) + ".\n",
			    enemy);
	  this_object()->command("$fume");
	  this_object()->command("$say Lucky dodge, you won't " +
				 "be so lucky next time.");
	}
      if (enemy->query_hp() <= 0)
	{
	  enemy->catch_msg("You yell in agony as " +
			   QTNAME(this_object()) + " slices " +
			   "open your body gutting your internals.\n");
	  tell_watcher(QCTNAME(enemy) + " yells in agony" +
		       " as " + QTNAME(this_object()) + " slices " +
		       "open " + enemy->query_possessive() + " body " +
                       "gutting " + enemy->query_possessive() +
                       " internals.\n", 
		       enemy);
	  enemy->do_die(this_object());
	}
      return 1;
    }
  return 0;
}
