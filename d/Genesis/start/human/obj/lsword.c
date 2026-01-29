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
    mixed  *arr;
    int n, i;

    set_name("sword");
    set_pname(({"swords", "weapons", }));
    set_adj("long");


    arr = ({
			"keen",		40, 
			"sharp",	35, 
			"black",	32, 
			"beautiful",28, 
			"nice",		20, 
			"ordinary",	18, 
			"ordinary",	18,
			"ordinary",	18,
			"ordinary",	18,
			"ordinary",	18,
			"ordinary",	18,
			"dull",		12,
			"rusty",	10, 
			"wooden",	 9

		  });



    n = random(sizeof(arr)/2)*2;
	if (strlen(arr[n])) add_adj(arr[n]);
	


	i = (arr[n+1]/2) + 8;
    set_hit(i);
    set_pen(arr[n+1]);

    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_NONE);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(i, arr[n+1]) + random(55));
  
	set_short(arr[n] + " long " + query_name());
    set_long("This "+ short() +" might come in handy in battle.\n");

}
