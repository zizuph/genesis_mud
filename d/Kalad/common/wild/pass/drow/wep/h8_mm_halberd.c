inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
int poison_used;

/* by Antharanos */

/* June 5, 2002 - Like h8_pr_halberd.c, but this was removed instead of
                  commented out.
 */

create_weapon()
{
    ::create_weapon();
    set_name("halberd");
    set_adj("abyss-black");
    add_adj("adamantine");
    set_pname("halberds");
    set_short("abyss-black adamantine halberd");
    set_pshort("abyss-black adamantine halberds");
    set_long("@@long_desc");
    set_hit(26);
    set_pen(39);
    set_hands(W_BOTH);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE | W_SLASH);
    add_prop(OBJ_I_VALUE, 700);
    add_prop(OBJ_I_WEIGHT,10000);
    add_prop(OBJ_I_VOLUME,10000);
    poison_used = 0;
}
string
long_desc()
{
    if(poison_used)
	return "A fabulously-crafted adamantine halberd, its utterly lightless "+
	"color is reminiscent of the spawning grounds of the Abyss.\n";
    else
	return "A fabulously-crafted adamantine halberd, its utterly lightless "+
	"color is reminiscent of the spawning grounds of the Abyss. A thin "+
	"sheen of black liquid coats its blade.\n";
}
public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
    object poison;
    if(!random(5))
    {
	setuid();
	seteuid(getuid());
	poison = clone_object("/std/poison_effect");
	if(poison)
	{
	    if(random(3))
                poison_used = 1;
		poison -> move(enemy);
	    poison -> set_time(200);
	    poison -> set_interval(25);
	    poison -> set_strength(200);
	    poison -> set_damage(({POISON_HP, 200, POISON_STAT, SS_CON}));
	    poison -> start_poison();
	    return 0;
	}
	else
	    write("Failed to load poison for some reason.\n");
    }
    return 0;
}
