/*
 * A magic weapon which can spawn as a 2H sword, polearm, club or axe.
 * If the wielder misses his target, there's a 20% chance that the wielder
 * will hit himself or a follower instead.
 */
inherit "/std/weapon";
inherit "/lib/keep";

#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>

string *weaponType = ({"glaive", "claymore", "battleaxe", "warhammer"});

string *weaponDesc = ({ "This is a very good newbie glaive.\n",
                        "This is a very good newbie claymore.\n",
                        "This is a very good newbie battleaxe.\n",
                        "This is a very good newbie warhammer.\n"});

#ifndef ONE_OF
#define ONE_OF(x)   (x[random(sizeof(x))])
#endif

int HIT = 49;
int PEN = 54 + random(6);
						
int type = random(sizeof(weaponType)); 
						
create_weapon()
{
    set_name(weaponType[type]);
    set_adj("metalic");
    add_adj("rune-covered");
    set_short("metalic rune-covered "+ weaponType[type]);
    set_long(weaponDesc[type]);

    switch (weaponType[type])
	{
		case "glaive":
		  set_default_weapon(HIT,PEN, W_POLEARM, W_SLASH | W_IMPALE, W_BOTH);
		  break;
		case "claymore":
		  set_default_weapon(HIT,PEN, W_SWORD, W_SLASH, W_BOTH);
		  break;
		case "battleaxe":
		  set_default_weapon(HIT,PEN, W_AXE, W_SLASH | W_IMPALE, W_BOTH);
		  break;
		case "warhammer":
	  	  set_default_weapon(HIT,PEN, W_CLUB, W_BLUDGEON, W_BOTH);
		  break;
		default:
		  set_default_weapon(HIT,PEN, W_SWORD, W_SLASH, W_BOTH);
		  break;
	}

   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
   add_prop(MAGIC_AM_ID_INFO, ({"These polearms were created "+
      "by the High Priests of Istar before the Cataclysm.  "+
      "Forged from a long forgotten mixture of metals that give it "+
      "its durability and light weight, it was then enchanted to "+
      "leave ghastly wounds that could not be healed through normal means. "+
      "Many of the High Priests enemies slowly bled to death "+
      "attempting to flee from the cruel oppressors.\n",10,
      "This one seems to be defiled by becoming blessed by the evil "+
      "god Sargonnas, which gives it some extra speed.\n", 35}));

   add_item(({"runes", "silvery"}),
        "These runes may be of elven origin but neither "+
        "the writing nor the way that this weapon has been "+
        "forged indicate who could have done this. You start "+
        "to stare intensely on the runes, but are unable "+
        "to decipher what they mean.\n");

   add_prop(OBJ_I_VOLUME, 3000);
   add_prop(OBJ_I_WEIGHT, 4470);
   set_likely_dull(1);
   set_likely_corr(1);
   set_likely_break(1);
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
        int phit, int dam)
{ 
    if (phurt <= 0) //We miss the enemy - check if we accidentally hit ourself or team member
    {
	    if (!random(5))
		{	
			string *hitLocation = ({ "head", "left arm", "right arm", "body", "left leg", "right leg"});
			hdesc =  ONE_OF(hitLocation);
			object *team = wielder->query_team();
			object target = wielder; //We'll hit the wielder as default.
		
			// Check of the wielder is in a team, select a random team member.
			if (sizeof(team) > 0) 
			{
				target = team[random(sizeof(team))]; 
				if (target->query_linkdead())  // The group member is linkdead, reset the target to wielder
					target = wielder;
			}
			if (target == wielder)
			{
				wielder->catch_msg("You swing at " + QTNAME(enemy) + " but he manage to avoid it.\n"+
				  "The momentum causes you to loose control of your " + short() +" and accidentally "+
				  "hit your own " + hdesc + " with your weapon!\n");
				  				  
				wielder->tell_watcher(QCTNAME(wielder) + " swings at " + QTNAME(enemy) + " but he manage "+
				  "to avoid it.\n"+
				  "The momentum causes him to loose control of his " + short() + " and accidentally "+
				  "hit his own "+ hdesc + " with his weapon.\n", target);
			}
			else
			{
				wielder->catch_msg("You swing at " + QTNAME(enemy) + " but he manage to avoid it.\n"+
				  "The momentum causes you to loose control of your " + short() +" and accidentally "+
				  "hit " +QTNAME(target)+ "'s " + hdesc + " with your weapon!\n");			

				target->catch_msg(QTNAME(wielder)+ " swings at " + QTNAME(enemy) + " but he manage to avoid it.\n"+
				  "The momentum causes him to loose control of his " + short() +" and accidentally "+
				  "hit your " + hdesc + " with his weapon!\n");
				  
				wielder->tell_watcher(QCTNAME(wielder) + " swings at " + QTNAME(enemy) + " but he manage to avoid it.\n"+
				  "The momentum causes him to loose control of his " + short() +" and accidentally "+
				  "hit " +QCTNAME(enemy)+ "'s "+ hdesc + " with his weapon.\n", target);
			}
			if (weaponType[type] == "warhammer")
				target->hit_me(wielder->query_stat(SS_STR), W_BLUDGEON, TO, hdesc);
			else
				target->hit_me(wielder->query_stat(SS_DEX), W_SLASH, TO, hdesc);
			
			// The wielder kills himself or team member
			if (target->query_hp() <= 0)
				target->do_die(TO);
			
			return 1;
		}
    }
   return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}
