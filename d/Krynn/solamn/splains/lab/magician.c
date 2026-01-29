/* The magician in the isolated laboratory.
 */

#include "local.h"
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>


inherit M_FILE


void
create_krynn_monster()
{
    set_name("asdfghjkl");
    set_race_name("human");
    set_adj("bald");
    add_adj("blue-eyed");
    set_long("");

    set_stats(({100,180,100,190,190,100}));
    set_skill(SS_DEFENCE,     50);
    set_skill(SS_PARRY,       50);
    set_skill(SS_WEP_SWORD,   30);  
    set_skill(SS_WEP_AXE,     30);

    set_alignment(-1200);
    set_knight_prestige(4500);
    set_aggressive(1);

    set_all_hitloc_unarmed(20);


    
}
int
special_attack(object victim)
{
    mixed *res;
    int hitp;
    string str, str1;
    if (E(victim) != E(TO) || victim->query_ghost())
      {
	  find_living("aridor")->catch_msg("KSTOP.\n");
	  TO->stop_fight(victim);
	  return 1;
      }
    if (!random(7))
      {
	  victim->catch_msg(query_The_name(victim) + " thrusts her " +
			    "draconian claymore towards you.\n");
	  
	  res = victim->hit_me(500, W_SLASH, TO, 1536);
	  hitp = res[0];
	  if (hitp = 0)
	    {
		str = "but you manage to avoid it";
		str1 = "fails to hit";
	    }
	  else if (hitp < 10)
	    {
		str = "and you try to sidestep, but you are tickled";
		str1 = "tickles";
	    }
	  else if (hitp < 20)
	    {
		str = "and you try to sidestep, but you are grazed ";
		str1 = "grazes";
	    }
	  else if (hitp < 40)
	    {
		str = "and you are hurt";
		str1 = "hurts";
	    }
	  else if (hitp < 60)	
	    {
		str = "and you are very badly hurt";
		str1 = "smashes";
	    }
	  else
	    {
		str = "and you are massacred";
		str1 = "massacres";
	    }
	  tell_object(victim,query_The_name(victim) + " suddenly twists the " +
		      "draconian claymore " + str + ".\n");
	  victim->add_attack_delay(hitp/3,1);
	  tell_watcher(QCTNAME(TO) + " " + str1 + " " + QCTNAME(victim) +
		      "with her draconian claymore.\n", victim);
	  if (!victim->query_ghost())
	    victim->do_die(this_object());
      }
    return 0;
}

