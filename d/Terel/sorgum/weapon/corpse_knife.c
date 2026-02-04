/*
 * Benton's preferred weapon
 */

inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>

#define TP this_player()
#define TO this_object()

void
create_weapon()
{
   set_name("tanto");
   add_name("_benton_knife_");
   set_short("tanto");
   set_long("This is a cold steel blade of superb craftsmanship.  " +
	    "The metal appears to have stripes where the steel has " +
	    "been folded during the forging process.  The hilt is " +
	    "crafted from fossilized bone and wrapped in shark skin.\n");

   set_adj("steel");
   
   set_default_weapon(44, 44, W_KNIFE, W_SLASH | W_IMPALE, W_ANYH, TO);
   add_prop(OBJ_I_WEIGHT, 10000); 
   add_prop(OBJ_I_VOLUME,  1000); 
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40, 44) + random(150));
   add_prop(OBJ_M_NO_BUY, 1);
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   
   add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
   add_prop(MAGIC_AM_ID_INFO,
	 "An evil knife that seems to take great skill to wield.\n");
   add_prop(OBJ_S_WIZINFO, 
      "The blade is intended for evil beings.  It has a chance to " +
      "do extra damage if the enemy has good alignment.  Requires " +
      "50 knife skill and evil alignment to wield.");
	
}

/*
 * In order to wield the weapon the player must have 50
 * knife skill and evil alignment.
 */
      
public int
wield(object wep)
{
    int a;
    if(TP->query_skill(SS_WEP_KNIFE) < 50)
    {
	write("You don't feel skilled enough to wield it.\n");
	return -1;
    }
   
    if(TP->query_alignment() >= -500)
    {
        write("You get shocked by the blade!  You must not be evil " +
	      "enough to wield it.\n");
	tell_room(environment(TP), 
		  "The tanto sends out an arc of electricity that shocks " +
		  QCTNAME(TP) + "!\n", TP);
	TP->reduce_hit_point(TP->query_alignment()/2);
	TP->do_die(TO);
	TP->command("drop tanto");
        return -1;
   }
   return 0;
}

/*
 * We want the weapon to be recoverable
 */

string
query_recover()
{
   return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
   init_wep_recover(arg);
}


int
try_hit(object ob) 
{
   return 1; 
}

varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit,
	int dam)
{
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

     if (enemy->query_alignment() < 0)
	  return 0;
     
    if (phurt == -1) {
        query_wielded()->catch_msg("The tanto just misses " +
				   QTNAME(enemy) + ".\n");
        enemy->catch_msg("The tanto comes dangerously close to you.\n");
    }
    else if (phurt == 0) {
        query_wielded()->catch_msg("The tanto cuts into the flesh of " +
                QTNAME(enemy) + ".\n");
        enemy->catch_msg("The tanto cuts into your flesh!\n");
    }
    else {
	   if (random(4) == 3) {
	      query_wielded()->catch_msg("Energy courses through the evil " +
	           "blade as it shreds " +QTNAME(enemy) + "!\n");
	     enemy->catch_msg("You feel excruciating pain as the evil blade " +
                   "shreds your flesh away from the bone.\n");

              enemy->heal_hp(-((random(100)) + 100));
	      enemy->do_die(environment(TO));

	 }
	   return 0;
      }
}
