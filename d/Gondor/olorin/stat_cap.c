#pragma strict_types

inherit "/std/object.c";

#include "/d/Gondor/defs.h"

#define T_MIN	100
#define T_MAX	120

public void
create_object()
{
    set_name("calculator");
    set_short("stat cap calculator");
    set_adj( ({ "stat" , "cap", }) );

    set_long("A calculator to estimate to effect of a stat cap.\n");
}

public int
do_calc(string str)
{
    int     t_min = T_MIN,
            t_max = T_MAX,
            i,
            e,
            exp;

    for (i = t_min; i < t_max; i++)
    {
	// exp between i and i+1:
	e = (i+1)*(i+1)*(i+1) - i*i*i;
	exp += (t_max - t_min) * e / (t_max - i);
	write(sprintf("%3d  %10d  %10d\n", i, e, exp));
    }
    write(exp*6 + "\n");
    return 1;
}

public void
init()
{
    ::init();

    add_action(do_calc, "calc");
}
