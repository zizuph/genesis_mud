/*
 * By Antharanos
 * Modified by Korat.. a bit
 *
 * Cotillion - 2006-04-20
 * - Fixed so ::did_hit is called
 */

#pragma strict_types

inherit "/d/Kalad/std/weapon";
#include <poison_types.h>
#include <formulas.h>
#include "/d/Kalad/defs.h"

int poison_used;

void create_weapon()
{
    ::create_weapon();
    set_name("dagger");
    set_adj("curved");
    set_long("@@long_desc");
    set_hit(14);
    set_pen(14);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
    poison_used = 0;
}
string
  long_desc()
{
    if(poison_used)
	return "This dagger is slightly curved and very sharp.\n";
    else
	return "This dagger is slightly curved and very sharp. There is a thin "+
	    "coating of a black liquid on the blade.\n";
}
public varargs int did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
    object poison;

    ::did_hit(aid, hdesc, phurt, enemy, dt, phit);
   
    if(!poison_used && !random(3))
    {
        setuid();
        seteuid(getuid());
	poison = clone_object("/std/poison_effect");
	if(poison) {
	    if(random(2))
		poison_used = 1;
	    poison->move(enemy, 1);
	    poison->set_time(1500);
	    poison->set_interval(150);
	    poison->set_strength(600);
	    poison->set_damage(({POISON_FATIGUE, 300, POISON_STAT, SS_CON}));
	    enemy->catch_msg("As the daggers blade neatly cuts you, a burning "+
			     "feeling runs from the small wound.\n");
	    TO->query_wielded()->catch_msg("You manage to cut your enemy "+
					   "with the poisoned edge of the daggers blade!\n");
	    poison->start_poison();
	    return 0;
	}
	else
	    write("Failed to load poison for some reason.\n");
    }
    return 0;
}
