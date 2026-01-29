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
    set_adj("short");

    arr = ({
			"sharp",	25,
			"beautiful",20,
			"black",	18, 
			"ordinary",	13,
			"dull",		10,
			"rusty",	9,
			"wooden",	8,
			"broken",	7

		  });


    n = random(sizeof(arr)/2)*2;
	if (strlen(arr[n])) add_adj(arr[n]);
	
	i = (arr[n+1]/2) + 6;


    set_hit(i);
    set_pen(arr[n+1]);

    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_NONE);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(i, arr[n+1]) + random(35));
	
	set_short(arr[n] + " short sword");
    set_long("It is a quite good looking "+ short() +".\n");
}
