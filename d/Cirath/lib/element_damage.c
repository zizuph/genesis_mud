/* Routine for dealing elemental (fire, acid, poison etc.) damage to a living.

   Code (c) October 2001 to Damian Horton, BKA Casimir.
*/

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Cirath/defs.h"

inherit CIRATH_DIR + "lib/pct_hurt";

/* Function name: element_damage
   Description  : Deals elemental damage to a living, taking into account
                  the livings resistances. 
   Arguments    : object victim  - The living object to which damage is to 
                                   to be dealt.
                  string element - The property which will reduce the damage.
		                   (E.g. MAGIC_I_RES_FIRE).
				    NB: NOT OBJ_I_RES_xxx, though that
				    property is taken into account.
		  int damage     - The penetration of the magical attack.
		                   (Expected damage is marginally more than
				   50% of this value) or, if the hitme flag
				   is false, then the actual damage to be done
				   (via heal_hp).
		  int hitme      - If true, the damage will be dealt via a
		                   a call to hit_me. If false, damage will be
				   dealt via heal_hp. Defaults to true.
				   NB: Set to false if the source of damage is
				   not a creature.
		  int strength   - Optional value which defaults to 100. Cannot
		                   exceed 100. This is the minimum resistance
				   required to take no damage from the attack.
				   E.g. if set to 50, than a resistance of 50
				   will result in no damage, and a resistance 
				   of 25 will result in taking 50% damage.
		  
   Returns      : The percentage of victims hit points (before the damage
                  was applied) dealt by this function. -1 if the victim
		  was not living, 100 if the victim took lethal damage.
                  
		  NB: You must call do_die() in the victim if the damage
		  is lethal.
*/

varargs int 
element_damage(object victim, string element, int damage, int hitme = 1,
	       int strength = 100)
{
    int resistance;
    mixed* result; //the result of the hit_me call
    int pct_damage; //how much damage was done

    if (! living(victim)) return -1;
    
    //mitigate the damage or penetration value by the victims resistance
    resistance = MAX(victim->query_magic_res(element), victim->query_magic_res(MAGIC_I_RES_MAGIC));
    damage -= damage * resistance / strength;

    //check to see if the damage was entirely mitigated (sanity check)
    if (damage < 1) return 0;

    if (hitme)
    {
	result = victim->hit_me(damage, MAGIC_DT, TO, -1);
	return MIN(result[0], 100);
    }

    pct_damage = pct_hurt(damage, victim);
    //deal the damage
    victim->heal_hp(- damage);
    
    return pct_damage;
}

















