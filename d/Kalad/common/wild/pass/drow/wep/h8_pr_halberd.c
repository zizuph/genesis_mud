inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
int poison_used;

/* by Antharanos */

/* Jun 5 2002 - Found a mortal carrying one of these, took a look for old
                time's sake... poison incrementing was commented out.
   -Rhyn
 */

create_weapon()
{
    ::create_weapon();
    set_name("halberd");
    set_adj("bone-white");
    add_adj("adamantine");
    set_pname("halberds");
    set_short("bone-white adamantine halberd");
    set_pshort("bone-white adamantine halberds");
    set_long("@@long_desc");
    set_hit(26);
    set_pen(37);
    set_hands(W_BOTH);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_VALUE, 750);
    add_prop(OBJ_I_WEIGHT,9000);
    add_prop(OBJ_I_VOLUME,9000);
    poison_used = 0;
}
string
long_desc()
{
    if(poison_used)
	return "An exquisite adamantine halberd, its strange color reminds you "+
	"vaguely of the long-since fleshless bones of a dead slave.\n";
    else
	return "An exquisite adamantine halberd, its strange color reminds you "+
	"vaguely of the long-since fleshless bones of a dead slave. Upon its "+
	"blade is a thin sheen of liquid.\n";
}
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
    object poison;
    if(!poison_used && !random(6))
    {
	poison = clone_object("/std/poison_effect");
	if(poison)
	{
	    if(random(3))
            poison_used = 1;
		poison -> move(enemy);
	    poison -> set_time(100);
	    poison -> set_interval(25);
	    poison -> set_strength(100);
	    poison -> set_damage(({POISON_HP, 200, POISON_STAT, SS_CON}));
	    poison -> start_poison();
	    return 0;
	}
	else
	    write("Failed to load poison for some reason.\n");
    }
    return 0;
}
