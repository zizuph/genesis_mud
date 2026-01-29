#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

public void
create_weapon()
{
    //string *adj;
    mixed  *arr;
    int n, i;

    set_name("axe");
    set_pname(({"axes", "weapons", }));

    arr = ({
			"dwarven",	24,
			"large",	20,
			"ordinary",	18,
			"old",		16,
			"small",	12,
			"dull",		 8
		  });



    n = random(sizeof(arr)/2)*2;

    //adj = query_adjs();
	if (strlen(arr[n])) set_adj(arr[n]);
    

    //adj = ({"small", "old", "dwarven", "dull", "large"});


    set_pen(arr[n+1]);
    i = (arr[n+1] /2) +4;
	set_hit(i);

    set_wt(W_AXE);
    set_dt(W_BLUDGEON | W_SLASH);
    set_hands(W_NONE);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(i, arr[n+1]) + random(30));


    set_short(arr[n] + " " + query_name());
    set_long("You see nothing special about the "+ query_name() +".\n");

}
