/*Code by Ckrik Nov, 97 for Earthsea
 *This is Klont.
 *He's a huge karg with a hard hitting special.
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

#define SPA_DELAY 6
static int counter = 5;



#define WEP "/d/Earthsea/ckrik/bl_battleaxe.c"
#define BARMOUR "/d/Earthsea/ckrik/bl_platemail.c"
#define HELMET "/d/Earthsea/ckrik/bl_mask.c"
#define LEG "/d/Earthsea/ckrik/bl_greaves.c"



void
create_earthsea_monster()
{
  ::create_earthsea_monster();
  add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
  set_name("klont");
  add_name("karg");
  set_living_name("klont");
  set_title("the Supreme Commander, " +
	    "Legendary Warrior of the Kargad Empire");
  set_adj("ruthless");
  add_adj("titanic");
  set_short("ruthless titanic karg");
  set_race_name("human");
  set_gender(G_MALE);
  set_long("This karg is huge. He is bigger, stronger, and " +
	   "nastier than any karg you have ever seen. He " +
	   "towers over everything in sight. His single " +
	   "good eye instills fear in you as you look at it. " +
	   "The emblem on his body armour indicates that " +
	   "his is the commander of this karg army. " +
	   "This karg is definitely someone you do not " +
	   "want to mess with.\n");
 
  
  set_stats(({190, 190, 190, 110, 110, 160}));

  set_hp(query_max_hp());
  set_all_hitloc_unarmed(50);
  
  set_skill(SS_DEFENSE, 100);
  set_skill(SS_PARRY, 90);
  set_skill(SS_WEP_POLEARM, 90);
  set_skill(SS_WEP_AXE, 100);
  set_skill(SS_UNARM_COMBAT, 80);
  set_skill(SS_AWARENESS, 35);
  set_skill(SS_BLIND_COMBAT, 50);
  
  set_act_time(50);
  add_act("emote laughs demonically.");
  add_act("say No one can stop me.");
  add_act("emote looks at you with his one good eye.");

  set_cact_time(5);
  add_cact("emote prepares himself for combat.");
  add_cact("say Your corpse shall decorate my belt.");
  add_cact("say Die weakling!");
  
  set_alignment(-100);
  trig_new("%s 'introduces' %s", "react_intro");

}

void
react_intro()
{ 
  call_out("intro", 4);
}

void
intro()
{
  command("introduce me");
}

int
arm_me()
{
    object wep, bodyarm, helmet, guards;
    
    wep = clone_object(WEP);
    wep->move(this_object());
    bodyarm = clone_object(BARMOUR);
    bodyarm->move(this_object());
    helmet = clone_object(HELMET);
    helmet->move(this_object());
    guards = clone_object(LEG);
    guards->move(this_object());
    this_object()->command("wield all");
    this_object()->command("wear all");
    (MONEY_MAKE_PC((random(2) + 1)))->move(this_object());
    return 1;
}


/*****Special*****
 * This special is governed by a base damage of 100 + random 400
 * - the con of the victim.
 * If the dex of the victim is greater than 100 + random 700 then 
 * the special misses.
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

      if ((100 + random(1000) < enemy->query_stat(1)))
	{
	  enemy->catch_msg(QCTNAME(this_object()) + " looks silly" +
			   " as he completely misses you.\n");
	  tell_watcher(QCTNAME(this_object()) + " looks silly" +
		       " as he misses an attempt to ram " + QCTNAME(enemy) 
		       + ".\n", enemy);
	}
      else
	{
	  damage = enemy->hit_me((200 + random(700) - 
				  enemy->query_stat(2)), 
				 W_BLUDGEON, this_object(), 0);
 
	  if (damage[0] <= 0) 
	    damage_lvl = "feel absolutely nothing.";
	  if (damage[0] > 0) 
	    damage_lvl = "feel a little shakened.";
	  if (damage[0] > 15) 
	    damage_lvl = "feel somewhat rattled.";
	  if (damage[0] > 25) 
	    damage_lvl = "feel quite hurt.";
	  if (damage[0] > 50) 
	    damage_lvl = "feel seriously injured.";
	  if (damage[0] > 85) 
	    damage_lvl = "are on the verge of death.";

	  enemy->catch_msg(QCTNAME(this_object()) + " rams you hard.\n");
	  enemy->catch_msg("You " + damage_lvl + "\n");

	  tell_watcher(QCTNAME(this_object()) + " rams "
		       + QCTNAME(enemy) + " hard.\n", enemy);

	  if (enemy->query_hp() <= 0)
	    {
	      enemy->catch_msg("You are flattened and" + 
			       " collapse to the ground.\n");
	      tell_watcher("\n" + QCTNAME(enemy) + " yells in agony" +
                           " as " + enemy->query_pronoun() + " is" +
                           " smashed and collapses to the ground.\n", 
			   enemy);
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



