/*
 * Cotillion - 20181104
 * - Fixed poison cloning
 */

#include "../default.h"
inherit (STD + "weapon");

#include <poison_types.h>
#include <ss_types.h>
#include <wa_types.h>

int poison_used;

void
create_weapon()
{
    ::create_weapon();

    set_name("dagger");
    set_adj("wicked");
    set_long("@@long_desc@@");
    set_hit(16);
    set_pen(14);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
    poison_used = 0;

    setuid();
    seteuid(getuid());
}

string
long_desc()
{
    if (poison_used)
	return "A large dagger with a viciously curved blade.\n";
    else
	return "A large dagger with a viciously curved blade. There is a thin "+
	    "coating of liquid on the blade.\n";
}

public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
    object poison;
    
    ::did_hit(aid, hdesc, phurt, enemy, dt, phit);

    if(!poison_used && !random(3))
    {
	poison = clone_object("/std/poison_effect");
	if(poison) {
	    if(random(2))
		poison_used = 1;
	    poison->move(enemy, 1);
	    poison->set_time(1500);
	    poison->set_interval(150);
	    poison->set_strength(600);
	    poison->set_damage(({POISON_FATIGUE, 300, POISON_STAT, SS_CON}));
	    poison->start_poison();
	    return 0;
	}
	else
	    write("Failed to load poison for some reason.\n");
    }
    return 0;
}
